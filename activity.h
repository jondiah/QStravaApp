#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QObject>

class Activity : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(double distance READ distance WRITE setDistance NOTIFY distanceChanged)
    Q_PROPERTY(double movingTime READ movingTime WRITE setMovingTime NOTIFY movingTimeChanged)

public:
    Activity(QObject *parent = 0);
    Activity(const QString &id,
             const QString &name,
             const double &distance,
             const double &movingTime,
             QObject *parent = 0);

    QString id() const;
    QString name() const;
    double distance() const;
    double movingTime() const;

public slots:
    void setId(const QString &id);
    void setName(const QString &name);
    void setDistance(double distance);
    void setMovingTime(double movingTime);

signals:
    void idChanged(QString id);
    void nameChanged(QString name);
    void distanceChanged(double distance);
    void movingTimeChanged(double movingTime);

private:
    QString m_id;
    QString m_name;
    double m_distance;
    double m_movingTime;
};

#endif // ACTIVITY_H
