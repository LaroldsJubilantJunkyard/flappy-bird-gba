#include <bn_core.h>
#include <bn_sprite_ptr.h>

#define MAX(A,B) (((A)>(B)) ? (A): (B))
#define GRAVITY .3
#define JUMP_SPEED 3
#define MOVE_SPEED 2


extern bool birdAlive;
extern bn::optional<bn::sprite_ptr> bird;

void InitializeBird();
void BirdJump();
void HideBird(void);
void ShowBird(void);

bn::fixed UpdateBird();