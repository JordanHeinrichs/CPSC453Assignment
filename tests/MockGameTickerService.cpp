#include "MockGameTickerService.h"

MockGameTickerService::MockGameTickerService()
{
}

MockGameTickerService::~MockGameTickerService()
{
}

void MockGameTickerService::emitGameActiveStateChanged(bool isGameActive)
{
    emit gameActiveStateChanged(isGameActive);
}
