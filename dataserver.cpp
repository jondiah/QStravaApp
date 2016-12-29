#include "dataserver.h"

#include <QUrl>
#include <QDebug>
#include <QFile>
#include <QUrlQuery>
#include <QDir>

QString clientId =          "";
QString clientSecret =      "";
QByteArray accessToken =    "";

const QString uriActivities = "https://www.strava.com/api/v3/activities";

DataServer::DataServer(QObject *parent) : QObject(parent)
{
    mNetworkAccessManager = NULL;
    m_stravaCredentialsFetched = setupStravaCredentials();
    mActivitiesName = "activities.json";
    mAthleteName = "athlete.json";
}

bool DataServer::setupStravaCredentials(QString path)
{
    QFile file("strava_config.txt");
    bool clientIdFound = false;
    bool clientSecretFound = false;
    bool accessTokenFound = false;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File " << file.fileName() << file.errorString();
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if(line.contains("clientId:")) {
            clientId = line.split(":").back();
            clientIdFound = true;
        } else if(line.contains("clientSecret:")) {
            clientSecret = line.split(":").back();
            clientSecretFound = true;
        } else if(line.contains("accessToken:")) {
            accessToken = line.split(":").back().toUtf8();
            accessTokenFound = true;
        }
    }

    if(!clientIdFound)
        qDebug("clientId not found");
    if(!clientSecretFound)
        qDebug("clientSecret not found");
    if(!accessTokenFound)
        qDebug("accessToken not found");

    if(clientIdFound && clientSecretFound && accessTokenFound)
        return true;
    else
        return false;
}

QNetworkAccessManager* DataServer::networkAccessManager()
{
    if(mNetworkAccessManager == NULL) {
        mNetworkAccessManager = new QNetworkAccessManager(this);
    }
    if(mNetworkAccessManager->networkAccessible() != QNetworkAccessManager::Accessible) {
        if(mNetworkAccessManager->networkAccessible() == QNetworkAccessManager::NotAccessible) {
            qDebug() << "NO ACCESS TO NETWORK";
            emit serverFailed(tr("No Network Access"));
        } else {
            qDebug() << "NO ACCESS: The network accessibility cannot be determined.";
            emit serverFailed(tr("No Network Access"));
        }
    }
    return mNetworkAccessManager;
}

void DataServer::requestActivities()
{
    QUrl url(uriActivities);
    QUrlQuery query;

    query.addQueryItem("per_page", "200");
    query.addQueryItem("page", "0");

    url.setQuery(query.query());

    QByteArray token = "Bearer " + accessToken;
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", token);

    QNetworkReply* reply = networkAccessManager()->get(request);
    bool connectResult = connect(reply, SIGNAL(finished()), this, SLOT(onFinishedRequestActivites()));
    Q_ASSERT(connectResult);
    Q_UNUSED(connectResult);
}

void DataServer::onFinishedRequestActivites()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if(!reply) {
        qWarning() << "Activites REPLY is NULL";
        return;
    }
    const int available = reply->bytesAvailable();
    if(available == 0) {
        qWarning() << "Activites: No Bytes received";
        return;
    }
    int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "Activites HTTP STATUS: " << httpStatusCode << " Bytes: " << available;
    if(httpStatusCode != 200) {
        qDebug() << "Activites Status Code not 200. No sucess getting Activites from Server. Got HTTP Status " +QString::number(httpStatusCode);
        return;
    }

    QFile saveFile(mActivitiesName);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open file to write " << mActivitiesName;
        emit serverFailed(tr("Activites Data cannot be written"));
        return;
    }
    qint64 bytesWritten = saveFile.write(reply->readAll());
    saveFile.close();
    qDebug() << "Activites Data Bytes written: " << bytesWritten << " to: " << mActivitiesName;
}

void DataServer::requestAthlete()
{
    QString uri = "https://www.strava.com/api/v3/athlete";
    QByteArray token = "Bearer " + accessToken;
    QNetworkRequest request(uri);
    request.setRawHeader("Authorization", token);

    QNetworkReply* reply = networkAccessManager()->get(request);
    bool connectResult = connect(reply, SIGNAL(finished()), this, SLOT(onFinishedRequestAthlete()));
    Q_ASSERT(connectResult);
    Q_UNUSED(connectResult);
}

void DataServer::onFinishedRequestAthlete()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if(!reply) {
        qWarning() << "Athlete REPLY is NULL";
        emit serverFailed(tr("No Network Reply"));
        return;
    }
    const int available = reply->bytesAvailable();
    if(available == 0) {
        qWarning() << "Athlete: No Bytes received";
        emit serverFailed(tr("No Schedule Data received"));
        return;
    }
    int httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "Athlete HTTP STATUS: " << httpStatusCode << " Bytes: " << available;
    if(httpStatusCode != 200) {
        qDebug() << "Athlete Status Code not 200";
        emit serverFailed(tr("No sucess getting Athlete from Server. Got HTTP Status ")+QString::number(httpStatusCode));
        return;
    }

    QFile saveFile(mAthleteName);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open file to write " << mAthleteName;
        emit serverFailed(tr("Athlete Data cannot be written"));
        return;
    }
    qint64 bytesWritten = saveFile.write(reply->readAll());
    saveFile.close();
    qDebug() << "Athlete Data Bytes written: " << bytesWritten << " to: " << mAthleteName;
}