/*
* CPSC 453 - Introduction to Computer Graphics
* Assignment 1
*/

#include "application/AssignmentApp.h"
#include "businessLogic/game.h"
#include "businessLogic/GameTickerService.h"
#include "infrastructure/QtTimer.h"
#include "view/Renderer.h"
#include "view/WindowUi.h"
#include "view/WindowView.h"

namespace
{
    const int WIDTH_OF_GAME_AREA = 10;
    const int HEIGHT_OF_GAME_AREA = 20;
}

AssignmentApp::AssignmentApp(int argc, char *argv[])
: QApplication(argc, argv)
, renderer_(new Renderer())
, windowUi_(new WindowUi(renderer_.data()))
, game_(new Game(WIDTH_OF_GAME_AREA, HEIGHT_OF_GAME_AREA))
, gameTimer1_(new QtTimer())
, gameTimer2_(new QtTimer())
, gameTickerService_(new GameTickerService(*game_, *gameTimer1_, *gameTimer2_))
, windowView_(new WindowView(*game_, *windowUi_, *renderer_, *gameTickerService_))
{
}

AssignmentApp::~AssignmentApp()
{
}
