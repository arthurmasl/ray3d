#include "main.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

const int screenWidth = 504;
const int screenHeight = 1052;
const Vector2 center = {screenWidth / 2.0f, screenHeight / 2.0f};

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "ray3d");
  SetWindowPosition(1176, 0);
  SetTargetFPS(60);

  Vector3 vel;

  Model warriorModel = LoadModel("resources/warrior/model.obj");
  Texture2D warriorTexture = LoadTexture("resources/warrior/texture.png");
  warriorModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = warriorTexture;

  Model stompModel = LoadModel("resources/stomp/model.obj");
  Texture2D stompTexture = LoadTexture("resources/stomp/texture.png");
  stompModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = stompTexture;

  Model orcModel = LoadModel("resources/orc/orc.obj");
  Texture2D orcTexture = LoadTexture("resources/orc/orc.texture.png");
  orcModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = orcTexture;

  int frameCounter = 0;
  int animsCount = 0;
  ModelAnimation* orcAnimation = LoadModelAnimations("resources/orc/orc2.glb", &animsCount);

  Camera3D camera = {
    .position = (Vector3){0, 7, 5},
    .target = (Vector3){0, 0, 0},
    .up = (Vector3){0, 1, 0},
    .fovy = 60,
    .projection = CAMERA_PERSPECTIVE
  };
  // DisableCursor();

  Vector3 warriorPos = {0.0f, 0.0f, 0.0f};
  Vector3 stompPos = {1, 0, 0};
  BoundingBox bound = GetMeshBoundingBox(warriorModel.meshes[0]);

  Vector3 pos = {0.0f, 0.0f, 1.0f};

  Vector2 cursor = GetMousePosition();

  warriorModel.transform = MatrixTranslate(0.1f, 0.0f, 0.0f);

  while (!WindowShouldClose()) {
    // UpdateCamera(&camera, CAMERA_FREE);

    // controls
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) vel.z -= SPEED;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) vel.z += SPEED;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) vel.x += SPEED;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) vel.x -= SPEED;

    // if (IsKeyDown(KEY_SPACE)) {
    //   frameCounter++;
    //   UpdateModelAnimation(orcModel, orcAnimation[0], frameCounter);
    //   if (frameCounter >= orcAnimation[0].frameCount) frameCounter = 0;
    // }

    camera.target = pos;

    vel = Vector3Multiply(vel, (Vector3){FRICTION, FRICTION, FRICTION});
    pos = Vector3Add(pos, Vector3Scale(vel, GetFrameTime()));

    Vector2 mousePosition = GetMousePosition();
    Vector3 direction = Vector3Subtract(
      (Vector3){mousePosition.x, 0, mousePosition.y}, (Vector3){center.x, 0, center.y}
    );
    float angle = atan2(direction.x, direction.z) * RAD2DEG - 90;

    // draw
    BeginDrawing();
    ClearBackground((Color){76, 115, 25, 255});

    BeginMode3D(camera);

    // DrawGrid(10, 1.0f);
    DrawPlane((Vector3){0, -0.1f, 0}, (Vector2){20, 20}, (Color){98, 148, 34, 255});
    DrawModelEx(warriorModel, warriorPos, (Vector3){0, 0.1f, 0}, -90, (Vector3){1, 1, 1}, WHITE);
    // DrawBoundingBox(bound, GREEN);

    DrawModelEx(orcModel, pos, (Vector3){0, 0.1f, 0}, angle, (Vector3){1, 1, 1}, WHITE);

    DrawModel(stompModel, stompPos, 0.5f, WHITE);

    EndMode3D();

    // UI
    DrawFPS(10, 10);
    EndDrawing();
  }

  UnloadTexture(warriorTexture);
  UnloadModel(warriorModel);
  UnloadModelAnimations(orcAnimation, animsCount);

  CloseWindow();
  return 0;
}
