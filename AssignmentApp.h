#pragma once
/*
* CPSC 453 - Introduction to Computer Graphics
* Assignment 1
*/

#include <QApplication>
#include <QScopedPointer>
class Renderer;
class WindowUi;
class WindowView;
class Game;

class AssignmentApp : public QApplication
{
    Q_OBJECT
public:
    AssignmentApp(int argc, char *argv[]);
    ~AssignmentApp();

private:
    QScopedPointer<Renderer> renderer_;
    QScopedPointer<WindowUi> windowUi_;
    QScopedPointer<Game> gameBusinessLogic_;
    QScopedPointer<WindowView> windowView_;
};
