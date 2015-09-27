#include "businessLogic/GameTickerService.h"
#include "businessLogic/I_Game.h"

namespace
{
    const int INITIAL_TICK_INTERVAL = 1000;
    const int MINIMUM_TICK_INTERVAL = 100;
    const int MAXIMUM_TICK_INTERVAL = 3000;
    const int TICK_INTERVAL_ADJUSTMENT_AMOUNT = 100;

    const int AUTO_INCREASE_INTERVAL = 5000;

    // Return values from the game class.
    const int GAME_OVER = -1;
}

GameTickerService::GameTickerService(I_Game& game)
: game_(game)
, isAutoIncreaseModeActive_(false)
, gamePaused_(false)
{
    setupTimers();
}

GameTickerService::~GameTickerService()
{
}

void GameTickerService::startGame()
{
    tickTimer_.start();
    game_.reset();
}

void GameTickerService::togglePauseGame()
{
    if (gamePaused_)
    {
        gamePaused_ = false;
        tickTimer_.start();
        if (isAutoIncreaseModeActive_)
        {
            autoIncreaseTimer_.start();
        }
    }
    else
    {
        gamePaused_ = true;
        tickTimer_.stop();
        autoIncreaseTimer_.stop();
    }
}

void GameTickerService::increaseRate()
{
    tickTimer_.setInterval(qBound(MINIMUM_TICK_INTERVAL,
        tickTimer_.interval() + TICK_INTERVAL_ADJUSTMENT_AMOUNT,
        MAXIMUM_TICK_INTERVAL));
}

void GameTickerService::decreaseRate()
{
    tickTimer_.setInterval(qBound(MINIMUM_TICK_INTERVAL,
        tickTimer_.interval() - TICK_INTERVAL_ADJUSTMENT_AMOUNT,
        MAXIMUM_TICK_INTERVAL));
    stopAutoIncreasing();
}

void GameTickerService::autoIncreaseRate()
{
    isAutoIncreaseModeActive_ = true;
    autoIncreaseTimer_.start();
}

void GameTickerService::tickGame()
{
    const int gameState = game_.tick();
    if (gameState == GAME_OVER)
    {
        stopGame();
    }
}

void GameTickerService::stopGame()
{
    tickTimer_.stop();
    stopAutoIncreasing();
}

void GameTickerService::setupTimers()
{
    tickTimer_.setSingleShot(false);
    tickTimer_.setInterval(INITIAL_TICK_INTERVAL);
    connect(&tickTimer_, SIGNAL(timeout()), this, SLOT(tickGame()));
    autoIncreaseTimer_.setSingleShot(false);
    autoIncreaseTimer_.setInterval(AUTO_INCREASE_INTERVAL);
    connect(&autoIncreaseTimer_, SIGNAL(timeout()), this, SLOT(increaseRate()));
}

void GameTickerService::stopAutoIncreasing()
{
    isAutoIncreaseModeActive_ = false;
    autoIncreaseTimer_.stop();
}
