#include "GameStartScene.h"
#include "GameScene.h"
#include "Function.h"
#include <fstream>
#include <ncurses.h>

Stage *stage;

extern int currentWidth;
extern int currentHeight;

GameStartScene::GameStartScene() {
    stage = new Stage();
}

GameStartScene::~GameStartScene() {}

void GameStartScene::Update(float eTime) {
    char answer;
    int temp;
    do {
        answer = IsUserReady();
        if (answer == 'n') {
            exit(0);
        }
        temp = (int)answer - 49;
    } while (temp < 0 || temp > 3);

    stage->setNowStage((int)answer - 49);

    ChangeScene(new GameScene());
}

void GameStartScene::Render() {}

void GameStartScene::ClearCentre(float x, float y) {
    clear(); // clear the screen if the game is played for the 2nd time
    initscr();
    noecho();
    getmaxyx(stdscr, maxheight, maxwidth);

    //myFunction에 있는 변수
    getmaxyx(stdscr, currentHeight, currentWidth);

    move((maxheight / y), (maxwidth / x));
}

// receive user confirmation
int GameStartScene::UserInput() {
    int UserInput = getch();
    refresh();
    endwin();
    clear();

    return UserInput;
}

void GameStartScene::Load() {
    std::ifstream readFile;
    string src = "scene/GameStartScene.txt";

    readFile.open(src);
    int height = 0;

    while (!readFile.eof()) {
        char temp[120];
        readFile.getline(temp, 120);

        for (int width = 0; width < 62; width++) {
            if (temp[width] == '-') {
                move(height, width);
                addch('-');
            } else if (temp[width] == '0') {
                move(height, width);
                addch(char(219));
            } else if (temp[width] == ' ') {
                move(height, width);
                addch(' ');
            }
        }
        height++;
    }
}

// print start menu
int GameStartScene::IsUserReady() {
    ClearCentre(3, 2.5);

    Load();

    move(25, 13);
    printw("Press 1 or 2 or 3 or 4 to start");

    move(30, 16);
    printw("20223111 gh & 20223153 yw !!");
    return UserInput();
}