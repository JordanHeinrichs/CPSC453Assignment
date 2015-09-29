#pragma once
/*
 * CPSC 453 - Introduction to Computer Graphics
 * Assignment 1
 */

#include <view/I_WindowUi.h>
class QAction;

class WindowUi : public I_WindowUi
{
    Q_OBJECT
public:
    explicit WindowUi(QWidget* mainWidget);
    virtual ~WindowUi();

    QAction& pauseAction() const;

private slots:
    void setDrawMode(QAction* action);

protected:
    bool eventFilter(QObject* object, QEvent* event);

private:
    void createFileMenu();
    void createDrawMenu();
    void createGameMenu();
    void setupKeyboardHandling();

private:
    QAction* pauseAction_;

    QAction* wireframeModeAction_;
    QAction* frameModeAction_;
    QAction* multicolouredModeAction_;
};
