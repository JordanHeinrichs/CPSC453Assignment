/*
* CPSC 453 - Introduction to Computer Graphics
* Assignment 1
*/

#include "AssignmentApp.h"
#include "game.h"
#include "Renderer.h"
#include "WindowUi.h"
#include "WindowView.h"

AssignmentApp::AssignmentApp(int argc, char *argv[])
: QApplication(argc, argv)
, renderer_(new Renderer())
, windowUi_(new WindowUi(renderer_.data()))
, gameBusinessLogic_(new Game())
, windowView_(new WindowView(*windowUi_, *gameBusinessLogic_))
{
}

AssignmentApp::~AssignmentApp()
{
}

