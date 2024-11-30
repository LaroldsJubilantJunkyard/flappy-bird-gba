#include <bn_core.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>
#include "bn_sprite_items_titlesprite.h"
#include "common.h"
#include "bird.h"

#define TITLE_X -64
#define TITLE_Y (0)

GameState UpdateTitleGameState(void)  {
    
    bn::sprite_ptr titleSprite1 = bn::sprite_items::titlesprite.create_sprite(TITLE_X,TITLE_Y);
    bn::sprite_ptr titleSprite2 = bn::sprite_items::titlesprite.create_sprite(TITLE_X+64,TITLE_Y,1);
    bn::sprite_ptr titleSprite3 = bn::sprite_items::titlesprite.create_sprite(TITLE_X+128,TITLE_Y,2);

    while(!bn::keypad::a_pressed()){
        
        CommonUpdateBackground(UpdateFlag_Background);

    }

    return GameState_TapToStart;
}