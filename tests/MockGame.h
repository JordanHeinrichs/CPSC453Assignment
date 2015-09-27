#pragma once

#include "gmock/gmock.h"
#include "businessLogic/I_Game.h"

class MockGame : public I_Game
{
    Q_OBJECT
public:
    MockGame();
    virtual ~MockGame();

    MOCK_METHOD0(reset, void());
    MOCK_METHOD0(tick, int());
    MOCK_METHOD0(moveLeft, bool());
    MOCK_METHOD0(moveRight, bool());
    MOCK_METHOD0(drop, bool());
    MOCK_METHOD0(rotateCW, bool());
    MOCK_METHOD0(rotateCCW, bool());

    MOCK_CONST_METHOD0(getWidth, int());
    MOCK_CONST_METHOD0(getHeight, int());

    MOCK_CONST_METHOD2(get, int(int, int));
    MOCK_METHOD2(get, int&(int, int));

    void emitStateChanged();
};
