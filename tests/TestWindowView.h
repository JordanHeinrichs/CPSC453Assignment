#pragma once

#include "view/WindowView.h"
#include "gtest/gtest.h"
#include "tests/MockGame.h"
#include "tests/MockGameTickerService.h"
#include "tests/MockWindowUi.h"
#include "tests/MockRenderer.h"

using namespace ::testing;

class TestWindowView : public Test
{
protected:
    TestWindowView()
    : patient_(game_,
        windowUi_,
        renderer_,
        gameTickerService_)
    {
    }

    virtual ~TestWindowView()
    {
    }

    NiceMock<MockGame> game_;
    NiceMock<MockWindowUi> windowUi_;
    NiceMock<MockRenderer> renderer_;
    NiceMock<MockGameTickerService> gameTickerService_;
    WindowView patient_;
};
