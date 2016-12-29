#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QVariantMap>
#include <QList>

class JsonParser
{
public:
    JsonParser();

    bool readActivitiesFile(QList<QObject *> &activityList, QString filePath = "activities.json");
    bool readAthleteFile(QVariantMap &athletes, QString filePath = "athlete.json");
};

#endif // JSONPARSER_H
