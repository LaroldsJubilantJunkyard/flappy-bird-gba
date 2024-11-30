#include "common.h"
#include "background.h"
#include "bird.h"
#include "pipesection.h"

GameState UpdateGameStartGameState(void){

    InitializeBackground();
    InitializeBird();
    InitializePipes();

    return GameState_Title;

}