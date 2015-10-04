#pragma once
/*
* CPSC 453 - Introduction to Computer Graphics
* Assignment 1
*/

class QAction;

class I_WindowUi
{
public:
    virtual ~I_WindowUi() {}

    virtual QAction& pauseAction() = 0;

protected: // signals:
    virtual void newGameRequested() = 0;
    virtual void resetRequested() = 0;
    virtual void wireframeViewModeRequested() = 0;
    virtual void faceViewModeRequested() = 0;
    virtual void multicolouredViewModeRequested() = 0;
    virtual void speedUpGameRequested() = 0;
    virtual void slowDownGameRequested() = 0;
    virtual void autoIncreaseGameSpeedRequested() = 0;

    virtual void movePieceLeftRequested() = 0;
    virtual void movePieceRightRequested() = 0;
    virtual void rotatePieceCounterClockwiseRequested() = 0;
    virtual void rotatePieceClockwiseRequested() = 0;
    virtual void dropPieceRequested() = 0;
};
