#include "WindowView.h"
#include "I_Game.h"
#include "I_WindowUi.h"
#include "I_Renderer.h"

WindowView::WindowView(I_Game& game, I_WindowUi& windowUi, I_Renderer& renderer)
: game_(game)
, windowUi_(windowUi)
, renderer_(renderer)
{
    setupKeyboardControls();
}

WindowView::~WindowView()
{
}

void WindowView::setupKeyboardControls()
{
    connect(&windowUi_, SIGNAL(movePieceLeftRequested()), &game_, SLOT(moveLeft()()));
    connect(&windowUi_, SIGNAL(movePieceRightRequested()), &game_, SLOT(moveRight()()));
    connect(&windowUi_, SIGNAL(rotatePieceCounterClockwiseRequested()), &game_, SLOT(rotateCCW()()));
    connect(&windowUi_, SIGNAL(rotatePieceClockwiseRequested()), &game_, SLOT(rotateCW()()));
    connect(&windowUi_, SIGNAL(dropPieceRequested()), &game_, SLOT(drop()()));
}

void WindowView::setupGameOptions()
{
    connect(&windowUi_, SIGNAL(newGameRequested()), &game_, SLOT(reset()));
    connect(&windowUi_, SIGNAL(wireframeViewModeRequested()), this, SLOT(setViewModeWireframe()));
    connect(&windowUi_, SIGNAL(faceViewModeRequested()), this, SLOT(setViewModeFace()));
    connect(&windowUi_, SIGNAL(multicolouredViewModeRequested()), this, SLOT(setViewModeMulticoloured()));
}

void WindowView::setViewModeWireframe()
{
    renderer_.setViewMode(I_Renderer::Wireframe);
}

void WindowView::setViewModeFace()
{
    renderer_.setViewMode(I_Renderer::Face);
}

void WindowView::setViewModeMulticoloured()
{
    renderer_.setViewMode(I_Renderer::Multicoloured);
}


