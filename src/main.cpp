#include "bn_core.h"
#include "common.h"

GameState UpdateGameStartGameState(void);
GameState UpdateTitleGameState(void);
GameState UpdateTapToStartGameState(void);
GameState UpdateGameplayGameState(void);
GameState UpdateGameEndGameState(void);

int main()
{
    bn::core::init();

    GameState nextGameState = GameState_GameStart;
  
    while(true){

        switch(nextGameState){

           default: nextGameState = UpdateGameStartGameState(); break;
            case  GameState_Title:nextGameState = UpdateTitleGameState(); break;
            case  GameState_TapToStart:nextGameState = UpdateTapToStartGameState(); break;
            case  GameState_Gameplay:nextGameState = UpdateGameplayGameState(); break;
            case  GameState_GameEnd:nextGameState = UpdateGameEndGameState(); break;
        }

        bn::core::update();
    }


}
