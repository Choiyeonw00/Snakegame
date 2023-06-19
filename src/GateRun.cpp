#include <cstdlib>
#include <ctime>
#include <string>
#include "Snake.h"
#include "GateRun.h"
#include "GameScene.h"

extern MapRun *mapManager;
extern Snake *snake;

Position nextPos;

Position GateRun::getRandPosition() {
    Position temp;
    while (1) {
        int x = rand() % (WIDTH);
        int y = rand() % (HEIGHT);
        if (mapManager->data[y][x] == '1') {
            temp.x = x;
            temp.y = y;
            break;
        }
    }
    return temp;
}

GateRun::GateRun() {
}

GateRun::~GateRun() {
}

void GateRun::Render() {
}

Position GateRun::GetNextGate() {
    int target = 9;

    for (int i = 0; i < data.size(); i++) {
        if (data[i].x == snake->GetHead().x && data[i].y == snake->GetHead().y) {
            target = i;
        }
    }

    if (target == 0) {
        target = 1;
    } else {
        target = 0;
    }

    int tempPosX = data[target].x;
    int tempPosY = data[target].y;

    bool possibleLeft = false;
    bool possibleRight = false;
    bool possibleUp = false;
    bool possibleDown = false;

    char direction = snake->direction;

    if (mapManager->data[tempPosY + 1][tempPosX] == '0') {
        possibleDown = true;
    }
    if (mapManager->data[tempPosY][tempPosX + 1] == '0') {
        possibleRight = true;
    }
    if (mapManager->data[tempPosY - 1][tempPosX] == '0') {
        possibleUp = true;
    }
    if (mapManager->data[tempPosY][tempPosX - 1] == '0') {
        possibleLeft = true;
    }

    //진입방향과 일치하는 경우
    if (possibleLeft && direction == 'l') {
        tempPosX -= 1;
    } else if (possibleRight && direction == 'r') {
        tempPosX += 1;
    } else if (possibleUp && direction == 'u') {
        tempPosY -= 1;
    } else if (possibleDown && direction == 'd') {
        tempPosY += 1;
    } else if (direction == 'u' || direction == 'd') {//snake의 direction을 바꿔야하는 경우
        if (possibleLeft) {
            tempPosX -= 1;
            snake->SetDirection('l');
        } else if (possibleRight) {
            tempPosX += 1;
            snake->SetDirection('r');
        } else if (possibleUp) {
            tempPosY -= 1;
            snake->SetDirection('u');
        } else if (possibleDown) {
            tempPosY += 1;
            snake->SetDirection('d');
        }
    } else if (direction == 'l' || direction == 'r') {
        if (possibleDown) {
            tempPosY += 1;
            snake->SetDirection('d');
        } else if (possibleUp) {
            tempPosY -= 1;
            snake->SetDirection('u');
        } else if (possibleLeft) {
            tempPosX -= 1;
            snake->SetDirection('l');
        } else if (possibleRight) {
            tempPosX += 1;
            snake->SetDirection('r');
        }
    }

    nextPos.x = tempPosX;
    nextPos.y = tempPosY;

    return nextPos;
}

void GateRun::Update(float eTime) {
    int *temp = new int[data.size()];
    vector<Position>::iterator iter;

    if (isEntering) {
        //꼬리가 다음 게이트 지시 위치로 갔는가
        Position tail = snake->GetTail();
        if (nextPos.x == tail.x && nextPos.y == tail.y) {
            isRemove = true;
        }

        //게이트를 삭제해야한다면 바로 map에 반영하기
        if (isRemove == true) {
            for (int i = data.size() - 1; i >= 0; i--) {
                mapManager->PatchData(data[i].y, data[i].x, '1');
                data.pop_back();
            }
            isCreated = false;
            isRemove = false;
            isEntering = false;
            lastDropTime = eTime;
        }
    } else if (isCreated == true && isEntering == false && eTime - lastDropTime > DROP_GATE_INTERVAL) {
        for (int i = data.size() - 1; i >= 0; i--) {
            mapManager->PatchData(data[i].y, data[i].x, '1');
            data.pop_back();
        }
        isCreated = false;
    }

    PushData();

    //Gate drop
    if (eTime - lastDropTime > DROP_GATE_INTERVAL && isEntering == false && snake->entire.size() >= 4) {
        if (isCreated == false) {
            PositionGate();
            lastDropTime = eTime;
            isCreated = true;
        }
    }

    delete[] temp;
}

void GateRun::PositionGate() {
    Position temp = getRandPosition();
    data.push_back(temp);
    PushData();
    temp = getRandPosition();
    data.push_back(temp);
    PushData();
}

void GateRun::PushData() {
    for (int32 i = 0; i < data.size(); i++) {
        mapManager->PatchData(data[i].y, data[i].x, '7');
    }
}