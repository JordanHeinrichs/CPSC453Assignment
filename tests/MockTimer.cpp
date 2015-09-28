#include "MockTimer.h"

MockTimer::MockTimer()
{
}

MockTimer::~MockTimer()
{
}

void MockTimer::emitTimeout()
{
    emit timeout();
}
