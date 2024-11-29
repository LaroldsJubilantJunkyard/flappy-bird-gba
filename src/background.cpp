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
#include "score.h"
#include "bird.h"

#define MAX(A,B) (((A)>(B)) ? (A): (B))
#define GRAVITY .3
#define JUMP_SPEED 3
#define MOVE_SPEED 2


bn::optional<bn::regular_bg_ptr> bkg1,bkg2,bkg3,ground;


void InitializeBackground(){
    

    bkg1 = bn::regular_bg_items::background_layer1.create_bg();
    bkg2 = bn::regular_bg_items::background_layer2.create_bg();
    bkg3 = bn::regular_bg_items::background_layer3.create_bg();
    ground = bn::regular_bg_items::groundbackground.create_bg();
    ground->set_priority(0);
    ground->set_y(-(256-160)/2);
    bkg1->set_y(-(256-160)/2);
    bkg2->set_y(-(256-160)/2);
    bkg3->set_y(-(256-160)/2);
}

void UpdateBackground(bn::fixed birdX){
     bn::fixed cameraLeft = MAX (birdX,0);
    bn::fixed cameraLeft2 = MAX (birdX/16,0) % 256;
    bn::fixed cameraLeft3 = MAX (birdX/8,0) % 256;
    bn::fixed cameraLeft4 = MAX (birdX/4,0) % 256;

    ground->set_x(-cameraLeft);
    bkg1->set_x(-cameraLeft2);
    bkg2->set_x(-cameraLeft3);
    bkg3->set_x(-cameraLeft4);
}
