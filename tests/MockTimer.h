#pragma once

#include <QObject>
#include "gmock/gmock.h"
#include "infrastructure/I_Timer.h"

class MockTimer : public QObject, public I_Timer
{
    Q_OBJECT
public:
    MockTimer();
    virtual ~MockTimer();

    MOCK_METHOD0(start, void());
    MOCK_METHOD1(start, void(int interval));
    MOCK_METHOD0(stop, void());

    MOCK_CONST_METHOD0(interval, int());
    MOCK_CONST_METHOD0(isActive, bool());
    MOCK_CONST_METHOD0(isSingleShot, bool());
    MOCK_CONST_METHOD0(remainingTime, int());
    MOCK_METHOD1(setInterval, void(int msec));
    MOCK_METHOD1(setSingleShot, void(bool singleShot));

    void emitTimeout();

signals:
    void timeout();
};
