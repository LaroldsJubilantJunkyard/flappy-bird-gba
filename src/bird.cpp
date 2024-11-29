#include "bn_core.h"
#include "bn_vector.h"
#include <bn_random.h>
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_camera_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_items_birdsprites.h"


#include "pipesection.h"
#include "background.h"
#include "score.h"
#include "bird.h"


// From: #include <bn_random.h>
bn::fixed birdYVelocity =0;

bool birdAlive=true;

bn::optional<bn::camera_ptr> camera;
bn::optional<bn::sprite_ptr> bird;
bn::optional<bn::sprite_animate_action<6>> birdFlapAnimation;


void InitializeBird(){

    birdYVelocity =0;
    birdAlive = true;

    camera = bn::camera_ptr::create();
    bird = bn::sprite_items::birdsprites.create_sprite(-172,0);
    bird->set_camera(camera.value());
    birdFlapAnimation = bn::create_sprite_animate_action_once(bird.value(),0,bn::sprite_items::birdsprites.tiles_item(),0,0,1,1,2,2);
}

void BirdJump(){

        birdYVelocity = -JUMP_SPEED;
        birdFlapAnimation->reset();

}


bn::fixed UpdateBird()
{

    birdYVelocity+=GRAVITY;
    bird->set_y(bird->y()+birdYVelocity);

    if(bn::keypad::a_pressed()){
        BirdJump();
    }

    bird->set_x(bird->x()+bn::fixed(MOVE_SPEED));
    bn::fixed cameraLeft = MAX (bird->x(),0);
    camera->set_x(cameraLeft);

    if(!birdFlapAnimation->done())birdFlapAnimation->update();

    if(bird->y()>48){
        birdAlive=false;
    }


    return bird->x();

}