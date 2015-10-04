#pragma once

#include <QAction>
#include "gmock/gmock.h"
#include "view/I_WindowUi.h"

class MockWindowUi : public QObject, public I_WindowUi
{
    Q_OBJECT
public:
    MockWindowUi();
    virtual ~MockWindowUi();

    QAction& pauseAction() const;

    void emitNewGameRequested();
    void emitResetRequested();
    void emitWireframeViewModeRequested();
    void emitFaceViewModeRequested();
    void emitMulticolouredViewModeRequested();
    void emitSpeedUpGameRequested();
    void emitSlowDownGameRequested();
    void emitAutoIncreaseGameSpeedRequested();
    void emitMovePieceLeftRequested();
    void emitMovePieceRightRequested();
    void emitRotatePieceCounterClockwiseRequested();
    void emitRotatePieceClockwiseRequested();
    void emitDropPieceRequested();

signals:
    void newGameRequested();
    void resetRequested();
    void wireframeViewModeRequested();
    void faceViewModeRequested();
    void multicolouredViewModeRequested();
    void speedUpGameRequested();
    void slowDownGameRequested();
    void autoIncreaseGameSpeedRequested();

    void movePieceLeftRequested();
    void movePieceRightRequested();
    void rotatePieceCounterClockwiseRequested();
    void rotatePieceClockwiseRequested();
    void dropPieceRequested();

public: // public for testing.
    QAction pauseAction_;
};
