#include "jsonparser.h"
#include "activity.h"
#include "activityparser.h"

#include <memory>

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

JsonParser::JsonParser() {

}

bool JsonParser::readActivitiesFile(QList<QObject *> &activityList, QString filePath) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << file.errorString();
        return false;
    }

    QJsonDocument jda = QJsonDocument::fromJson(file.readAll());
    file.close();

    if(!jda.isArray()) {
        qWarning() << "Couldn't create JSON from file";
        return false;
    }

    foreach(const QJsonValue &value, jda.array()) {
        QJsonObject obj = value.toObject();
        ActivityParser activityParser(obj);

        Activity *activity = activityParser.parse();

        activityList.append(activity);
    }

    qDebug() << "Model length: " << activityList.size();

    return true;
}

bool JsonParser::readAthleteFile(QVariantMap &athletes, QString filePath) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << file.errorString();
        return false;
    }

    QJsonDocument jda = QJsonDocument::fromJson(file.readAll());
    file.close();

    if(!jda.isObject()) {
        qWarning() << "Couldn't create JSON";
        return false;
    }

    athletes = jda.toVariant().toMap();
    return true;
}
