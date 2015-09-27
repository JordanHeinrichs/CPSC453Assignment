#pragma once
/*
* CPSC 453 - Introduction to Computer Graphics
* Assignment 1
*/

#include <QApplication>
#include <QScopedPointer>
class Game;
class GameTickerService;
class Renderer;
class WindowUi;
class WindowView;

class AssignmentApp : public QApplication
{
    Q_OBJECT
public:
    AssignmentApp(int argc, char *argv[]);
    ~AssignmentApp();

private:
    QScopedPointer<Renderer> renderer_;
    QScopedPointer<WindowUi> windowUi_;
    QScopedPointer<Game> game_;
    QScopedPointer<GameTickerService> gameTickerService_;
    QScopedPointer<WindowView> windowView_;
};