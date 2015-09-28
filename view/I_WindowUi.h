#pragma once
/*
* CPSC 453 - Introduction to Computer Graphics
* Assignment 1
*/

#include <QMainWindow>

class I_WindowUi : public QMainWindow
{
    Q_OBJECT
public:
    virtual ~I_WindowUi() {}

signals:
    void newGameRequested();
    void resetRequested();
    void wireframeViewModeRequested();
    void faceViewModeRequested();
    void multicolouredViewModeRequested();
    void pauseGameRequested();
    void unpauseGameRequested();
    void speedUpGameRequested();
    void slowDownGameRequested();
    void autoIncreaseGameSpeedRequested();

    void movePieceLeftRequested();
    void movePieceRightRequested();
    void rotatePieceCounterClockwiseRequested();
    void rotatePieceClockwiseRequested();
    void dropPieceRequested();
};
