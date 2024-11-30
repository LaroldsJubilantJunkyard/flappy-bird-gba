#include <bn_core.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>
#include "bn_sprite_items_smallnumbersprites.h"
#include "bn_sprite_items_gameendsprites.h"
#include "bn_sprite_items_gameoversprite.h"
#include "bn_sprite_items_medalsprites.h"
#include "common.h"
#include "bird.h"
#include "score.h"
#include "pipesection.h"

#define MEDAL_Y_OFFSET 9
#define MEDAL_X_OFFSET 4

#define CURRENT_SCORE_X_OFFSET (60)
#define CURRENT_SCORE_Y_OFFSET (-6)

#define TOP_SCORE_X_OFFSET (60)
#define TOP_SCORE_Y_OFFSET (14)

GameState UpdateGameEndGameState(void){

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
        CommonUpdateBackground(UpdateFlag_Background|UpdateFlag_Pipes|UpdateFlag_PlayerDead);
    }
    

    HideScore();
    
    
    bn::sprite_ptr gameOverSprite1 = bn::sprite_items::gameoversprite.create_sprite(-32,-48);
    bn::sprite_ptr gameOverSprite2 = bn::sprite_items::gameoversprite.create_sprite(32, -48,1);

    while(gameEndSprite1.y()>0)
    {
        CommonUpdateBackground(UpdateFlag_Background|UpdateFlag_Pipes|UpdateFlag_PlayerDead);

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
        CommonUpdateBackground(UpdateFlag_Background|UpdateFlag_Pipes|UpdateFlag_PlayerDead);
    }

    while(gameEndSprite1.y()<110)
    {
        CommonUpdateBackground(UpdateFlag_Background|UpdateFlag_Pipes|UpdateFlag_PlayerDead);


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

    return GameState_TapToStart;
}