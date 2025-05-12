#pragma once

#include "raylib.h"
#include <functional>
#include "utils.hpp"
#include "vector"

enum CollisionBoxEnums {
    STATIC,
    ENTITY,
    ENEMY
};

struct CollisionBox {
    f32 x,y,h,w;
    CollisionBoxEnums type;
    Rectangle getRectangle();
};

void LoggCollisionBox(CollisionBox var);
std::vector<CollisionBox>* GetCollision();
