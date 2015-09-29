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

    virtual QAction& pauseAction() const = 0;

signals:
    void newGameRequested();
    void resetRequested();
    void wireframeViewModeRequested();
    void faceViewModeRequested();
    void multicolouredViewModeRequested();
    void speedUpGameRequested();
    void slowDownGameRequested();
    void autoIncreaseGameSpeedRequested();

    void movePieceLeftRequested();
    void movePieceRightRequested();
    void rotatePieceCounterClockwiseRequested();
    void rotatePieceClockwiseRequested();
    void dropPieceRequested();
};
