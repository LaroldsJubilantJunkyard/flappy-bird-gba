#include <bn_core.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>
#include "bn_sprite_items_getreadysprite.h"
#include "bn_sprite_items_taptapsprite.h"



#include "bird.h"
#include "common.h"

GameState UpdateTapToStartGameState(void)  {

    ShowBird();
    
    bn::sprite_ptr getReadySprite1 = bn::sprite_items::getreadysprite.create_sprite(-16, -32);
    bn::sprite_ptr getReadySprite2 = bn::sprite_items::getreadysprite.create_sprite(48, -32,1);

    bn::sprite_ptr tapTapSprite = bn::sprite_items::taptapsprite.create_sprite(64, 16);


    while(!bn::keypad::a_pressed()){
        CommonUpdateBackground(UpdateFlag_Background | UpdateFlag_Player);

        if(bird->y()>0){
            BirdJump();
        }
    }

    return GameState_Gameplay;
}