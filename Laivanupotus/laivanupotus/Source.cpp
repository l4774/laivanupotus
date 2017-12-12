#include "Header.h"

SHIP ship[SHIP_TYPES];
PLAYER player[3];
bool gameRunning = false;

int main()
{
	LoadShips();
	ResetBoard();

	//"PLACE SHIPS" phase of game
	//Loop through each player... 
	for (int aplyr = 1; aplyr<3; ++aplyr)
	{
		//Loop through each ship type to place
		for (int thisShip = 0; thisShip<SHIP_TYPES; ++thisShip)
		{
			//Display gameboard for player
			system("cls");
			DrawBoard(aplyr);
			//Give instructions
			cout << "\n";
			cout << "INSTRUCTIONS (Player " << aplyr << ")\n\n";
			cout << "You are about to place your ships.  Format should be:\n";
			cout << "Facing (0:Horizontal,1:Vertical), X (top-row) coords, Y (left-side) coords\n";
			cout << "Example: 0 7 2    This would place a ship beginning at X:7 Y:2 going horizontal\n\n";
			cout << "Ship to place: " << ship[thisShip].name << " which has a length of " << ship[thisShip].length << "\n";
			cout << "Where do you want it placed? ";

			//Get input from user and loop until good data is returned
			PLACESHIPS aShip;
			aShip.shipType.onGrid[0].X = -1;
			while (aShip.shipType.onGrid[0].X == -1)
			{
				aShip = UserInputShipPlacement();
			}

			//Combine user data with "this ship" data
			aShip.shipType.length = ship[thisShip].length;
			aShip.shipType.name = ship[thisShip].name;

			//Add the FIRST grid point to the current player's game board
			player[aplyr].grid[aShip.shipType.onGrid[0].X][aShip.shipType.onGrid[0].Y] = isSHIP;

			//Determine ALL grid points based on length and direction
			for (int i = 1; i<aShip.shipType.length; ++i)
			{
				if (aShip.direction == HORIZONTAL) {
					aShip.shipType.onGrid[i].X = aShip.shipType.onGrid[i - 1].X + 1;
					aShip.shipType.onGrid[i].Y = aShip.shipType.onGrid[i - 1].Y;
				}
				if (aShip.direction == VERTICAL) {
					aShip.shipType.onGrid[i].Y = aShip.shipType.onGrid[i - 1].Y + 1;
					aShip.shipType.onGrid[i].X = aShip.shipType.onGrid[i - 1].X;
				}

				//Add the REMAINING grid points to our current players game board
				player[aplyr].grid[aShip.shipType.onGrid[i].X][aShip.shipType.onGrid[i].Y] = isSHIP;
			}
			//Loop back through each ship type
		}
		//Loop back through each player
	}

	//********* FINISHED WITH "PLACE SHIPS" PHASE *********************************
	//*****************************************************************************

	//Ready to play the game
	int turns;
	gameRunning = true;
	int thisPlayer = 1;
	do {
		//Because we are ATTACKING now, the 
		//opposite players board is the display board
		int enemyPlayer;
		if (thisPlayer == 1) enemyPlayer = 2;
		if (thisPlayer == 2) enemyPlayer = 1;
		system("cls");
		DrawBoard(enemyPlayer);

		//Get attack coords from this player
		bool goodInput = false;
		int x, y;
		while (goodInput == false) {
			goodInput = UserInputAttack(x, y, thisPlayer);
		}

		//Check board; if a ship is there, set as HIT.. otherwise MISS
		if (player[enemyPlayer].grid[x][y] == isSHIP) player[enemyPlayer].grid[x][y] = isHIT;
		if (player[enemyPlayer].grid[x][y] == isWATER) player[enemyPlayer].grid[x][y] = isMISS;

		//Check to see if the game is over
		//If 0 is returned, nobody has won yet
		int aWin = GameOverCheck(enemyPlayer);
		turns = TurnCounter(thisPlayer);
		if (aWin != 0) {
			gameRunning = false;
			break;
		}

		//Alternate between each player as we loop back around
		thisPlayer = (thisPlayer == 1) ? 2 : 1;
	} while (gameRunning);

	system("cls");
	cout << "\n\nCONGRATULATIONS!!!  PLAYER " << thisPlayer << " HAS WON THE GAME IN " << turns <<" TURNS!\n\n\n\n";

	system("pause");
	return 0;
}

