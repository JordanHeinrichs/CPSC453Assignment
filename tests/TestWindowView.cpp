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
    gameTickerService_.emitGameActiveStateChanged(true);

    EXPECT_CALL(game_, moveLeft());

    windowUi_.emitMovePieceLeftRequested();
}

TEST_F(TestWindowView, willMovePieceRight)
{
    gameTickerService_.emitGameActiveStateChanged(true);

    EXPECT_CALL(game_, moveRight());

    windowUi_.emitMovePieceRightRequested();
}

TEST_F(TestWindowView, willRotateCCW)
{
    gameTickerService_.emitGameActiveStateChanged(true);

    EXPECT_CALL(game_, rotateCCW());

    windowUi_.emitRotatePieceCounterClockwiseRequested();
}

TEST_F(TestWindowView, willRotateCW)
{
    gameTickerService_.emitGameActiveStateChanged(true);

    EXPECT_CALL(game_, rotateCW());

    windowUi_.emitRotatePieceClockwiseRequested();
}

TEST_F(TestWindowView, willDropPiece)
{
    gameTickerService_.emitGameActiveStateChanged(true);

    EXPECT_CALL(game_, drop());

    windowUi_.emitDropPieceRequested();
}

TEST_F(TestWindowView, willNotMovePieceLeftOnConstruction)
{
    EXPECT_CALL(game_, moveLeft()).Times(0);

    windowUi_.emitMovePieceLeftRequested();
}

TEST_F(TestWindowView, willNotMovePieceRightOnConstruction)
{
    EXPECT_CALL(game_, moveRight()).Times(0);

    windowUi_.emitMovePieceRightRequested();
}

TEST_F(TestWindowView, willNotRotateCCWOnConstruction)
{
    EXPECT_CALL(game_, rotateCCW()).Times(0);

    windowUi_.emitRotatePieceCounterClockwiseRequested();
}

TEST_F(TestWindowView, willNotRotateCWOnConstruction)
{
    EXPECT_CALL(game_, rotateCW()).Times(0);

    windowUi_.emitRotatePieceClockwiseRequested();
}

TEST_F(TestWindowView, willNotDropPieceOnConstruction)
{
    EXPECT_CALL(game_, drop()).Times(0);

    windowUi_.emitDropPieceRequested();
}

TEST_F(TestWindowView, willNotMovePieceLeftOnBecomingUnactive)
{
    gameTickerService_.emitGameActiveStateChanged(true);
    gameTickerService_.emitGameActiveStateChanged(false);

    EXPECT_CALL(game_, moveLeft()).Times(0);

    windowUi_.emitMovePieceLeftRequested();
}

TEST_F(TestWindowView, willNotMovePieceRightOnBecomingUnactive)
{
    gameTickerService_.emitGameActiveStateChanged(true);
    gameTickerService_.emitGameActiveStateChanged(false);

    EXPECT_CALL(game_, moveRight()).Times(0);

    windowUi_.emitMovePieceRightRequested();
}

TEST_F(TestWindowView, willNotRotateCCWOnBecomingUnactive)
{
    gameTickerService_.emitGameActiveStateChanged(true);
    gameTickerService_.emitGameActiveStateChanged(false);

    EXPECT_CALL(game_, rotateCCW()).Times(0);

    windowUi_.emitRotatePieceCounterClockwiseRequested();
}

TEST_F(TestWindowView, willNotRotateCWOnBecomingUnactive)
{
    gameTickerService_.emitGameActiveStateChanged(true);
    gameTickerService_.emitGameActiveStateChanged(false);

    EXPECT_CALL(game_, rotateCW()).Times(0);

    windowUi_.emitRotatePieceClockwiseRequested();
}

TEST_F(TestWindowView, willNotDropPieceOnBecomingUnactive)
{
    gameTickerService_.emitGameActiveStateChanged(true);
    gameTickerService_.emitGameActiveStateChanged(false);

    EXPECT_CALL(game_, drop()).Times(0);

    windowUi_.emitDropPieceRequested();
}
