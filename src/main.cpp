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
#include "bn_sprite_items_smallnumbersprites.h"
#include "bn_sprite_items_gameendsprites.h"
#include "bn_sprite_items_medalsprites.h"
#include "bn_sprite_items_titlesprite.h"
#include "bn_sprite_items_taptapsprite.h"


#include "pipesection.h"
#include "background.h"
#include "score.h"
#include "bird.h"

#define MAX(A,B) (((A)>(B)) ? (A): (B))
#define MIN(A,B) (((A)<(B)) ? (A): (B))
#define GRAVITY .3
#define JUMP_SPEED 3
#define MOVE_SPEED 2


// From: #include <bn_random.h>
bn::random r;

int highScore = 0;
int spawnCounter=0;



int main()
{
    bn::core::init();

    bn::fixed birdX;

    maingameplay:

    InitializeBackground();
    InitializeBird();
    InitializePipes();

    {

        #define TITLE_X -64
        #define TITLE_Y (-48)

        
        bn::sprite_ptr titleSprite1 = bn::sprite_items::titlesprite.create_sprite(TITLE_X,TITLE_Y);
        bn::sprite_ptr titleSprite2 = bn::sprite_items::titlesprite.create_sprite(TITLE_X+64,TITLE_Y,1);
        bn::sprite_ptr titleSprite3 = bn::sprite_items::titlesprite.create_sprite(TITLE_X+128,TITLE_Y,2);

        
        bn::sprite_ptr tapTapSprite = bn::sprite_items::taptapsprite.create_sprite(64, 16);
  

        while(bird->x()<0 || !bn::keypad::a_pressed()){

            
            bn::core::update();


            UpdateBird();
        
                birdX += MOVE_SPEED;
            UpdateBackground(birdX);


            if(bird->y()>0){
                BirdJump();
            }
        }
    }

    InitializeScore();

    while(birdAlive)
    {
        bn::core::update();

        spawnCounter+=MOVE_SPEED;


        if(spawnCounter>56){
            

            if( (r.get() % 256)>100 || spawnCounter > 72){

                SpawnPipe();
            }

            spawnCounter=0;

        }

       UpdateBird();
    
            birdX += MOVE_SPEED;
        UpdateBackground(birdX);
        UpdateAllPipes();

    }

    highScore = MAX(highScore,score);

    HideScore();

    {

        #define MEDAL_Y_OFFSET 9
        #define MEDAL_X_OFFSET 4

        #define CURRENT_SCORE_X_OFFSET (60)
        #define CURRENT_SCORE_Y_OFFSET (-6)

        #define TOP_SCORE_X_OFFSET (60)
        #define TOP_SCORE_Y_OFFSET (14)

        bn::fixed gameEndY = 110;
        bn::fixed gameEndX = -32;

        bn::sprite_ptr gameEndSprite1 = bn::sprite_items::gameendsprites.create_sprite(gameEndX,gameEndY);
        bn::sprite_ptr gameEndSprite2 = bn::sprite_items::gameendsprites.create_sprite(gameEndX+64,gameEndY,1);
        bn::optional<bn::sprite_ptr> medal;

        
        bn::sprite_ptr currentScore1 = bn::sprite_items::smallnumbersprites.create_sprite(gameEndX+CURRENT_SCORE_X_OFFSET,gameEndY+CURRENT_SCORE_Y_OFFSET,(score/100)%10);
        bn::sprite_ptr currentScore2 = bn::sprite_items::smallnumbersprites.create_sprite(gameEndX+CURRENT_SCORE_X_OFFSET+8,gameEndY+CURRENT_SCORE_Y_OFFSET,(score/10)%10);
        bn::sprite_ptr currentScore3 = bn::sprite_items::smallnumbersprites.create_sprite(gameEndX+CURRENT_SCORE_X_OFFSET+16,gameEndY+CURRENT_SCORE_Y_OFFSET,score%10);
        
        bn::sprite_ptr topScore1 = bn::sprite_items::smallnumbersprites.create_sprite(gameEndX+TOP_SCORE_X_OFFSET,gameEndY+TOP_SCORE_Y_OFFSET,(highScore/100)%10);
        bn::sprite_ptr topScore2 = bn::sprite_items::smallnumbersprites.create_sprite(gameEndX+TOP_SCORE_X_OFFSET+8,gameEndY+TOP_SCORE_Y_OFFSET,(highScore/10)%10);
        bn::sprite_ptr topScore3 = bn::sprite_items::smallnumbersprites.create_sprite(gameEndX+TOP_SCORE_X_OFFSET+16,gameEndY+TOP_SCORE_Y_OFFSET,highScore%10);
        
        
        if(score>10) medal = bn::sprite_items::medalsprites.create_sprite(gameEndX+MEDAL_X_OFFSET,gameEndY+MEDAL_Y_OFFSET,MIN(score/10,3));

        gameEndSprite1.set_bg_priority(3);
        gameEndSprite2.set_bg_priority(3);

        while(activePipeCount>0 && bird->x()>-150)
        {
            bn::core::update();

            
            birdX += MOVE_SPEED;
            bird->set_x(bird->x()-MOVE_SPEED);
        
            UpdateBackground(birdX);
            UpdateAllPipes();


        }


        while(gameEndSprite1.y()>0)
        {
            bn::core::update();

            
            birdX += MOVE_SPEED;
            bird->set_x(bird->x()-=MOVE_SPEED);
        
            UpdateBackground(birdX);
            UpdateAllPipes();

            gameEndSprite1.set_y(gameEndSprite1.y()-5);
            gameEndSprite2.set_y(gameEndSprite1.y());
            topScore1.set_y(gameEndSprite1.y()+TOP_SCORE_Y_OFFSET);
            topScore2.set_y(gameEndSprite1.y()+TOP_SCORE_Y_OFFSET);
            topScore3.set_y(gameEndSprite1.y()+TOP_SCORE_Y_OFFSET);
            currentScore1.set_y(gameEndSprite1.y()+CURRENT_SCORE_Y_OFFSET);
            currentScore2.set_y(gameEndSprite1.y()+CURRENT_SCORE_Y_OFFSET);
            currentScore3.set_y(gameEndSprite1.y()+CURRENT_SCORE_Y_OFFSET);
            if(medal.has_value())medal->set_y(gameEndSprite1.y()+MEDAL_Y_OFFSET);
        }
        while(!bn::keypad::a_pressed())
        {
            bn::core::update();

            
            birdX += MOVE_SPEED;
            bird->set_x(bird->x()-=MOVE_SPEED);
        
            UpdateBackground(birdX);
            UpdateAllPipes();


        }
        while(gameEndSprite1.y()<110)
        {
            bn::core::update();

            
            birdX += MOVE_SPEED;
            bird->set_x(bird->x()-MOVE_SPEED);
        
            UpdateBackground(birdX);
            UpdateAllPipes();


            gameEndSprite1.set_y(gameEndSprite1.y()+5);
            gameEndSprite2.set_y(gameEndSprite1.y());
            topScore1.set_y(gameEndSprite1.y()+TOP_SCORE_Y_OFFSET);
            topScore2.set_y(gameEndSprite1.y()+TOP_SCORE_Y_OFFSET);
            topScore3.set_y(gameEndSprite1.y()+TOP_SCORE_Y_OFFSET);
            currentScore1.set_y(gameEndSprite1.y()+CURRENT_SCORE_Y_OFFSET);
            currentScore2.set_y(gameEndSprite1.y()+CURRENT_SCORE_Y_OFFSET);
            currentScore3.set_y(gameEndSprite1.y()+CURRENT_SCORE_Y_OFFSET);
            if(medal.has_value())medal->set_y(gameEndSprite1.y()+MEDAL_Y_OFFSET);
        }

    }

    
    while(activePipeCount>0)
    {
        bn::core::update();

        birdX += MOVE_SPEED;
        bird->set_x(bird->x()-MOVE_SPEED);
    
        UpdateBackground(birdX);
        UpdateAllPipes();

    }


    goto maingameplay;
}
