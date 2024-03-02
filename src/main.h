#include <raylib.h>
#include <raymath.h>

#define ORC_SIZE  48
#define ORC_COUNT 6
#define ORC_FPS   10
#define ORC_TIME  1.0f / ORC_FPS

#define SPEED     10.0f
#define FRICTION  0.8f

const int screenWidth = 504;
const int screenHeight = 997;

Texture2D walkD;
Texture2D walkU;
Texture2D walkS;
Texture2D attackU;
Texture2D attackD;
Texture2D attackS;

int orcIndex = 0;
float orcTimer = ORC_TIME;

Vector2 vel = {0, 0};
Vector2 pos = {0, 0};

enum states {
  WALK_U,
  WALK_D,
  WALK_L,
  WALK_R,
  ATTACK_U,
  ATTACK_D,
  ATTACK_L,
  ATTACK_R,
};

enum dirs { L, R, U, D };
enum states state = WALK_D;
enum dirs dir = L;
