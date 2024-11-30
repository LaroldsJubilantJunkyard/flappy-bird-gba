#include <bn_core.h>

#include "common.h"
#include "score.h"
#include "bird.h"
#include "pipesection.h"

int spawnCounter=0;

GameState UpdateGameplayGameState(void){

    InitializeScore();
    InitializePipes();

    spawnCounter=0;

    while(birdAlive)
    {
        CommonUpdateBackground(UpdateFlag_Player | UpdateFlag_Pipes | UpdateFlag_Background);

        spawnCounter+=MOVE_SPEED;


        if(spawnCounter>56){
            

            if( (r.get() % 256)>100 || spawnCounter > 72){

                SpawnPipe();
            }

            spawnCounter=0;

        }


    }

    highScore = MAX(highScore,score);

    return GameState_GameEnd;
}