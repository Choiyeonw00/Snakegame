#pragma once
#include "IScene.h"
#include "Stage.h"
#include "Function.h"
#include "GameScene.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>

class GameStartScene : public IScene {
public:
	int maxwidth, maxheight;

	GameStartScene();
	~GameStartScene();

	void Update(float eTime);
	void Render();

	void Load();
	void ClearCentre(float x, float y);
	int UserInput();
	int IsUserReady();

	// clear the screen and centre the cursor
};