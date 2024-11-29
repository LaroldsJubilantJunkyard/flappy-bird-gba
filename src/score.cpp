#include "bn_core.h"
#include "bn_vector.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_items_largenumberssprites.h"


int score=0;

bn::vector<bn::sprite_ptr,3> largeNumbers;


void UpdateScore(void){

    if(largeNumbers.size()!=3)return;

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

void HideScore(void){

    largeNumbers.clear();
}

void InitializeScore(void){

    score=0;

    if(largeNumbers.size()!=3){

        largeNumbers.push_back(bn::sprite_items::largenumberssprites.create_sprite(0,-58));
        largeNumbers.push_back(bn::sprite_items::largenumberssprites.create_sprite(16,-58));
        largeNumbers.push_back(bn::sprite_items::largenumberssprites.create_sprite(32,-58));
    }

    UpdateScore();

}

void IncreaseScore(void){

    score++;
    UpdateScore();
}

