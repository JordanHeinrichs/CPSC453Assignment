#pragma once
/*
 * CPSC 453 - Introduction to Computer Graphics
 * Assignment 1
 */

#include <QMainWindow>
#include <view/I_WindowUi.h>
class QAction;

class WindowUi : public QMainWindow, public I_WindowUi
{
    Q_OBJECT
public:
    WindowUi(QWidget* renderer, QWidget* parent = 0);
    virtual ~WindowUi();

    QAction& pauseAction();
    QLabel& scoreLabel();

private slots:
    void setDrawMode(QAction* action);

protected:
    bool eventFilter(QObject* object, QEvent* event);

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

private:
    void createFileMenu();
    void createDrawMenu();
    void createGameMenu();
    void setupKeyboardHandling();
    void setDefaultViewMode();

private:
    QAction* pauseAction_;
    QLabel* scoreLabel_;

    QAction* wireframeModeAction_;
    QAction* faceModeAction_;
    QAction* multicolouredModeAction_;
};
