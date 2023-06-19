#pragma once
#include "IObject.h"
#include "Position.h"
#include "Function.h"
#include "Snake.h"
#include "IScene.h"
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <string>
#include <ctime>

class MapRun : public IObject {
public:
    char data[HEIGHT][WIDTH];

    float lastDropTime = 0;

    MapRun();
    ~MapRun();

    void Render();
    void Update(float eTime);

    void *GetData();

    void PatchData(int y, int x, char patchData);

    void Print();
    void Load();
};