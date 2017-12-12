#pragma once
#include <iostream>
#include <string>
using namespace std;

const int BOARD_WIDTH = 15;
const int BOARD_HEIGHT = 10;
const int SHIP_TYPES = 5;

const unsigned char isWATER = 247; //ASCII Character Code
const char isHIT = 'X';
const char isSHIP = 'S';
const char isMISS = '0';

struct POINT {
	//A location on the grid defined
	//by X(horizontal) Y(vertical) coordinates
	int X;
	int Y;
};

struct SHIP {
	//Ship name
	string name;
	//Total points on the grid
	int length;
	//Coordinates of those points
	POINT onGrid[5]; //0-4 max length of biggest ship
					 //Whether or not those points are a "hit"
	bool hitFlag[5];
};

struct PLAYER {
	char grid[BOARD_WIDTH][BOARD_HEIGHT];
}; //Ignore player 0, just using player's 1 & 2

enum DIRECTION { HORIZONTAL, VERTICAL };

struct PLACESHIPS {
	DIRECTION direction;
	SHIP shipType;
};


//Functions
void LoadShips();
void ResetBoard();
void DrawBoard(int);
PLACESHIPS UserInputShipPlacement();
bool UserInputAttack(int&, int&, int);
bool GameOverCheck(int);
int TurnCounter(int);

extern SHIP ship[];
extern PLAYER player[];
extern bool gameRunning;