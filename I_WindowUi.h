#pragma once
/*
 * CPSC 453 - Introduction to Computer Graphics
 * Assignment 1
 */
class I_WindowUi
{
public:
    virtual ~I_WindowUi() {}

protected: // signals:
    virtual void newGameRequested() = 0;
    virtual void resetRequested() = 0;
    virtual void wireframeViewModeRequested() = 0;
    virtual void faceViewModeRequested() = 0;
    virtual void multicolouredViewModeRequested() = 0;
    virtual void pauseGameRequested() = 0;
    virtual void speedUpGameRequested() = 0;
    virtual void slowDownGameRequested() = 0;
    virtual void autoIncreaseGameSpeedRequested() = 0;
};
