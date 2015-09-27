#include "TestGameTickerService.h"

TEST_F(TestGameTickerService, willResetGameWhenGameIsStarted)
{
    EXPECT_CALL(game_, reset());

    patient_.startGame();
}
