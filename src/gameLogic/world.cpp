#include "gameLogic/world.hpp"
#include "gameLogic/collision.hpp"
#include "raylib.h"
#include "fstream"
#include "iostream"
#include <array>

#define MAXTILESIZE 1000

void World::ReedEnum(std::string line) {
    int pos = 0;
    while (line[pos] != '{') pos++;
    for (int i=0; i<12; i++) pos++;

    int nr = 0;
    while (line[pos] >= '0' && line[pos] <= '9') {
        nr*= 10;
        nr += line[pos++] - '0';
    }

    for (int i=0; i<11; i++) pos++;
    std::string rez = "";
    while (line[pos] != '\"') {
        rez += line[pos];
        pos++;
    }

    TileEnums[nr] = rez;
}

void World::ReedData(std::string line) {
    std::array<int,8> numbers;
    int nr = 0,p = 0,isNumber = false;
    for (auto x:line) {
        if (x >= '0' && x <= '9') {
            nr *= 10;
            nr += x - '0';
            isNumber = true;
        }
        else {
            if (isNumber) numbers[p++] = nr;
            isNumber = false;
            nr = 0;
        }
    }
    if (TileEnums[numbers[5]] == "coll") LoggCollisionBox({(f32)numbers[0],(f32)numbers[1],(f32)tileSize,(f32)tileSize});
    tiles.push_back({{(f32)numbers[2],(f32)numbers[3],(f32)tileSize,(f32)tileSize},{(f32)numbers[0],(f32)numbers[1]}});
}

void World::Load(std::string path) {
    std::ifstream in(path);
    atlas = LoadTexture(RESOURCE_PATH "atlas.png");
    tiles.reserve(MAXTILESIZE);

    bool reedEnum = false;
    bool reedData = false;

    std::string line = "";
    while (getline(in,line)) {
        if (line == "			],") reedEnum = false;
        if (line == "					],") reedData = false;

        if (reedEnum == true) ReedEnum(line);
        if (reedData == true) ReedData(line);

        if (line == "			\"customData\": [") reedEnum = true;
        if (line == "					\"gridTiles\": [") reedData = true;
    }
}

void World::Draw() {
    for (auto x:tiles) {
        DrawTextureRec(atlas, x.positionInAtlas, x.position, WHITE);
    }
}
