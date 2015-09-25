#pragma once

#include <QTimer>
#include "I_GameTickerService.h"
class I_Game;

class GameTickerService : I_GameTickerService
{
    Q_OBJECT
public:
    explicit GameTickerService(I_Game& game);
    virtual ~GameTickerService();

public slots:
    void startGame();
    void togglePauseGame();
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
    QTimer tickTimer_;
    QTimer autoIncreaseTimer_;
    bool isAutoIncreaseModeActive_;
    bool gamePaused_;
};
