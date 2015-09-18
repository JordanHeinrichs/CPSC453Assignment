#pragma once
/*
 * CPSC 453 - Introduction to Computer Graphics
 * Assignment 1
 */

#include <QMainWindow>
#include <I_WindowUi.h>
class QAction;

class WindowUi : public QMainWindow, public I_WindowUi
{
    Q_OBJECT
public:
    explicit WindowUi(QWidget* mainWidget);
    virtual ~WindowUi();

signals:
    void newGameRequested();
    void resetRequested();
    void wireframeViewModeRequested();
    void faceViewModeRequested();
    void multicolouredViewModeRequested();
    void pauseGameRequested();
    void speedUpGameRequested();
    void slowDownGameRequested();
    void autoIncreaseGameSpeedRequested();

private slots:
    void setDrawMode(QAction* action);

private:
    void createFileMenu();
    void createDrawMenu();
    void createGameMenu();

private:
    QAction* wireframeModeAction_;
    QAction* frameModeAction_;
    QAction* multicolouredModeAction_;
};
