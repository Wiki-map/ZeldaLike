#include "gameLogic/collision.hpp"
#include "vector"
#include "iostream"

std::vector<CollisionBox> CollisionBoxList;

Rectangle CollisionBox::getRectangle() {
    return {x,y,w,h};
}

void LoggCollisionBox(CollisionBox var) {
    std::cout<<"[INFO]: "<<"Logged CollisionBox at: {" << var.x<<"," << var.y<<"}\n";
    CollisionBoxList.push_back(var);
}

std::vector<CollisionBox>* GetCollision() {
    return &CollisionBoxList;
}
