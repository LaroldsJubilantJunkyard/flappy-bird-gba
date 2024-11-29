#include "bn_core.h"
#include "bn_vector.h"
#include <bn_random.h>
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_camera_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_regular_bg_items_background.h"
#include "bn_regular_bg_items_groundbackground.h"
#include "bn_regular_bg_items_background_layer1.h"
#include "bn_regular_bg_items_background_layer2.h"
#include "bn_regular_bg_items_background_layer3.h"
#include "bn_sprite_items_birdsprites.h"
#include "bn_sprite_items_greenpipesprite.h"
#include "bn_sprite_items_largenumberssprites.h"


#include "pipesection.h"
#include "background.h"
#include "score.h"
#include "bird.h"

#define MAX(A,B) (((A)>(B)) ? (A): (B))
#define GRAVITY .3
#define JUMP_SPEED 3
#define MOVE_SPEED 2


// From: #include <bn_random.h>
bn::random r;

int spawnCounter=0;



int main()
{
    bn::core::init();

    InitializeScore();
    InitializeBackground();
    InitializeBird();


    while(true)
    {
        bn::core::update();


        spawnCounter+=MOVE_SPEED;


        if(spawnCounter>56){
            

            if( (r.get() % 256)>100 || spawnCounter > 72){

                SpawnPipe();
            }

            spawnCounter=0;

        }



        bn::fixed birdX = UpdateBird();
    
        UpdateBackground(birdX);
        UpdateAllPipes();

    }
}
