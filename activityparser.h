#ifndef ACTIVITYPARSER_H
#define ACTIVITYPARSER_H

#include "activity.h"

#include <memory>

#include <QJsonObject>

class ActivityParser
{
public:
    ActivityParser(QJsonObject &activity);

    Activity* parse();

private:
    QJsonObject *m_object;
};

#endif // ACTIVITYPARSER_H
