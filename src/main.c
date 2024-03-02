#include "main.h"
#include <raylib.h>
#include <raymath.h>

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "ray3d");
  SetWindowPosition(1176, 0);
  SetTargetFPS(60);

  walkD = LoadTexture("resources/orc/D_Walk.png");
  walkU = LoadTexture("resources/orc/U_Walk.png");
  walkS = LoadTexture("resources/orc/S_Walk.png");
  attackU = LoadTexture("resources/orc/U_Attack.png");
  attackD = LoadTexture("resources/orc/D_Attack.png");
  attackS = LoadTexture("resources/orc/S_Attack.png");

  Texture2D textures[] = {walkU, walkD, walkS, walkS, attackU, attackD, attackS, attackS};

  Camera2D camera = {0};
  camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
  camera.zoom = 2.5f;

  while (!WindowShouldClose()) {
    // update
    if (IsKeyDown(KEY_W)) state = WALK_U, dir = U, vel.y += SPEED;
    if (IsKeyDown(KEY_S)) state = WALK_D, dir = D, vel.y -= SPEED;
    if (IsKeyDown(KEY_D)) state = WALK_R, dir = R, vel.x -= SPEED;
    if (IsKeyDown(KEY_A)) state = WALK_L, dir = L, vel.x += SPEED;

    if (IsMouseButtonPressed(0)) {
      if (dir == U) state = ATTACK_U;
      if (dir == D) state = ATTACK_D;
      if (dir == L) state = ATTACK_L;
      if (dir == R) state = ATTACK_R;
    }

    vel = Vector2Multiply(vel, (Vector2){FRICTION, FRICTION});
    pos = Vector2Add(pos, Vector2Scale(vel, GetFrameTime()));

    // animation
    orcTimer -= GetFrameTime();
    if (orcTimer <= 0) orcTimer = ORC_TIME, orcIndex++;

    // draw
    BeginDrawing();
    BeginMode2D(camera);
    ClearBackground(RAYWHITE);

    int scaleX = 1;
    int scaleY = 1;
    if (dir == L) scaleX = 1;
    if (dir == R) scaleX = -1;

    Rectangle source = {ORC_SIZE * orcIndex, 0, ORC_SIZE * scaleX, ORC_SIZE * scaleY};
    Rectangle dest = {0, 0, source.width * scaleX, source.height * scaleY};
    Vector2 origin = (Vector2){pos.x, pos.y};

    DrawTexturePro(textures[state], source, dest, origin, 0, WHITE);

    // DrawRectangle(0, 0, ORC_SIZE, ORC_SIZE, (Color){255, 0, 0, 50});
    EndMode2D();

    // UI
    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
