/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *									
 *	FileName	GameLogic.C					
 * 									
 *	Authors		Dean Marsden		29143332		
 *			Simon van Dyk		10266764		
 *									
 *	Date		October 2010					
 *									
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "GameLogic.h"
#include "Players.h"

GameLogic::GameLogic (){
	interpreter = new CMDInterpreter;
	kingIsDead = 0;
}

GameLogic::~GameLogic (){
	if (playerSwitch) {
		delete playerSwitch;
	}
	if (gameBoard) {
		delete gameBoard;
	}
	if (boardCreator) {
		delete boardCreator;
	}
	if (interpreter) {
		delete interpreter;
	}
}

/////// Menu driven functions ///////
void GameLogic ::gameMenu(){
	cout << endl;
	cout << "Select action followed by the piece's co-ordinate:" << endl;
	cout << "(0-Select Piece, 1-Move Piece, 2-Cast Spell, 3-Forfeit, 4-Exit) space delimited" << endl;
	cout << "i.e. 0 d4" << endl;
}

void GameLogic::heading(){
	cout << "   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
	cout << "   *                            ~Fantasy Chess~                          *" << endl;
	cout << "   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
	cout << "   *                           Version : Phase 3                         *" << endl;
	cout << "   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
	
	// Introduction to the game
	cout <<	endl;
	cout << "Welcome to Fantasy Chess! The game is much like ordinary chess but the pieces\n"
			"may cast a spell (if they have spells) every new players turn. A turn comprises\n"
			"of the (A) spell phase and (B) movement phase. Players must be even to secure a\n"
			"fair game. The players are part of a team each with a maximum of 2 teams.\n"
			"You must select a piece on the board before you can do either a spell or a move.\n"
			"The games ends if your king, the X, dies. A piece can die if a another moves on\n"
			"top of it or if a spell does enough damage to deplete it's life force. When a\n"
			"piece moves on top of another piece, it engages in a short battle losing 2 life\n"
			"force - be careful, you can lose pieces in these engagements.\n\n"
			"Please answer a few questions as we setup a new game for you...";
	cout <<	endl << endl;
}

void GameLogic::welcomeMenu(){
	// Display heading + welcome/user message
	heading();
	
	//State:
	createPlayers();
	
	//Factory method:
	createBoard();
	
	//Strategy: sets board up according to player preference
	gameBoard->setStrategy(getGameOptions());
	gameBoard->setupBoard();
}

void GameLogic::mainMenu(){

	welcomeMenu();
	
	gameBoard->display();
	playerSwitch->printCurrentPlayer();
	
	turnCycle();
	
	// Sum up the scores and output something plesant - > refactor this into a function of Game
	//playerSwitch->playerTurn->printNames();
	if (kingIsDead) {
		if (kingIsDead == 1){
			// Team 1's king died
			cout << "Team 1's king just died!" << endl;
			cout << "Team 2 wins!\n" << endl;
			gameBoard->calculateScores(kingIsDead);
		} else if (kingIsDead == 2){
			// Team 2's king died
			cout << "Team 2's king is dead!" << endl;
			cout << "Team 1 wins!\n" << endl;
			gameBoard->calculateScores(kingIsDead);
		} else if (kingIsDead == 3){
			cout << "Both Kings dead! Stale Mate game!" << endl << endl;
			gameBoard->calculateScores(kingIsDead);
		} else {
			// FORFEIT
			cout << "Forfeiting game\n---------------\n";
			
			gameBoard->calculateScores(kingIsDead);
			
		}
	} else {
		cout << "Exiting game.\n";
	}
	
} // end of the program

/////// Input & Creational functions ///////
void GameLogic::getInput(int& menu, Coordinate& coord){
	bool failed = true;
	gameMenu();
	do { // Try to get input until it is valid
		
		cout << "> ";
		string input;
		getline(cin, input);
		
		try {
			if (strlen(input.c_str()) > 4) {
				throw CMDInterpreter::GeneralException("Invalid command: too much "
													   "info to complete your task.\n");
			}

			char cutInput[5];
			strncpy(cutInput, input.c_str(), 5);
			
			interpreter->interpret(cutInput, menu, coord);
			
			// If it sets the 'tokens' correctly, it will continue
			failed = false;
		}
		catch (CMDInterpreter::GeneralException except) {
			except.print();
			failed = true;
		}
		catch (CMDInterpreter::Exception except) {
			cin.ignore();
			except.print();
			failed = true;
		}
	} while (failed);
}

int GameLogic::getGameOptions(){
	
	cout << endl << "-- Please select a board setup --" << endl;
	cout << "1 - Standard setup" << endl;
	cout << "	 is a traditional setup similar to chess." << endl;
	cout << "2 - Random setup" << endl;
	cout << "	 is randomly generated coordinates for the ";
	cout <<	"placement of the pieces." << endl;
	
	bool failed = true;
	int setupOption;
	string input;
	do { // get input until it is valid
		
		cout << "> ";
		getline(cin, input);
		setupOption = (int)(input[0]) - 48;
		
		//////// CHANGE int to a char* for validation & update code
		try {	
			if (input[0] == '\n'){
				throw "Invalid setup option, please select again.";
			}
			if (setupOption != 1 && setupOption != 2) {
				throw "Invalid setup option, please select again.";
			}
			
			failed = false;
			cout << endl << "Starting game..." << endl << endl;
		}
		catch (char const* msg) {
			cout << msg << endl;
			failed = true;
		}
		catch (char* msg) {
			cout << msg << endl;
			failed = true;
		}
	} while (failed);
	return setupOption; // a valid setup option
}

void GameLogic::createBoard(){
//Factory method: creates the 2D board
	cout << "Please enter the dimension of the board (2 or 3 indicating 2D or 3D board)." << endl;
	cout << "> ";
	
	string input;
	cin.ignore();
	getline(cin, input);
	int numDimension = (int)(input[0]) - 48;
	
	if (numDimension != 2) {
		numDimension = 2;
		cout << "Only support for a 2D board has been implemented." << endl;
	}
// Create the requested board
	boardCreator = new TwoDBoardCreator;
	gameBoard = boardCreator->createBoard(numDimension);
}

void GameLogic::createPlayers(){
//State: # of players
	cout << "Please enter how many players would like to play (2-8)." << endl;
	cout << "> ";

	string input;
	getline(cin, input);
	int numPlayers = (int)(input[0]) - 48;
	
	//cin >> numPlayers;
	while ((numPlayers % 2 != 0) || (numPlayers < 2) || (numPlayers > 8)) {
		cout << "Error: Unbalanced number of players, please enter an even number.\n> ";
		getline(cin, input);
		numPlayers = (int)(input[0]) - 48;
	}
	playerSwitch = new PlayerSwitch(numPlayers);
}

/////// GameLogic logic functions ///////
void GameLogic::selectPiece(const Coordinate& coord){
	
	Piece* tempPiece = pieceAtCoord(coord);

	if (!tempPiece){
		throw GameLogic::SelectNULLException("Error: No piece at requested coordinate.\n");
	} else {
		if (tempPiece->getTeam() != playerSwitch->playerTurn->getTeamTurn()) {
			throw GameLogic::SelectEnemyException("Error: Requested piece belongs to another player.\n");
		} else {
			tempPiece->setSelected(true);
			playerSwitch->playerTurn->setHasSelectedPiece(true);
		}
	}
}

/////// Helper functions ///////
Piece* GameLogic::pieceAtCoord(const Coordinate& coord){
	return gameBoard->operator()(coord.getX(), coord.getY());
}

void GameLogic::deselectPlayersPieces(){
	playerSwitch->playerTurn->setHasSelectedPiece(false);	
}

/////// Template method functions ///////
void GameLogic::turnCycle(){
// Enter loop of turns:
	int choice;
	Coordinate requestedCoord, selectedCoord;
	
	do { // Loop menu until forfeit, exit or the game in over (a king 'dies')
		
		// This checks the kings status each turn & exits if appropriate
		if (kingIsDead > 0) { 
			choice = 4;
		} else {
			getInput(choice,requestedCoord);
		}
		
		// Enter into menu
		switch (choice) {
			case 0: //Select
				selectPhase(selectedCoord, requestedCoord);
				break;
			case 1: //Move
				movePhase(selectedCoord, requestedCoord);
				break;
			case 2: //Spell
				spellCastPhase(selectedCoord, requestedCoord);
				break;
			case 3: //Forfeit
				if (playerSwitch->playerTurn->getTeamTurn() == 1) {
					kingIsDead = 4;
				} else {
					kingIsDead = 5;
				}
				break;
			default: break;
		}
	} while (choice != 4);
}

// Empty template method virtual operations
void GameLogic::selectPhase(Coordinate&, Coordinate&) {
	
}
void GameLogic::spellCastPhase(Coordinate&, Coordinate&) {
	
}
void GameLogic::movePhase(Coordinate&, Coordinate&) {
	
}






























