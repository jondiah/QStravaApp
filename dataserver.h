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

    void requestAllActivities(bool force = false);
    void requestAthlete();

signals:
    void serverFailed(const QString msg);

public slots:

private slots:
    void onFinishedRequestActivites();
    void onFinishedRequestAthlete();

private:
    void requestActivities(int page = 1);

    QString mActivitiesName;
    QString mAthleteName;

    bool m_stravaCredentialsFetched;

    QNetworkAccessManager* mNetworkAccessManager;
};

#endif // DATASERVER_H
