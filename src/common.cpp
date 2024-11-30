#include <bn_core.h>
#include <bn_random.h>

#include "background.h"
#include "common.h"
#include "pipesection.h"
#include "bird.h"


// From: #include <bn_random.h>
bn::random r;

bn::fixed backgroundScrollX=0;

int highScore = 0;

void CommonUpdateBackground(int updateFlags){

    
    bn::core::update();

    if(updateFlags & UpdateFlag_Background){

        backgroundScrollX += MOVE_SPEED;
        UpdateBackground(backgroundScrollX);
    }


    if(updateFlags & UpdateFlag_Player){
        
        UpdateBird();
    }

    if(updateFlags & UpdateFlag_Pipes){
        
        bird->set_x(bird->x()-MOVE_SPEED);
    }

    if(updateFlags & UpdateFlag_Pipes){
        
        UpdateAllPipes();
    }
}