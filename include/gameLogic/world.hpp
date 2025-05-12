#pragma once

#include <vector>
#include "raylib.h"
#include "utils.hpp"
#include "string"
#include "map"

struct Tile {
    Rectangle positionInAtlas;
    vec2 position;
};

struct World {
private:
    const int tileSize = 16;
    Texture2D atlas;
    std::vector<Tile> tiles;
    std::map<int,std::string> TileEnums;
    void ReedEnum(std::string line);
    void ReedData(std::string line);
public:
    void Load(std::string path);
    void Draw();
};
