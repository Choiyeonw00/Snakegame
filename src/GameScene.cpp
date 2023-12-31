#include "GameScene.h"
#include "GameStartScene.h"
#include "Snake.h"
#include "ItemRun.h"
#include "Function.h"
#include "IObject.h"
#include "Player.h"
#include "MapRun.h"
#include "Position.h"

#include <unistd.h>
#include <vector>
#include <ncurses.h>
using namespace std;
extern Stage *stage;
// Unreal coding standards
using int32 = int;

MapRun *mapManager;
Player *player;
Snake *snake;

GameScene::GameScene() {
  srand(time(NULL));

  player = new Player();

  //mapManager를 먼저 생성시켜줘야함
  mapManager = new MapRun();
  mapManager->Load();

  snake = new Snake();
  itemManager = new ItemRun();
  gateManager = new GateRun();

  format = new Format();

  InitGameWindow();
  refresh();
}

GameScene::~GameScene() {
  //delete mapManager;
  nodelay(stdscr, false);
  endwin();
}

// initialise the game window
void GameScene::InitGameWindow() {
  initscr(); // initialise the screen
  nodelay(stdscr, TRUE);
  keypad(stdscr, true);                  // initialise the keyboard: we can use arrows for directions
  noecho();                              // user input is not displayed on the screen
  curs_set(0);                           // cursor symbol is not not displayed on the screen (Linux)
  getmaxyx(stdscr, maxheight, maxwidth); // define dimensions of game window
  return;
}

void GameScene::ProcessCollision() {
  int y = snake->GetHead().y;
  int x = snake->GetHead().x;

  char temp = mapManager->data[y][x];

  // mvaddch(2, maxwidth / 5 * 4 + 4, mapManager->data[y][x]);

  if (temp == '1' || snake->entire.size() <= 4) {
    snake->isDied = true;
  } else if (temp == '5') {
    itemManager->DeleteCollisionData(y, x);
    player->growScore += 1;
    snake->Grow();
  } else if (temp == '6') {
    itemManager->DeleteCollisionData(y, x);
    player->poisonScore += 1;
    snake->Shrink();
  } else if (temp == '7') {
    Position nextGate = gateManager->GetNextGate();
    player->gateScore += 1;
    gateManager->isUsed = true;
    snake->SetHeadPos(nextGate.y, nextGate.x);
  } else if (temp == 'a') {
    itemManager->DeleteCollisionData(y, x);
    player->growScore += 3;
    // snake->Grow();
  }
}

bool isClear() {
  if (player->lengthScore >= stage->mission[stage->getNowStage()][0] && player->growScore >= stage->mission[stage->getNowStage()][1] && player->poisonScore >= stage->mission[stage->getNowStage()][2] && player->gateScore == stage->mission[stage->getNowStage()][3]) {
    return true;
  }
  return false;
}

void GameScene::Update(float eTime) {
  //여기에서 changeScene을 걸어준다.
  if (isClear()) {
    stage->nowStage++;
    ChangeScene(new GameScene());
  }

  player->SetLengthScore(snake->entire.size());
  player->SetTotalScore(stage->nowStage);

  snake->Update(eTime);
  if (snake->IsCollision()) {
    ProcessCollision();
  }
  if (snake->isDied) {
    ChangeScene(new GameOverScene());
  }
  snake->PushData();
  format->Update(eTime);
  itemManager->Update(eTime);
  gateManager->Update(eTime);
  //* float eTime test code *//
  // move((maxheight-2)/2,(maxwidth-5)/2);
  // printw("%f",eTime);
  usleep(160000);//150000
}

void GameScene::Render() {
  format->Render();

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      switch (mapManager->data[i][j])
      {
      case '0':
        mvaddch(i, j, ' ');
        break;
      case '1':
        mvaddch(i, j, '-');
        break;
      case '2':
        mvaddch(i, j, 'X');
        break;
      case '3':
        mvaddch(i, j, 'H');
        break;
      case '4':
        mvaddch(i, j, 'B');
        break;
      case '5':
        mvaddch(i, j, 'G');
        break;
      case '6':
        mvaddch(i, j, 'P');
        break;
      case '7':
        mvaddch(i, j, '?');
        break;
      case 'a':
        mvaddch(i, j, 'S');
        break;
      case '8':
        mvaddch(i, j, ' ');
      }
    }
  }

  refresh();
}