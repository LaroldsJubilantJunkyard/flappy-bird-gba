#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_items_greenpipesprite.h"

#define MAXIMUM_PIPES 10

class PipeSection{

    public:

        PipeSection(){
            
            topPipe=bn::sprite_items::greenpipesprite.create_sprite(120,-80);
            topPipe->set_vertical_flip(true);
            topPipe->set_z_order(0);

            bottomPipe=bn::sprite_items::greenpipesprite.create_sprite(120,80);
            bottomPipe->set_z_order(0);

            reset();
            
            bottomPipe->set_visible(false);
            topPipe->set_visible(false);
        }

        bool active;
        bool counted;
        bn::fixed x, gapSize, gapOffset;

        bn::optional<bn::sprite_ptr> topPipe,bottomPipe;

        void update(void);
        void reset(void);
};

void InitializePipes();
void UpdateAllPipes();
void SpawnPipe();

extern int  activePipeCount;