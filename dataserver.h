#ifndef DATASERVER_H
#define DATASERVER_H

#include <QObject>
#include <QVariantMap>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkrequest.h>
#include <QtNetwork/qnetworkreply.h>

class DataServer : public QObject
{
    Q_OBJECT
public:
    explicit DataServer(QObject *parent = 0);

    bool setupStravaCredentials(QString path = ".");

    QNetworkAccessManager* networkAccessManager();

    void requestActivities();
    void requestAthlete();

signals:
    serverFailed(const QString msg);

public slots:

private slots:
    void onFinishedRequestActivites();
    void onFinishedRequestAthlete();

private:
    QString mActivitiesName;
    QString mAthleteName;

    bool m_stravaCredentialsFetched;

    QNetworkAccessManager* mNetworkAccessManager;
};

#endif // DATASERVER_H
