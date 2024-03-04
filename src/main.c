#include "main.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

const int screenWidth = 504;
const int screenHeight = 997;

// const int screenWidth = 1920;
// const int screenHeight = 1080;

int main() {

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "ray3d");
  SetWindowPosition(1176, 0);
  SetTargetFPS(60);

  const Vector2 center = {screenWidth / 2.0f, screenHeight / 2.0f};

  Vector2* mobs;
  int mobs_s = MOBS_COUNT;

  mobs = (Vector2*)malloc(mobs_s * sizeof(Vector2));

  for (int i = 0; i < mobs_s; i++)
    mobs[i] = (Vector2
    ){GetRandomValue(-MOBS_RADIUS, MOBS_RADIUS), GetRandomValue(-MOBS_RADIUS, MOBS_RADIUS)};

  Camera2D camera = {};
  camera.offset = center;
  camera.zoom = 0.2f;

  while (!WindowShouldClose()) {
    // update
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) state = WALK_U, dir = U, vel.y -= SPEED;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) state = WALK_D, dir = D, vel.y += SPEED;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) state = WALK_R, dir = R, vel.x += SPEED;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) state = WALK_L, dir = L, vel.x -= SPEED;

    Vector2 cursor = GetMousePosition();
    float dirAngle = atan2(cursor.y - center.y, cursor.x - center.x) * RAD2DEG;

    vel = Vector2Multiply(vel, (Vector2){FRICTION, FRICTION});
    pos = Vector2Add(pos, Vector2Scale(vel, GetFrameTime()));
    angle = dirAngle;

    camera.target = pos;

    // draw
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(camera);

    for (int i = 0; i < mobs_s; i++) {
      Vector2* mob = &mobs[i];

      Vector2 direction = Vector2Subtract(pos, *mob);
      Vector2 normalizedDirection = Vector2Normalize(direction);
      Vector2 mobVel = {normalizedDirection.x * MOBS_SPEED, normalizedDirection.y * MOBS_SPEED};

      mob->x += mobVel.x;
      mob->y += mobVel.y;

      DrawRectanglePro(
        (Rectangle){mob->x, mob->y, SIZE, SIZE, BLACK}, (Vector2){SIZE / 2.0f, SIZE / 2.0f}, 0, GRAY
      );
    }

    DrawRectanglePro(
      (Rectangle){pos.x, pos.y, SIZE, SIZE, BLACK}, (Vector2){SIZE / 2.0f, SIZE / 2.0f}, angle, RED
    );

    EndMode2D();

    // UI
    DrawFPS(10, 10);

    char mobsCountText[20];
    sprintf(mobsCountText, "%d", mobs_s);

    Rectangle bord = {10, 30, 200, 40};
    DrawRectangleRec(bord, GREEN);
    DrawText("SPRITES:", 20, 40, 20, WHITE);
    DrawText(mobsCountText, 120, 40, 20, WHITE);

    Rectangle button = {10, 70, 130, 40};
    DrawRectangleRec(button, GREEN);
    DrawText("INCREASE", 20, 80, 20, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(0)) {
      printf("pressed\n");
      mobs_s += 10000;
      mobs = (Vector2*)realloc(mobs, mobs_s * sizeof(Vector2));

      for (int i = 0; i < mobs_s; i++)
        mobs[i] = (Vector2
        ){GetRandomValue(-MOBS_RADIUS, MOBS_RADIUS), GetRandomValue(-MOBS_RADIUS, MOBS_RADIUS)};
    };

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
