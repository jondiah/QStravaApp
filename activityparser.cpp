#include "activityparser.h"

#include <QVariant>

ActivityParser::ActivityParser(QJsonObject &activity) :
    m_object(&activity)
{
}

Activity *ActivityParser::parse() {
    if(m_object != NULL) {
        return new Activity(m_object->value("id").toVariant().toString(),
                            m_object->value("name").toString(),
                            m_object->value("distance").toDouble(),
                            m_object->value("movingTime").toDouble());
    }
    else {
        return new Activity();
    }
}
