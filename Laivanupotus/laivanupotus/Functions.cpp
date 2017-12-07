#include "Header.h"

PLACESHIPS UserInputShipPlacement()
{
	int d, x, y;
	PLACESHIPS tmp;
	//Using this as a bad return
	tmp.shipType.onGrid[0].X = -1;
	//Get 3 integers from user
	cin >> d >> x >> y;
	if (d != 0 && d != 1) return tmp;
	if (x<0 || x >= BOARD_WIDTH) return tmp;
	if (y<0 || y >= BOARD_HEIGHT) return tmp;
	//Good data
	tmp.direction = (DIRECTION)d;
	tmp.shipType.onGrid[0].X = x;
	tmp.shipType.onGrid[0].Y = y;
	return tmp;
}

bool UserInputAttack(int& x, int& y, int theplayer)
{
	cout << "\nPLAYER " << theplayer << ", ENTER COORDINATES TO ATTACK: ";
	bool goodInput = false;
	cin >> x >> y;
	if (x<0 || x >= BOARD_WIDTH) return goodInput;
	if (y<0 || y >= BOARD_HEIGHT) return goodInput;
	goodInput = true;
	return goodInput;
}

void LoadShips()
{
	//Sets the default data for the ships
	//we plan to include in the game
	//IMPORTANT!! > MUST MATCH SHIP_TYPES -Default=5 (0-4)
	ship[0].name = "Cruiser"; ship[0].length = 2;
	ship[1].name = "Frigate"; ship[1].length = 3;
	ship[2].name = "Submarine"; ship[2].length = 3;
	ship[3].name = "Escort"; ship[3].length = 4;
	ship[4].name = "Battleship"; ship[4].length = 5;
}
void ResetBoard()
{
	//Loop through each player
	for (int plyr = 1; plyr<3; ++plyr)
	{
		//For each grid point, set contents to 'water'
		for (int w = 0; w<BOARD_WIDTH; ++w) {
			for (int h = 0; h<BOARD_HEIGHT; ++h) {
				player[plyr].grid[w][h] = isWATER;
			}
		}
		//Loop back to next player
	}
}

void DrawBoard(int thisPlayer)
{
	//Draws the board for a player (thisPlayer)
	cout << "PLAYER " << thisPlayer << "'s GAME BOARD\n";
	cout << "----------------------\n";

	//Loop through top row (board_width) and number columns
	cout << "   ";
	for (int w = 0; w<BOARD_WIDTH; ++w) {
		if (w < 10)
			//Numbers only 1 character long, add two spaces after
			cout << w << "  ";
		else if (w >= 10)
			//Numbers 2 characters long, add only 1 space after
			cout << w << " ";
	}
	cout << "\n";

	//Loop through each grid point and display to console
	for (int h = 0; h<BOARD_HEIGHT; ++h) {
		for (int w = 0; w<BOARD_WIDTH; ++w) {

			//If this is the FIRST (left) grid point, number the grid first
			if (w == 0) cout << h << " ";
			//If h was 1 character long, add an extra space to keep numbers lined up
			if (w<10 && w == 0) cout << " ";
			//Display contents of this grid (if game isn't running yet, we are placing ships
			//so display the ships
			if (gameRunning == false) cout << player[thisPlayer].grid[w][h] << "  ";
			//Don't show ships, BUT show damage if it's hit
			if (gameRunning == true && player[thisPlayer].grid[w][h] != isSHIP)
			{
				cout << player[thisPlayer].grid[w][h] << "  ";
			}
			else if (gameRunning == true && player[thisPlayer].grid[w][h] == isSHIP)
			{
				cout << isWATER << "  ";
			}
			//If we have reached the border.. line feed
			if (w == BOARD_WIDTH - 1) cout << "\n";
		}
	}
}

bool GameOverCheck(int enemyPLAYER)
{
	bool winner = true;
	//Loop through enemy board
	for (int w = 0; w<BOARD_WIDTH; ++w) {
		for (int h = 0; h<BOARD_HEIGHT; ++h) {
			//If any ships remain, game is NOT over
			if (player[enemyPLAYER].grid[w][h] == isSHIP)
			{
				winner = false;
				return winner;
			}
		}
	}
	//If we get here, somebody won, game over!
	return winner;
}