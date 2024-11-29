#include "bn_core.h"


#define MAX(A,B) (((A)>(B)) ? (A): (B))
#define GRAVITY .3
#define JUMP_SPEED 3
#define MOVE_SPEED 2


extern bool birdAlive;
extern bn::optional<bn::sprite_ptr> bird;

void InitializeBird();
void BirdJump();

bn::fixed UpdateBird();