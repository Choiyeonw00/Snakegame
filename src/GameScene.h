#pragma once
#include "IScene.h"
#include "GameStartScene.h"
#include "Stage.h"
#include "Snake.h"
#include "ItemRun.h"
#include "GateRun.h"
#include "Format.h"
#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>

#include "MapRun.h"

using int32 = int;

class GameScene : public IScene {
public:
	int32 score;
	int32 maxwidth, maxheight;

	char edgechar;

	GameScene();
	~GameScene();

	ItemRun *itemManager;
	GateRun *gateManager;

	Format *format;

	bool isChangeScene;

	void InitGameWindow();
	void Update(float eTime);
	void Render();
	void ProcessCollision();
};