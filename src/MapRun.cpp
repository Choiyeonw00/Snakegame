#include "MapRun.h"
#include "Function.h"
#include <vector>
#include <fstream>

extern Stage *stage;

MapRun::MapRun() {} // load txt file. named stageName. ex) 1.txt 2.txt 3.txt 4.txt

void MapRun::Load() {

    std::ifstream readFile;
    string src = "map/map" + std::to_string(stage->getNowStage() + 1) + ".txt";

    readFile.open(src);
    int height = 0;

    while (!readFile.eof()) {
        char temp[120];
        readFile.getline(temp, 120);

        for (int i = 0; i < WIDTH; i++) {
            data[height][i] = temp[i];
        }
        height++;
    }
}

void *MapRun::GetData() {
    return data;
}

void MapRun::PatchData(int y, int x, char patchData) {
    data[y][x] = patchData;
}

MapRun::~MapRun(){}

void MapRun::Render() {}

void MapRun::Update(float eTime) {}