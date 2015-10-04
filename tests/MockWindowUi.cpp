#include "MockWindowUi.h"

MockWindowUi::MockWindowUi()
{
}

MockWindowUi::~MockWindowUi()
{
}

QAction& MockWindowUi::pauseAction() const
{
    return pauseAction_;
}

void MockWindowUi::emitNewGameRequested()
{
    emit newGameRequested();
}
void MockWindowUi::emitResetRequested()
{
    emit resetRequested();
}
void MockWindowUi::emitWireframeViewModeRequested()
{
    emit wireframeViewModeRequested();
}
void MockWindowUi::emitFaceViewModeRequested()
{
    emit faceViewModeRequested();
}
void MockWindowUi::emitMulticolouredViewModeRequested()
{
    emit multicolouredViewModeRequested();
}
void MockWindowUi::emitSpeedUpGameRequested()
{
    emit speedUpGameRequested();
}
void MockWindowUi::emitSlowDownGameRequested()
{
    emit slowDownGameRequested();
}
void MockWindowUi::emitAutoIncreaseGameSpeedRequested()
{
    emit autoIncreaseGameSpeedRequested();
}
void MockWindowUi::emitMovePieceLeftRequested()
{
    emit movePieceLeftRequested();
}
void MockWindowUi::emitMovePieceRightRequested()
{
    emit movePieceRightRequested();
}
void MockWindowUi::emitRotatePieceCounterClockwiseRequested()
{
    emit rotatePieceCounterClockwiseRequested();
}
void MockWindowUi::emitRotatePieceClockwiseRequested()
{
    emit rotatePieceClockwiseRequested();
}
void MockWindowUi::emitDropPieceRequested()
{
    emit dropPieceRequested();
}
