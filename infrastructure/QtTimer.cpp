#include "QtTimer.h"
#include "infrastructure/ConnectionHelpers.h"

QtTimer::QtTimer()
{
    safeConnect(&timer_, SIGNAL(timeout()), this, SIGNAL(timeout()));
}

QtTimer::~QtTimer()
{
}
