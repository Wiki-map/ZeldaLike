#pragma once

#include "gameLogic/player.hpp"
#include "raylib.h"
#include "utils.hpp"
#include "gameLogic/world.hpp"

struct Game {
private:
    Player player;
    Camera2D camera;
    i32 RenderHeight = 180;
    i32 RenderWidth = 320;
    World world;

    void Init();
    void Update();
    void Draw();
public:
    void Run();
};
