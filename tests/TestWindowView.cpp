#include "TestWindowView.h"

TEST_F(TestWindowView, willSetViewModeToWireframe)
{
    EXPECT_CALL(renderer_, setViewMode(I_Renderer::Wireframe));

    windowUi_.emitWireframeViewModeRequested();
}

TEST_F(TestWindowView, willSetViewModeToFace)
{
    EXPECT_CALL(renderer_, setViewMode(I_Renderer::Face));

    windowUi_.emitFaceViewModeRequested();
}

TEST_F(TestWindowView, willSetViewModeToMultiColored)
{
    EXPECT_CALL(renderer_, setViewMode(I_Renderer::MultiColored));

    windowUi_.emitMulticolouredViewModeRequested();
}

TEST_F(TestWindowView, willPauseGameIfGameIsActive)
{
    ON_CALL(gameTickerService_, isGameActive()).WillByDefault(Return(true));

    EXPECT_CALL(gameTickerService_, pauseGame());

    windowUi_.pauseAction().trigger();
}

TEST_F(TestWindowView, willUnpauseGameIfGameIsNotActive)
{
    ON_CALL(gameTickerService_, isGameActive()).WillByDefault(Return(false));

    EXPECT_CALL(gameTickerService_, unpauseGame());

    windowUi_.pauseAction().trigger();
}

TEST_F(TestWindowView, willSetTextWhenGameBecomesActive)
{
    gameTickerService_.emitGameActiveStateChanged(true);

    EXPECT_EQ(windowUi_.pauseAction().text(), QString("&Pause"));
}

TEST_F(TestWindowView, willSetTextWhenGameBecomesUnactive)
{
    gameTickerService_.emitGameActiveStateChanged(false);

    EXPECT_EQ(windowUi_.pauseAction().text(), QString("Un&pause"));
}

TEST_F(TestWindowView, willMovePieceLeft)
{
    EXPECT_CALL(game_, moveLeft());

    windowUi_.emitMovePieceLeftRequested();
}

TEST_F(TestWindowView, willMovePieceRight)
{
    EXPECT_CALL(game_, moveRight());

    windowUi_.emitMovePieceRightRequested();
}

TEST_F(TestWindowView, willRotateCCW)
{
    EXPECT_CALL(game_, rotateCCW());

    windowUi_.emitRotatePieceCounterClockwiseRequested();
}

TEST_F(TestWindowView, willRotateCW)
{
    EXPECT_CALL(game_, rotateCW());

    windowUi_.emitRotatePieceClockwiseRequested();
}

TEST_F(TestWindowView, willDropPiece)
{
    EXPECT_CALL(game_, drop());

    windowUi_.emitDropPieceRequested();
}
