#include "gameLogic/player.hpp"
#include "gameLogic/collision.hpp"
#include "raylib.h"
#include "cstdlib"
#include "imgui.h"

Player::Player(int x,int y) {
    position = {(float)x,(float)y};
    height = 8;
    width = 8;
}

void Player::Update() {
    vec2 movement = {0,0};

    if (IsKeyDown(KEY_W)) movement.y += -1;
    if (IsKeyDown(KEY_S)) movement.y += 1;

    if (IsKeyDown(KEY_A)) movement.x += -1;
    if (IsKeyDown(KEY_D)) movement.x += 1;

    if (std::abs(movement.x) == 1 && std::abs(movement.y) == 1) {
        movement.x /= 1.41421356;
        movement.x /= 1.41421356;
    }

    position.x += movement.x * SPEED;
    position.y += movement.y * SPEED;

    for (auto x:*GetCollision()) {
        if (CheckCollisionRecs(GetRectangle(), x.getRectangle())) {
            OnCollision(x);
        }
    }
}

void Player::Draw() {
    DrawRectangle(position.x,position.y,width,height,WHITE);
}

Rectangle Player::GetRectangle() {
    Rectangle rez = {position.x,position.y,(f32)width,(f32)height};
    return rez;
}

void Player::DrawImguiBox() {
    ImGui::Begin("Player");

    ImGui::DragFloat("Speed", &SPEED);
    ImGui::DragFloat("size",&height);
    width = height;

    ImGui::End();
}

void Player::OnCollision(CollisionBox x) {
    f32 x1 = position.x,y1 = position.y;
    f32 w1 = width, h1 = height;

    f32 x2 = x.x,y2 = x.y;
    f32 h2 = x.h, w2 = x.w;

    f32 left = x1 + w1 - x2;
    f32 right = x2 + w2 - x1;
    f32 top = y1 + h1 - y2;
    f32 bottom = y2 + h2 - y1;

    if (left < right && left < top && left < bottom) {
        position.x = x2 - w1;
    }
    else if (right < left && right < top && right < bottom) {
        position.x = x2 + w2;
    }
    else if (top < left && top < right && top < bottom) {
        position.y = y2 - h1;
    }
    else if (bottom < left && bottom < right && bottom < top) {
        position.y = y2 + h2;
    }
}
