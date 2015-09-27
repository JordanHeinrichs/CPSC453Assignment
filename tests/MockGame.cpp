#include "MockGame.h"

MockGame::MockGame()
{
}

MockGame::~MockGame()
{
}

void MockGame::emitStateChanged()
{
    emit stateChanged();
}
