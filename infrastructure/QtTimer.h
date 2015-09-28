#pragma once

#include <QObject>
#include <QTimer>
#include "infrastructure/I_Timer.h"

class QtTimer : public QObject, public I_Timer
{
    Q_OBJECT
public:
    QtTimer();
    virtual ~QtTimer();

public slots:
    void start();
    void stop();

public:
    int interval() const;
    bool isActive() const;
    bool isSingleShot() const;
    int remainingTime() const;

    void setInterval(int msec);
    void setSingleShot(bool singleShot);

signals:
    void timeout();

private:
    QTimer timer_;
};

inline void QtTimer::start()
{
    timer_.start();
}

inline void QtTimer::stop()
{
    timer_.stop();
}

inline int QtTimer::interval() const
{
    return timer_.interval();
}

inline bool QtTimer::isActive() const
{
    return timer_.isActive();
}

inline bool QtTimer::isSingleShot() const
{
    return timer_.isSingleShot();
}

inline int QtTimer::remainingTime() const
{
    return timer_.remainingTime();
}

inline void QtTimer::setInterval(int msec)
{
    return timer_.setInterval(msec);
}

inline void QtTimer::setSingleShot(bool singleShot)
{
    timer_.setSingleShot(singleShot);
}
