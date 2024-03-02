#include "main.h"
#include <raylib.h>
#include <raymath.h>

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "ray3d");
  SetWindowPosition(1176, 0);
  SetTargetFPS(60);

  const Vector2 center = {screenWidth / 2.0f, screenHeight / 2.0f};

  for (int i = 0; i < MOBS_COUNT; i++)
    mobs[i] = (Vector2
    ){GetRandomValue(-MOBS_RADIUS, MOBS_RADIUS), GetRandomValue(-MOBS_RADIUS, MOBS_RADIUS)};

  Camera2D camera = {};
  camera.offset = center;
  camera.zoom = 0.5f;

  while (!WindowShouldClose()) {
    // update
    if (IsKeyDown(KEY_W)) state = WALK_U, dir = U, vel.y -= SPEED;
    if (IsKeyDown(KEY_S)) state = WALK_D, dir = D, vel.y += SPEED;
    if (IsKeyDown(KEY_D)) state = WALK_R, dir = R, vel.x += SPEED;
    if (IsKeyDown(KEY_A)) state = WALK_L, dir = L, vel.x -= SPEED;

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

    for (int i = 0; i < MOBS_COUNT; i++) {
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
      (Rectangle){pos.x, pos.y, SIZE, SIZE, BLACK}, (Vector2){SIZE / 2.0f, SIZE / 2.0f}, angle,
      BLACK
    );

    EndMode2D();

    // UI
    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
