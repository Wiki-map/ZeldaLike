#pragma once

#include "gameLogic/collision.hpp"
#include "utils.hpp"

struct Player {
    vec2 position;
    f32 height,width;
    f32 SPEED = 2;

    Player() = default;
    Player(int x,int y);
    void Update();
    void Draw();
    void DrawImguiBox();

    Rectangle GetRectangle();
    void OnCollision(CollisionBox x);
};
