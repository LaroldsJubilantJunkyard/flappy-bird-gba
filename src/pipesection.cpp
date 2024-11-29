
#include "bn_core.h"
#include "bn_vector.h"
#include "pipesection.h"
#include "score.h"
#include "global.h"
#include "bird.h"

bn::vector<PipeSection,MAXIMUM_PIPES> pipes;


void UpdateAllPipes(){

    bn::vector<PipeSection,MAXIMUM_PIPES>::iterator it = pipes.begin();


    while(it<pipes.end()){
        
        it->update();

        it++;
    }
}

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