#include <QSignalSpy>
#include "TestGameTickerService.h"

namespace
{
    const int MINIMUM_TICK_INTERVAL = 100;
    const int MAXIMUM_TICK_INTERVAL = 3000;
    const int TICK_INTERVAL_ADJUSTMENT_AMOUNT = 100;

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
    ON_CALL(tickTimer_, interval()).WillByDefault(Return(300));
    const int expectedValue = 300 + TICK_INTERVAL_ADJUSTMENT_AMOUNT;
    patient_.autoIncreaseRate();

    EXPECT_CALL(tickTimer_, setInterval(expectedValue));

    autoIncreaseTimer_.emitTimeout();
}

TEST_F(TestGameTickerService, willIncreaseRateOnIncreaseRate)
{
    ON_CALL(tickTimer_, interval()).WillByDefault(Return(300));
    const int expectedValue = 300 + TICK_INTERVAL_ADJUSTMENT_AMOUNT;

    EXPECT_CALL(tickTimer_, setInterval(expectedValue));

    patient_.increaseRate();
}

TEST_F(TestGameTickerService, willDecreaseRateOnDecreaseRate)
{
    ON_CALL(tickTimer_, interval()).WillByDefault(Return(300));
    const int expectedValue = 300 - TICK_INTERVAL_ADJUSTMENT_AMOUNT;

    EXPECT_CALL(tickTimer_, setInterval(expectedValue));

    patient_.decreaseRate();
}

TEST_F(TestGameTickerService, willStopTimersIfGameOver)
{
    ON_CALL(game_, tick()).WillByDefault(Return(GAME_OVER));

    EXPECT_CALL(tickTimer_, stop());
    EXPECT_CALL(autoIncreaseTimer_, stop());

    tickTimer_.emitTimeout();
}

TEST_F(TestGameTickerService, willNotDecreaseRateBelowMinimum)
{
    ON_CALL(tickTimer_, interval()).WillByDefault(Return(MINIMUM_TICK_INTERVAL));

    EXPECT_CALL(tickTimer_, setInterval(MINIMUM_TICK_INTERVAL));

    patient_.decreaseRate();
}

TEST_F(TestGameTickerService, willNotIncreaseRateAboveMaximum)
{
    ON_CALL(tickTimer_, interval()).WillByDefault(Return(MAXIMUM_TICK_INTERVAL));

    EXPECT_CALL(tickTimer_, setInterval(MAXIMUM_TICK_INTERVAL));

    patient_.increaseRate();
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
