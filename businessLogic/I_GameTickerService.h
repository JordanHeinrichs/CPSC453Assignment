#pragma once

#include <QObject>

class I_GameTickerService : public QObject
{
    Q_OBJECT
public:
    virtual ~I_GameTickerService() {}

public slots:
    virtual void startGame() = 0;
    virtual void togglePauseGame() = 0;
    virtual void increaseRate() = 0;
    virtual void decreaseRate() = 0;
    virtual void autoIncreaseRate() = 0;
};
