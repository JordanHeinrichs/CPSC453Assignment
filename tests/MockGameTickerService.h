#pragma once

#include "gmock/gmock.h"
#include "businessLogic/I_GameTickerService.h"

class MockGameTickerService
{
public:
    MockGameTickerService();
    virtual ~MockGameTickerService();

    MOCK_CONST_METHOD(isGameActive, bool());

    void emitGameActiveStateChanged(bool isGameActive);

public slots:
    MOCK_METHOD(startGame, void());
    MOCK_METHOD(pauseGame, void());
    MOCK_METHOD(unpauseGame, void());
    MOCK_METHOD(increaseRate, void());
    MOCK_METHOD(decreaseRate, void());
    MOCK_METHOD(autoIncreaseRate, void());
};
