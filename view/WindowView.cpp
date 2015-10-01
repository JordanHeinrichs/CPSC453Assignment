#include <QAction>

#include "businessLogic/I_Game.h"
#include "businessLogic/I_GameTickerService.h"
#include "view/I_Renderer.h"
#include "view/I_WindowUi.h"
#include "view/WindowView.h"

WindowView::WindowView(I_Game& game,
   I_WindowUi& windowUi,
   I_Renderer& renderer,
   I_GameTickerService& gameTickerService)
: game_(game)
, windowUi_(windowUi)
, renderer_(renderer)
, gameTickerService_(gameTickerService)
{
    setupKeyboardControls();
    setupGameOptions();
    setupGameTickerOptions();
}

WindowView::~WindowView()
{
}

void WindowView::setupKeyboardControls()
{
    connect(&windowUi_, SIGNAL(movePieceLeftRequested()), &game_, SLOT(moveLeft()));
    connect(&windowUi_, SIGNAL(movePieceRightRequested()), &game_, SLOT(moveRight()));
    connect(&windowUi_, SIGNAL(rotatePieceCounterClockwiseRequested()), &game_, SLOT(rotateCCW()));
    connect(&windowUi_, SIGNAL(rotatePieceClockwiseRequested()), &game_, SLOT(rotateCW()));
    connect(&windowUi_, SIGNAL(dropPieceRequested()), &game_, SLOT(drop()));
}

void WindowView::setupGameOptions()
{
    connect(&windowUi_, SIGNAL(newGameRequested()), &game_, SLOT(reset()));
    connect(&windowUi_, SIGNAL(wireframeViewModeRequested()), this, SLOT(setViewModeWireframe()));
    connect(&windowUi_, SIGNAL(faceViewModeRequested()), this, SLOT(setViewModeFace()));
    connect(&windowUi_, SIGNAL(multicolouredViewModeRequested()), this, SLOT(setViewModeMulticoloured()));
}

void WindowView::setupGameTickerOptions()
{
    connect(&windowUi_, SIGNAL(newGameRequested()), &gameTickerService_, SLOT(startGame()));
    connect(&windowUi_.pauseAction(), SIGNAL(triggered()), this, SLOT(handlePauseGameTriggered()));
    connect(&windowUi_, SIGNAL(speedUpGameRequested()), &gameTickerService_, SLOT(increaseRate()));
    connect(&windowUi_, SIGNAL(slowDownGameRequested()), &gameTickerService_, SLOT(decreaseRate()));
    connect(&windowUi_, SIGNAL(autoIncreaseGameSpeedRequested()), &gameTickerService_, SLOT(autoIncreaseRate()));
    connect(&gameTickerService_, SIGNAL(gameActiveStateChanged(bool)), this, SLOT(handleGameActiveStateChanged(bool)));
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

void WindowView::handlePauseGameTriggered()
{
    if (gameTickerService_.isGameActive())
    {
        gameTickerService_.pauseGame();
    }
    else
    {
        gameTickerService_.unpauseGame();
    }
}

void WindowView::handleGameActiveStateChanged(bool isGameActive)
{
    if (isGameActive)
    {
        windowUi_.pauseAction().setText("&Pause");
    }
    else
    {
        windowUi_.pauseAction().setText("Un&pause");
    }
}
