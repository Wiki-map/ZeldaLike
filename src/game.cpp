#include "game.hpp"
#include "raylib.h"
#include "rlImGui.h"

void Game::Init() {
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(RenderWidth*6, RenderHeight*6,"hi");
    SetTargetFPS(60);

    player = Player(300,300);

    camera = { {0,0}, {0,0}, 0, 0 };
    rlImGuiSetup(true);

    world.Load(RESOURCE_PATH "world.ldtk");
}

static void CameraUpdate(Camera2D &camera,Rectangle target,i32 RenderWidth) {
    f32 zoom = (f32)GetScreenWidth()/(f32)RenderWidth;
    camera.zoom = zoom;

    camera.target.x = (f32)target.x + (f32)target.width/2;
    camera.target.y = (f32)target.y + (f32)target.height/2;

    camera.offset.x = (f32)GetScreenWidth()/2;
    camera.offset.y = (f32)GetScreenHeight()/2;
}

void Game::Update(float deltaTime) {
    player.Update();
    CameraUpdate(camera,player.GetRectangle(),RenderWidth);
}

void Game::Draw() {
    ClearBackground(SKYBLUE);

    BeginMode2D(camera);
    {
        world.Draw();
        player.Draw();
    }
    EndMode2D();

    rlImGuiBegin();
    {
        player.DrawImguiBox();
    }
    rlImGuiEnd();
}

void Game::Run() {
    Init();
    while (!WindowShouldClose()) {
        Update(GetFrameTime());
        BeginDrawing();
        Draw();
        EndDrawing();
    }
}
