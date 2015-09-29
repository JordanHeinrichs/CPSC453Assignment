#pragma once

#include <QObject>

class I_GameTickerService : public QObject
{
    Q_OBJECT
public:
    virtual ~I_GameTickerService() {}

    virtual bool isGameActive() const = 0;

public slots:
    virtual void startGame() = 0;
    virtual void pauseGame() = 0;
    virtual void unpauseGame() = 0;
    virtual void increaseRate() = 0;
    virtual void decreaseRate() = 0;
    virtual void autoIncreaseRate() = 0;

signals:
    void gameActiveStateChanged(bool isGameActive);
};
