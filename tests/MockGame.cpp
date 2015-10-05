#include "MockGame.h"

MockGame::MockGame()
{
}

MockGame::~MockGame()
{
}

void MockGame::emitScoreChanged(int score)
{
    emit scoreChanged(score);
}
