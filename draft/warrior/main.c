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

  Model warriorModel = LoadModel("resources/warrior/model.obj");
  Texture2D warriorTexture = LoadTexture("resources/warrior/texture.png");
  warriorModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = warriorTexture;

  Model stompModel = LoadModel("resources/stomp/model.obj");
  Texture2D stompTexture = LoadTexture("resources/stomp/texture.png");
  stompModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = stompTexture;

  Camera3D camera = {
    .position = (Vector3){10, 10, 10},
    .target = (Vector3){0, 0, 0},
    .up = (Vector3){0, 1, 0},
    .fovy = 45,
    .projection = CAMERA_PERSPECTIVE
  };
  DisableCursor();

  Vector3 warriorPos = {0.0f, 0.25f, 0};
  Vector3 stompPos = {0, 0, 0};
  BoundingBox bound = GetMeshBoundingBox(warriorModel.meshes[0]);

  warriorModel.transform = MatrixTranslate(0.1f, 0.0f, 0.0f);

  while (!WindowShouldClose()) {
    UpdateCamera(&camera, CAMERA_FREE);

    // draw
    BeginDrawing();
    ClearBackground((Color){76, 115, 25, 255});

    BeginMode3D(camera);

    // DrawGrid(10, 1.0f);
    DrawPlane((Vector3){0, -0.1f, 0}, (Vector2){10, 10}, (Color){98, 148, 34, 255});
    // DrawPlane((Vector3){0, -0.1f, 0}, (Vector2){10, 10}, GREEN);
    // DrawModel(warriorModel, warriorPos, 1.0f, WHITE);
    DrawModelEx(
      warriorModel, warriorPos, (Vector3){0, 0.1f, 0}, 60 * GetTime(), (Vector3){1, 1, 1}, WHITE
    );
    // DrawBoundingBox(bound, GREEN);

    DrawModel(stompModel, stompPos, 0.5f, WHITE);

    EndMode3D();

    // UI
    DrawFPS(10, 10);
    EndDrawing();
  }

  UnloadTexture(warriorTexture);
  UnloadModel(warriorModel);

  CloseWindow();
  return 0;
}
