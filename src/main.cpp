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

#define MAX(A,B) (((A)>(B)) ? (A): (B))
#define GRAVITY .3
#define JUMP_SPEED 3
#define MOVE_SPEED 2
#define MAXIMUM_PIPES 10


// From: #include <bn_random.h>
bn::random r;

int score=0;
int spawnCounter=0;

bn::vector<bn::sprite_ptr,3> largeNumbers;


void UpdateScore(void){


    bn::vector<bn::sprite_ptr,3>::iterator it = largeNumbers.begin();

    while(it<largeNumbers.end()){

        int id = (it-largeNumbers.begin());

        if(id==0)id=score/100;
        else if(id==1)id=(score/10) %10;
        else if(id==2)id=score%10;
        
        it->set_z_order(-20);
        it->set_tiles(bn::sprite_items::largenumberssprites.tiles_item(),id);
        it++;


    }
}

void IncreaseScore(void){

    score++;
    UpdateScore();
}

class PipeSection{

    public:

        PipeSection(){
            
            topPipe=bn::sprite_items::greenpipesprite.create_sprite(120,-80);
            topPipe->set_vertical_flip(true);
            topPipe->set_z_order(0);

            bottomPipe=bn::sprite_items::greenpipesprite.create_sprite(120,80);
            bottomPipe->set_z_order(0);

            reset();
        }

        bool active;
        bool counted;
        bn::fixed x, gapSize, gapOffset;

        bn::optional<bn::sprite_ptr> topPipe,bottomPipe;

        void update(void);
        void reset(void);
};


void PipeSection::reset(void){

    active=true;
    counted=false;
    x=120;

    gapSize = 32 + (r.get()%32);
    gapOffset = -32+(r.get()%64);
    
    this->topPipe->set_visible(true);
    this->bottomPipe->set_visible(true);
    
    this->topPipe->set_x(this->x);
    this->bottomPipe->set_x(this->x);

    bn::fixed topCenter =  (gapOffset/2) - (gapSize/2)-32;
    bn::fixed bottomCenter = (gapOffset/2) + (gapSize/2)+32;

    topCenter = (topCenter >= -64) ? -64 : topCenter;
    bottomCenter = topCenter+gapSize+64;
    
    this->topPipe->set_y(topCenter);
    this->bottomPipe->set_y(bottomCenter);

}
void PipeSection::update(void){

    if(!this->active)return;

    if(!counted){

        if(this->x<-16){

            IncreaseScore();
            counted=true;
        }
    }

    this->x-=MOVE_SPEED;

    if(this->x<-120){
        this->active=false;
        this->topPipe->set_visible(false);
        this->bottomPipe->set_visible(false);
    }


    this->topPipe->set_x(this->x);
    this->bottomPipe->set_x(this->x);
}


bn::vector<PipeSection,MAXIMUM_PIPES> pipes;
void SpawnPipe(void){

    if(pipes.size()<MAXIMUM_PIPES){
        PipeSection newPipeSection;
        pipes.push_back(newPipeSection);
    }
    else {

        bn::vector<PipeSection,MAXIMUM_PIPES>::iterator it = pipes.begin();


        while(it<pipes.end()){
            
            if(!it->active){
                it->reset();
                return;
            }

            it++;
        }

    }
}


int main()
{
    bn::core::init();

    largeNumbers.push_back(bn::sprite_items::largenumberssprites.create_sprite(0,-64));
    largeNumbers.push_back(bn::sprite_items::largenumberssprites.create_sprite(16,-64));
    largeNumbers.push_back(bn::sprite_items::largenumberssprites.create_sprite(32,-64));



    UpdateScore();

    bn::camera_ptr camera = bn::camera_ptr::create();
    bn::regular_bg_ptr bkg1 = bn::regular_bg_items::background_layer1.create_bg();
    bn::regular_bg_ptr bkg2 = bn::regular_bg_items::background_layer2.create_bg();
    bn::regular_bg_ptr bkg3 = bn::regular_bg_items::background_layer3.create_bg();
    bn::regular_bg_ptr ground = bn::regular_bg_items::groundbackground.create_bg();

    ground.set_priority(0);

    bn::sprite_ptr bird = bn::sprite_items::birdsprites.create_sprite(-172,0);

    bn::sprite_animate_action<6> birdFlapAnimation = bn::create_sprite_animate_action_once(bird,0,bn::sprite_items::birdsprites.tiles_item(),0,0,1,1,2,2);

    ground.set_y(-(256-160)/2);
    bkg1.set_y(-(256-160)/2);
    bkg2.set_y(-(256-160)/2);
    bkg3.set_y(-(256-160)/2);
    bird.set_camera(camera);

    bn::fixed birdYVelocity =0;

    while(true)
    {
        bn::core::update();

        //largeNumber0.

        birdYVelocity+=GRAVITY;
        bird.set_y(bird.y()+birdYVelocity);

        if(bn::keypad::a_pressed()){
            birdYVelocity = -JUMP_SPEED;
            birdFlapAnimation.reset();
        }


        spawnCounter+=MOVE_SPEED;


        if(spawnCounter>56){

            

            if( (r.get() % 256)>100 || spawnCounter > 72){

                SpawnPipe();
            }

            spawnCounter=0;

        }


    
    
        bird.set_x(bird.x()+bn::fixed(MOVE_SPEED));

        bn::fixed cameraLeft = MAX (bird.x(),0);
        bn::fixed cameraLeft2 = MAX (bird.x()/16,0) % 256;
        bn::fixed cameraLeft3 = MAX (bird.x()/8,0) % 256;
        bn::fixed cameraLeft4 = MAX (bird.x()/4,0) % 256;

        ground.set_x(-cameraLeft);
        bkg1.set_x(-cameraLeft2);
        bkg2.set_x(-cameraLeft3);
        bkg3.set_x(-cameraLeft4);
        camera.set_x(cameraLeft);

        if(!birdFlapAnimation.done())birdFlapAnimation.update();

        bn::vector<PipeSection,MAXIMUM_PIPES>::iterator it = pipes.begin();


        while(it<pipes.end()){
            
            it->update();

            it++;
        }

    }
}
