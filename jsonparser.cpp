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
    bool filesToParse = true;
    int page = 1;
    while(filesToParse) {
        QFile file(filePath+QString::number(page)+".json");


        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << file.errorString();
            filesToParse = false;
            return false;
        }

        QJsonParseError parseError;
        QJsonDocument jda = QJsonDocument::fromJson(file.readAll(), &parseError);
        qDebug() << parseError.errorString();
        file.close();

        if(jda.isEmpty()) {
            qWarning() << "Couldn't create JSON from file, isEmpty()";
            return false;
        }

        if(!jda.isArray()) {
            qWarning() << "Couldn't create JSON from file, is not an array";
            return false;
        }

        foreach(const QJsonValue &value, jda.array()) {
            qDebug() << "Append: " << value.toObject().value("id").toVariant().toString();
            QJsonObject obj = value.toObject();
            ActivityParser activityParser(obj);

            Activity *activity = activityParser.parse();

            activityList.append(activity);
        }

        page = page + 1;

        qDebug() << "Model length: " << activityList.size();
    }

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
