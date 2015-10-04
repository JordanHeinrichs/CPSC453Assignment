#include <QSignalSpy>
#include "TestGameTickerService.h"

namespace
{
    const int MINIMUM_TICK_INTERVAL = 100;
    const int MAXIMUM_TICK_INTERVAL = 3000;
    const int TICK_INTERVAL_ADJUSTMENT_AMOUNT = 100;
    const int INITIAL_TICK_INTERVAL = 1000;

    const int GAME_OVER = -1;
}

TEST_F(TestGameTickerService, willResetGameWhenGameIsStarted)
{
    EXPECT_CALL(game_, reset());

    patient_.startGame();
}

TEST_F(TestGameTickerService, willStartTickTimerWhenGameStarts)
{
    EXPECT_CALL(tickTimer_, start());

    tickTimer_.start();
}

TEST_F(TestGameTickerService, willTickGameWhenTickTimerTimesOut)
{
    EXPECT_CALL(game_, tick());

    tickTimer_.emitTimeout();
}

TEST_F(TestGameTickerService, willStopAllTimersWhenGameIsPaused)
{
    EXPECT_CALL(tickTimer_, stop());
    EXPECT_CALL(autoIncreaseTimer_, stop());

    patient_.pauseGame();
}

TEST_F(TestGameTickerService, willStartTickTimerWhenGameIsUnpaused)
{
    EXPECT_CALL(tickTimer_, start());

    patient_.unpauseGame();
}

TEST_F(TestGameTickerService, willStartAutoIncreaseTimerIfInAutoIncreaseMode)
{
    patient_.autoIncreaseRate();

    EXPECT_CALL(autoIncreaseTimer_, start());

    patient_.unpauseGame();
}

TEST_F(TestGameTickerService, willNotStartAutoIncreaseTimerIfNotInAutoIncreaseMode)
{
    EXPECT_CALL(autoIncreaseTimer_, start()).Times(0);

    patient_.unpauseGame();
}

TEST_F(TestGameTickerService, willIncreaseRateOnAutoIncreaseTimeout)
{
    const int expectedValue = INITIAL_TICK_INTERVAL - TICK_INTERVAL_ADJUSTMENT_AMOUNT;
    patient_.autoIncreaseRate();
    autoIncreaseTimer_.emitTimeout();

    EXPECT_CALL(tickTimer_, start(expectedValue));

    tickTimer_.emitTimeout();
}

TEST_F(TestGameTickerService, willDecreaseIntervalOnIncreaseRate)
{
    const int expectedValue = INITIAL_TICK_INTERVAL - TICK_INTERVAL_ADJUSTMENT_AMOUNT;
    patient_.increaseRate();

    EXPECT_CALL(tickTimer_, start(expectedValue));

    tickTimer_.emitTimeout();
}

TEST_F(TestGameTickerService, willIncreaseIntervalOnDecreaseRate)
{
    const int expectedValue = INITIAL_TICK_INTERVAL + TICK_INTERVAL_ADJUSTMENT_AMOUNT;
    patient_.decreaseRate();

    EXPECT_CALL(tickTimer_, start(expectedValue));

    tickTimer_.emitTimeout();
}

TEST_F(TestGameTickerService, willStopTimersIfGameOver)
{
    ON_CALL(game_, tick()).WillByDefault(Return(GAME_OVER));

    EXPECT_CALL(tickTimer_, stop());
    EXPECT_CALL(autoIncreaseTimer_, stop());

    tickTimer_.emitTimeout();
}

TEST_F(TestGameTickerService, willNotIncreaseRateBelowMinimumPeriod)
{
    for (int i = 0; i < 100; i++)
    {
        patient_.increaseRate();
    }

    EXPECT_CALL(tickTimer_, start(MINIMUM_TICK_INTERVAL));

    tickTimer_.emitTimeout();
}

TEST_F(TestGameTickerService, willNotDecreaseRateAboveMaximumPeriod)
{
    for (int i = 0; i < 100; i++)
    {
        patient_.decreaseRate();
    }

    EXPECT_CALL(tickTimer_, start(MAXIMUM_TICK_INTERVAL));

    tickTimer_.emitTimeout();
}

TEST_F(TestGameTickerService, willIsGameActiveReturnCorrectValue)
{
    EXPECT_CALL(tickTimer_, isActive()).WillOnce(Return(true));
    EXPECT_EQ(patient_.isGameActive(), true);
}

TEST_F(TestGameTickerService, willEmitGameActiveStateChangedOnStarting)
{
    QSignalSpy spy(&patient_, SIGNAL(gameActiveStateChanged(bool)));

    patient_.startGame();

    EXPECT_EQ(spy.count(), 1);
    EXPECT_EQ(spy.takeFirst().at(0).toBool(), true);
}

TEST_F(TestGameTickerService, willEmitGameActiveStateChangedOnPausing)
{
    QSignalSpy spy(&patient_, SIGNAL(gameActiveStateChanged(bool)));

    patient_.pauseGame();

    EXPECT_EQ(spy.count(), 1);
    EXPECT_EQ(spy.takeFirst().at(0).toBool(), false);
}

TEST_F(TestGameTickerService, willEmitGameActiveStateChangedOnUnpausing)
{
    QSignalSpy spy(&patient_, SIGNAL(gameActiveStateChanged(bool)));

    patient_.unpauseGame();

    EXPECT_EQ(spy.count(), 1);
    EXPECT_EQ(spy.takeFirst().at(0).toBool(), true);
}

TEST_F(TestGameTickerService, willEmitGameActiveStateChangedOnGameOver)
{
    ON_CALL(game_, tick()).WillByDefault(Return(GAME_OVER));
    QSignalSpy spy(&patient_, SIGNAL(gameActiveStateChanged(bool)));

    tickTimer_.emitTimeout();

    EXPECT_EQ(spy.count(), 1);
    EXPECT_EQ(spy.takeFirst().at(0).toBool(), false);
}
