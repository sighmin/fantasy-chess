/* * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	main.C
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * */

#include "GameLogic.h"
#include "Game.h"

using namespace std;

int main(){
	
	GameLogic* newGame = new Game;

	newGame->mainMenu();
	
	delete newGame;
	newGame = 0;
	
	return 0;
}
