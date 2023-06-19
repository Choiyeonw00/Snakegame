#pragma once
#include "IObject.h"

class Stage : public IObject {
public:
	int nowStage;
	bool clear;

	//mission 배열 (뱀 길이, grow 아이템, poison 아이템, gate 아이템)
	int mission[4][4] = {{7, 3, 1, 1},
						{7, 4, 2, 1},
						{7, 5, 3, 2},
						{7, 5 ,2, 2},};

	Stage();
	~Stage();

	int getNowStage() { return nowStage; }

	int *getNowMission() { return mission[nowStage]; }

	void setNowStage(int nowStage) { this->nowStage = nowStage; }

	void Update(float eTime);

	void Render();
};