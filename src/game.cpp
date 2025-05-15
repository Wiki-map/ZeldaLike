#include "game.hpp"
#include "raylib.h"
#include "rlImGui.h"

void Game::Init() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 800,"hi");
    SetTargetFPS(60);

    player = Player(300,300);

    camera = { {0,0}, {0,0}, 0, 0 };
    rlImGuiSetup(true);

    world.Load(RESOURCE_PATH "world.ldtk");
}

static void CameraUpdate(Camera2D &camera,Rectangle target,i32 RenderHeight,i32 RenderWidth) {
    f32 zoom;
    if (GetScreenHeight() > GetScreenWidth()) {
        zoom = (f32)GetScreenHeight()/(f32)RenderHeight;
    }
    else {
        zoom = (f32)GetScreenWidth()/(f32)RenderWidth;
    }
    camera.zoom = zoom;

    camera.target.x = (f32)target.x + (f32)target.width/2;
    camera.target.y = (f32)target.y + (f32)target.height/2;

    camera.offset.x = (f32)GetScreenWidth()/2;
    camera.offset.y = (f32)GetScreenHeight()/2;
}

void Game::Update() {
    if (IsKeyPressed(KEY_F11)) {
        SetWindowSize(GetMonitorWidth(0),GetMonitorHeight(0));
        ToggleFullscreen();
    }
    player.Update();
    CameraUpdate(camera,player.GetRectangle(),RenderHeight,RenderWidth);
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
        Update();
        BeginDrawing();
        Draw();
        EndDrawing();
    }
}
