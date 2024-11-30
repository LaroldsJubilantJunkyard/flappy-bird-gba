
#include <bn_core.h>
#include <bn_random.h>

#define MAX(A,B) (((A)>(B)) ? (A): (B))
#define MIN(A,B) (((A)<(B)) ? (A): (B))
#define GRAVITY .3
#define JUMP_SPEED 3
#define MOVE_SPEED 2

extern bn::random r;

typedef enum GameState { GameState_GameStart, GameState_Title, GameState_TapToStart, GameState_Gameplay, GameState_GameEnd } GameState;
typedef enum UpdateFlags {UpdateFlag_Background = 1<<0, UpdateFlag_Player = 1<<1, UpdateFlag_PlayerDead=1<<2, UpdateFlag_Pipes=1<<3}UpdateFlags;

void CommonUpdateBackground(int);


extern bn::fixed birdX;

extern int highScore;