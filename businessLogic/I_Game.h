#pragma once

#include <QObject>

class I_Game : public QObject
{
    Q_OBJECT
public:
    virtual ~I_Game() {}

public slots:
    virtual void reset() = 0;
    virtual int tick() = 0;

    virtual bool moveLeft() = 0;
    virtual bool moveRight() = 0;

    virtual bool drop() = 0;

    virtual bool rotateCW() = 0;
    virtual bool rotateCCW() = 0;

public:
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

    virtual int get(int r, int c) const = 0;
    virtual int& get(int r, int c) = 0;
};
