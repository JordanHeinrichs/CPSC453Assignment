#pragma once

#include "gmock/gmock.h"
#include "businessLogic/I_GameTickerService.h"

class MockGameTickerService : public I_GameTickerService
{
    Q_OBJECT
public:
    MockGameTickerService();
    virtual ~MockGameTickerService();

    MOCK_CONST_METHOD0(isGameActive, bool());

    void emitGameActiveStateChanged(bool isGameActive);

    MOCK_METHOD0(startGame, void());
    MOCK_METHOD0(pauseGame, void());
    MOCK_METHOD0(unpauseGame, void());
    MOCK_METHOD0(increaseRate, void());
    MOCK_METHOD0(decreaseRate, void());
    MOCK_METHOD0(autoIncreaseRate, void());
};
