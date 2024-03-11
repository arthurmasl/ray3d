#include "main.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

const int screenWidth = 504;
const int screenHeight = 1052;

Vector2* createMobs(int count) {
  Vector2* mobs;

  mobs = (Vector2*)malloc(count * sizeof(Vector2));

  for (int i = 0; i < count; i++)
    mobs[i] = (Vector2
    ){GetRandomValue(-MOBS_RADIUS, MOBS_RADIUS), GetRandomValue(-MOBS_RADIUS, MOBS_RADIUS)};

  return mobs;
}

void updateMobsCount(int* mobsCount, Vector2** mobs, int addCount) {
  *mobsCount += addCount;
  *mobs = (Vector2*)realloc(*mobs, *mobsCount * sizeof(Vector2));

  for (int i = 0; i < *mobsCount; i++)
    (*mobs)[i] = (Vector2
    ){GetRandomValue(-MOBS_RADIUS, MOBS_RADIUS), GetRandomValue(-MOBS_RADIUS, MOBS_RADIUS)};
}

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "ray3d");
  SetWindowPosition(1176, 0);
  SetTargetFPS(60);

  const Vector2 center = {screenWidth / 2.0f, screenHeight / 2.0f};

  int mobsCount = MOBS_COUNT;
  Vector2* mobs = createMobs(mobsCount);

  int playerSize = SIZE;
  bool paused = true;

  Camera2D camera = {};
  camera.offset = center;
  camera.zoom = 1.2f;

  while (!WindowShouldClose()) {
    // controls
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) state = WALK_U, dir = U, vel.y -= SPEED;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) state = WALK_D, dir = D, vel.y += SPEED;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) state = WALK_R, dir = R, vel.x += SPEED;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) state = WALK_L, dir = L, vel.x -= SPEED;

    // player
    Vector2 cursor = GetMousePosition();
    float dirAngle = atan2(cursor.y - center.y, cursor.x - center.x) * RAD2DEG;

    vel = Vector2Multiply(vel, (Vector2){FRICTION, FRICTION});
    pos = Vector2Add(pos, Vector2Scale(vel, GetFrameTime()));
    // angle = dirAngle;

    camera.target = pos;

    // draw
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(camera);

    // draw player
    Rectangle playerRectangle = (Rectangle){pos.x, pos.y, playerSize, playerSize};
    DrawRectanglePro(playerRectangle, (Vector2){playerSize / 2.0f, playerSize / 2.0f}, angle, RED);

    // player debug
    Rectangle playerCollisionBox = (Rectangle
    ){pos.x - playerSize / 2.0f, pos.y - playerSize / 2.0f, playerSize, playerSize};
    DrawRectangleLinesEx(playerCollisionBox, 2, GREEN);

    // enemy
    for (int i = 0; i < mobsCount; i++) {
      Vector2* mob = &mobs[i];

      if (!paused) {
        Vector2 direction = Vector2Subtract(pos, *mob);
        Vector2 normalizedDirection = Vector2Normalize(direction);
        Vector2 mobVel = {normalizedDirection.x * MOBS_SPEED, normalizedDirection.y * MOBS_SPEED};

        mob->x += mobVel.x;
        mob->y += mobVel.y;
      }

      Rectangle enemyCollisionBox = (Rectangle
      ){mob->x - SIZE / 2.0f, mob->y - SIZE / 2.0f, SIZE, SIZE};

      // collision
      if (CheckCollisionRecs(enemyCollisionBox, playerCollisionBox)) {
        mob->x = GetRandomValue(-MOBS_RADIUS * 10, MOBS_RADIUS * 10);
        mob->y = GetRandomValue(-MOBS_RADIUS * 10, MOBS_RADIUS * 10);
        playerSize += 1;
      }

      DrawRectangleRec(enemyCollisionBox, GRAY);
      DrawRectangleLinesEx(enemyCollisionBox, 2, GREEN);
    }

    EndMode2D();

    // UI
    DrawFPS(10, 10);

    char mobsCountText[20];
    sprintf(mobsCountText, "%d", mobsCount);

    Rectangle bord = {10, 30, 200, 40};
    DrawRectangleRec(bord, GREEN);
    DrawText("SPRITES:", 20, 40, 20, WHITE);
    DrawText(mobsCountText, 120, 40, 20, WHITE);

    // keys
    if (IsKeyPressed(KEY_I)) updateMobsCount(&mobsCount, &mobs, 10000);
    if (IsKeyPressed(KEY_O)) updateMobsCount(&mobsCount, &mobs, -10000);
    if (IsKeyPressed(KEY_P)) paused = !paused;
    if (IsKeyPressed(KEY_J)) camera.zoom += 0.1f;
    if (IsKeyPressed(KEY_K)) camera.zoom -= 0.1f;

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
