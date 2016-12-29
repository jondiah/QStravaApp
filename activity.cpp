#include "activity.h"

Activity::Activity(QObject *parent)
{

}

Activity::Activity(const QString &id,
                   const QString &name,
                   const double &distance,
                   const double &movingTime,
                   QObject *parent) :
    m_id(id),
    m_name(name),
    m_distance(distance),
    m_movingTime(movingTime),
    QObject(parent)
{

}

QString Activity::id() const
{
    return m_id;
}

QString Activity::name() const
{
    return m_name;
}

double Activity::distance() const
{
    return m_distance;
}

double Activity::movingTime() const
{
    return m_movingTime;
}

void Activity::setId(const QString &id)
{
    if(id == m_id)
        return;

    m_id = id;
    emit idChanged(id);
}

void Activity::setName(const QString &name)
{
    if(name == m_name)
        return;

    m_name = name;
    emit nameChanged(name);
}

void Activity::setDistance(double distance)
{
    if (m_distance == distance)
        return;

    m_distance = distance;
    emit distanceChanged(distance);
}

void Activity::setMovingTime(double movingTime)
{
    if (m_movingTime == movingTime)
        return;

    m_movingTime = movingTime;
    emit movingTimeChanged(movingTime);
}
