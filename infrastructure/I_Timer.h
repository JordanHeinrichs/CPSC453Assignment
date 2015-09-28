#pragma once

class I_Timer
{
public:
    virtual ~I_Timer() {}

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual int interval() const = 0;
    virtual bool isActive() const = 0;
    virtual bool isSingleShot() const = 0;
    virtual int remainingTime() const = 0;
    virtual void setInterval(int msec) = 0;
    virtual void setSingleShot(bool singleShot) = 0;

protected: // signals:
    virtual void timeout() = 0;
};
