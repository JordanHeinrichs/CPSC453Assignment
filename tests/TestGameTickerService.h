#pragma once

#include "businessLogic/GameTickerService.h"
#include "gtest/gtest.h"
#include "tests/MockGame.h"

class TestGameTickerService : public ::testing::Test
{
protected:
    TestGameTickerService()
    : patient_(game_)
    {
    }

    virtual ~TestGameTickerService()
    {
    }

    ::testing::NiceMock<MockGame> game_;
    GameTickerService patient_;
};
