#pragma once

#include "businessLogic/GameTickerService.h"
#include "gtest/gtest.h"
#include "tests/MockGame.h"
#include "tests/MockTimer.h"

using namespace ::testing;

class TestGameTickerService : public Test
{
protected:
    TestGameTickerService()
    : patient_(game_, tickTimer_, autoIncreaseTimer_)
    {
    }

    virtual ~TestGameTickerService()
    {
    }

    NiceMock<MockGame> game_;
    NiceMock<MockTimer> tickTimer_;
    NiceMock<MockTimer> autoIncreaseTimer_;

    GameTickerService patient_;
};
