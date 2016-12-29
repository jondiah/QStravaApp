#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "dataserver.h"
#include "jsonparser.h"
#include "activity.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DataServer dServer;
    JsonParser jsParser;

    dServer.requestActivities();
    QList<QObject*> activities;
    jsParser.readActivitiesFile(activities);

    //dServer.requestAthlete();
    QVariantMap data2;
    jsParser.readAthleteFile(data2);

    // QML Backend
    QQmlApplicationEngine engine;

    qmlRegisterType<Activity>();
    engine.rootContext()->setContextProperty("activityModel", QVariant::fromValue(activities));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}
