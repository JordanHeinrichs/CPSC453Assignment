#pragma once

#include <QTimer>
#include "businessLogic/I_GameTickerService.h"
class I_Game;
class I_Timer;

class GameTickerService : public I_GameTickerService
{
    Q_OBJECT
public:
    GameTickerService(I_Game& game, I_Timer& tickTimer, I_Timer& autoIncreaseTimer);
    virtual ~GameTickerService();

    bool isGameActive() const;

public slots:
    void startGame();
    void pauseGame();
    void unpauseGame();
    void increaseRate();
    void decreaseRate();
    void autoIncreaseRate();

private slots:
    void tickGame();
    void stopGame();

private:
    void setupTimers();
    void stopAutoIncreasing();

private:
    I_Game& game_;
    I_Timer& tickTimer_;
    I_Timer& autoIncreaseTimer_;
    bool isAutoIncreaseModeActive_;
    int interval_;
};
