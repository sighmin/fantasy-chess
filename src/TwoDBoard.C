/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	TwoDBoard.C
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "TwoDBoard.h"

// Ctor & Dtor
TwoDBoard::TwoDBoard(){
	
	board = new Piece**[DEFAULT_DIMENSIONS];
	
	for (int x = 0; x < DEFAULT_DIMENSIONS; x++) {
		board[x] = new Piece*[DEFAULT_DIMENSIONS];
		for (int y = 0; y < DEFAULT_DIMENSIONS; y++) {
			board[x][y] = 0;
		}
	}
}

TwoDBoard::~TwoDBoard(){
	if (board){
		for (int x = 0; x < DEFAULT_DIMENSIONS; x++) {
			
			if (board[x]){
				for (int y = 0; y < DEFAULT_DIMENSIONS; y++) {
					
					if (board[x][y]) {
						delete board[x][y];
						board[x][y] = 0;
					}
				}
				delete [] board[x];
				board[x] = 0;
			}
		}//end for
		delete [] board;
		board = 0;
	}//end big if
	if (!graveyard.empty()) {
		vector<Piece*>::iterator iter;
		for (iter = graveyard.begin(); iter < graveyard.end(); iter++) {
			delete *iter;
		}
		graveyard.clear();
	}
}

//Display
void TwoDBoard::display() const {
	//X alpha coordinates
	cout << "     ";
	for(char letters = 'a'; letters < 'a'+ DEFAULT_DIMENSIONS; letters++){
		cout << "      " << letters;
	}
	cout << endl;
	
	//'Border'
	cout << '\t';
	for(int i = 0; i < DEFAULT_DIMENSIONS; i++){
		cout << "-------";
	}
	cout << '-' << endl;
	
	//Squares + Contents
	for(int y = 0; y < DEFAULT_DIMENSIONS; y++){
		cout << "\t|";
		for(int j = 0; j < DEFAULT_DIMENSIONS; j++){
			cout << "      |";
			
		}
		cout << endl;
		
		//Y numeric coordinates
		if( y < 10){
			cout << "    " << y << "   |";
		} else {
			cout << "    " << y << "  |";
		}
		
		//Displaying pieces contained in the board
		for(int x = 0; x < DEFAULT_DIMENSIONS; x++){
			if(!board[x][y]){
				cout << "  " << "  " << "  |";
			} else if (board[x][y]->isSelected()) {
				cout << " *";
				board[x][y]->displayOnBoard();
				cout << "* |";
			} else {
				cout << "  ";
				board[x][y]->displayOnBoard();
				cout << "  |";
			}
		}
		cout << endl;
		
		//The bottom of the squares
		cout << "\t|";
		for(int j = 0; j < DEFAULT_DIMENSIONS; j++){
			cout << "------|";
		}
		cout << endl;
	}
}

Piece* TwoDBoard::operator()(const Coordinate& coord){
	return board[coord.getX()][coord.getY()];
}

Piece* TwoDBoard::operator()(int x, int y){
	return board[x][y];	
}

Piece* TwoDBoard::getPieceAt(const Coordinate& coord){
	return board[coord.getX()][coord.getY()];
}

void TwoDBoard::setPieceAt(const Coordinate& coord, Piece* piece){
	board[coord.getX()][coord.getY()] = piece;
}

Piece* TwoDBoard::getSelectedPiece() const{
	for (int k = 0; k < DEFAULT_DIMENSIONS; k ++) {
		for (int j= 0; j < DEFAULT_DIMENSIONS; j++) {
			if(board[j][k]){
				if (board[j][k]->isSelected()) {
					return board[j][k];
				}
			}
		}
	}
	return 0;
}

void TwoDBoard::swapPiecesAt(Coordinate& currCoord, Coordinate& destCoord){
	//swap Piece*'s
	Piece* temp = board[destCoord.getX()][destCoord.getY()];
	board[destCoord.getX()][destCoord.getY()] = board[currCoord.getX()][currCoord.getY()];
	board[currCoord.getX()][currCoord.getY()] = temp;
	
	//swap coordinates
	Coordinate tmp = destCoord;
	destCoord = currCoord;
	currCoord = tmp;
}

void TwoDBoard::buryPiece(const Coordinate& coord){
	if (board[coord.getX()][coord.getY()]->getLife() <= 0) {
		
		if (board[coord.getX()][coord.getY()]->getTeam() == 1) {
			team1GraveYard.push(board[coord.getX()][coord.getY()]);
		} else {
			team2GraveYard.push(board[coord.getX()][coord.getY()]);
		}
		board[coord.getX()][coord.getY()] = 0;
	}
}

//Logic functions
int TwoDBoard::move(Coordinate& currCoord, Coordinate& destCoord){
	Piece* selectedPiece = getPieceAt(currCoord);
	Piece* destPiece = getPieceAt(destCoord);
	int kingWasAttacked = 0;
	if (destPiece) {
		//check owner
		if(destPiece->getTeam() == selectedPiece->getTeam()){
			throw ReachStrategy::MoveException("Error: Cannot move onto your own piece.");
		}
		//check reach
		selectedPiece->getReach()->validateReach(currCoord, destCoord);
		
		// check for the king status
		if (getPieceAt(destCoord)->getSymbol() == 'X') {
			kingWasAttacked = getPieceAt(destCoord)->getTeam();
		}
		if ((getPieceAt(currCoord)->getSymbol() == 'X') && (getPieceAt(currCoord)->getLife() <= 2)) {
			kingWasAttacked = getPieceAt(currCoord)->getTeam();
		}
		if ((getPieceAt(currCoord)->getSymbol() == 'X') && (getPieceAt(currCoord)->getLife() <= 2) && (getPieceAt(destCoord)->getSymbol() == 'X')) {
			kingWasAttacked = 3;
		}
		
		//attack piece
		attackPiece(currCoord, destCoord); //this function assumes destination has an enemy piece
		
		return kingWasAttacked;
			
	} else {
		selectedPiece->getReach()->validateReach(currCoord, destCoord);
		movePieces(currCoord, destCoord); //this function assumes destination is NULL
		return false;
	}
}

void TwoDBoard::movePieces(Coordinate& currCoord, Coordinate& destCoord){
	// swap piece*'s
	board[destCoord.getX()][destCoord.getY()] = board[currCoord.getX()][currCoord.getY()];
	board[currCoord.getX()][currCoord.getY()] = 0;
	
	// change the coords
	board[destCoord.getX()][destCoord.getY()]->setCoord(currCoord);
}

void TwoDBoard::attackPiece(Coordinate& currCoord, Coordinate& destCoord){
	
	//set life = 0
	board[destCoord.getX()][destCoord.getY()]->setLife(0);
	//push the defeated piece* into a vector to be deleted later
	buryPiece(destCoord);
	
	//current Piece* = dest Piece*
	board[destCoord.getX()][destCoord.getY()] = board[currCoord.getX()][currCoord.getY()];
	//remove reference from board
	board[currCoord.getX()][currCoord.getY()] = 0;
	
	// change the coords
	board[destCoord.getX()][destCoord.getY()]->setCoord(currCoord);
	board[destCoord.getX()][destCoord.getY()]->decLife(2);
	
	//check if s/he is dead
	buryPiece(destCoord); //this represents the current player after the move
}

void TwoDBoard::deselectPieces(){
	for (int k = 0; k < DEFAULT_DIMENSIONS; k ++) {
		for (int j= 0; j < DEFAULT_DIMENSIONS; j++) {
			if(board[j][k]){
				board[j][k]->setSelected(false);
			}
		}
	}
}

void TwoDBoard::refreshSpells(){
	
	FootSoldier* tempFootSoldierPTR;
	Knight* tempKnightPTR;
	
	for (int k = 0; k < DEFAULT_DIMENSIONS; k ++) {
		for (int j= 0; j < DEFAULT_DIMENSIONS; j++) {
			if(board[j][k]){
				if ((typeid(board[j][k]) == typeid(tempFootSoldierPTR))
					&& (typeid(board[j][k]) == typeid(tempKnightPTR))) {
				} else {
					board[j][k]->refresh();
				}
			}
		}
	}
}

void TwoDBoard::calculateScores(const int kingIsDead) {
	
	int team1Score = 0, team2Score = 0, team1PieceCount =0, team2PieceCount =0;
	int bonusScoreTeam1 =0, bonusScoreTeam2 =0;
	
	cout << "Scores:\n-----------------------------------------------------------------------\n";
	
	for (int k = 0; k < DEFAULT_DIMENSIONS; k ++) {
		for (int j= 0; j < DEFAULT_DIMENSIONS; j++) {
			if(board[j][k]){
				if (board[j][k]->getTeam() == 1) {
					team1Score += board[j][k]->getLife();
					team1PieceCount++;
				} else {
					team2Score += board[j][k]->getLife();
					team2PieceCount++;
				}
			}
		}
	}
	if (kingIsDead == 1){
		// Team 1's king died
		bonusScoreTeam2 = 100;
	} else if (kingIsDead == 2){
		// Team 2's king died
		bonusScoreTeam1 = 100;
	} else if (kingIsDead == 3){
		// Stalemate
		bonusScoreTeam1 = 20;
		bonusScoreTeam2 = 20;
	} else if (kingIsDead == 4){
		// Team 1 forfeitted.
		bonusScoreTeam2 = 20;
	} else {
		// Team 2 forfeitted.
		bonusScoreTeam1 = 20;
	}
	
	cout << "Team 1: ";
	cout << "\n------\n";
	team1GraveYard.displayStack();
	cout << "------\n";
	cout << "Pieces left on the board:\t\t" << team1PieceCount << endl;
	cout << "Life points for remaining pieces:\t" << team1Score << endl;
	cout << "Bonus:\t\t\t\t\t" << bonusScoreTeam1 << endl;
	cout << "\t\t\t\t\t---" << endl;
	cout << "Total Points:\t\t\t\t" << team1Score + bonusScoreTeam1 + team1PieceCount << endl << endl;
	
	cout << "Team 2: ";
	cout << "\n------\n";
	team2GraveYard.displayStack();
	cout << "------\n";
	cout << "Pieces left on the board:\t\t" << team2PieceCount << endl;
	cout << "Life points for remaining pieces:\t" << team2Score << endl;
	cout << "Bonus:\t\t\t\t\t" << bonusScoreTeam2 << endl;
	cout << "\t\t\t\t\t---" << endl;
	cout << "Total Points:\t\t\t\t" << team2Score + bonusScoreTeam2 + team2PieceCount << endl << endl;
	
}

