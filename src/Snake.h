#pragma once
#include <ncurses.h>
#include <vector>
#include "Position.h"
#include "Function.h"
#include "GameOverScene.h"
#include "IScene.h"
#include "IObject.h"

using int32 = int;

class Snake : public IObject {
public:
	Snake();
	~Snake();

	std::vector<Position> entire;
	bool isDied = false;
	char partchar, direction;
	int choiceCount;
	int select;
	int maxwidth, maxheight;
	bool isGrow = false;
	bool isShrink = false;

	void Update(float eTime);

	void PushData();

	void SetDirection(char ch);

	bool IsCollision();

	void Grow();
	void Shrink();

	Position GetHead();
	Position GetTail();

	void SetHeadPos(int y, int x);

	void CutTail();

	void Render();
	void initBody();

	void EatItem(bool fruit, bool poison);
};