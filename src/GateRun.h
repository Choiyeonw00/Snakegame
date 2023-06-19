#pragma once
#include "IObject.h"
#include "Position.h"
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <string>
#include <ctime>

class GateRun : public IObject {
public:
    std::vector<Position> data;
    bool isUsed = true;
    bool isRemove = false;
    bool isCreated = false;
    bool isEntering = false;
    float lastDropTime = 0;

    GateRun();
    ~GateRun();

    Position getRandPosition();

    void Render();
    Position GetNextGate();
    void Update(float eTime);
    void PositionGate();
    void DeleteCollisionData(int y, int x);

    void PushData();
};