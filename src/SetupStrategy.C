/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	SetupStrategy.C
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "SetupStrategy.h"

// Enum used to identify prototypes
enum pieceTypes_enum{FOOTSOLDIERS, KINGS, KNIGHTS, DRAGONS, PHANTOMS, HEALERS, NECROMANCERS, TOTALS};	

/////////////// SetupStrategy ///////////////
SetupStrategy::SetupStrategy(){
// Create piece prototypes
	pieceTypes = new Piece*[TOTALS];
	pieceTypes[FOOTSOLDIERS] = new FootSoldier();
	pieceTypes[KINGS] = new KingTeleport(  new King()  );
	pieceTypes[KNIGHTS] = new Knight();
	pieceTypes[DRAGONS] =  new FireBreathing(  new Dragon()  );
	pieceTypes[PHANTOMS] = new Teleport(  new Phantom()  );
	pieceTypes[HEALERS] = new Heal(  new Healer()  );
	pieceTypes[NECROMANCERS] = new Resurrect(  new Necromancer()  );
}

SetupStrategy::~SetupStrategy(){
	if (pieceTypes) {
		for (int i = 0; i < TOTALS; i++) {
			if (pieceTypes[i]) {
				delete pieceTypes[i];
				pieceTypes[i] = 0;
			}
		}
	}
	delete [] pieceTypes;
	pieceTypes = 0;
}


/////////////// FixedSetupStrategy ///////////////
void FixedSetupStrategy::setup(Piece*** board, int dimension){

// Temporary variables
	Coordinate tmpCoord1;
	Coordinate tmpCoord2;
// Need the make generic code generic as possible for extending the board dimensions
	int dimMinus1 = dimension - 1;
	int dimMinus2 = dimension - 2; 
	
	//srand(time(0));
	//int randomPiece = 0;

// Create the Kings
	tmpCoord1.setCoordXY(4,0);
	board[4][0] = pieceTypes[KINGS]->clonePiece(tmpCoord1,1);
	tmpCoord1.setCoordXY(4,dimMinus1);
	board[4][dimMinus1] = pieceTypes[KINGS]->clonePiece(tmpCoord1,2);

// Create Footsoldiers
	for (int x = 0; x < dimension; x++) {
		tmpCoord1.setCoordXY(x,1);
		tmpCoord2.setCoordXY(x,dimMinus2);
		board[x][1] = pieceTypes[FOOTSOLDIERS]->clonePiece(tmpCoord1,1);
		board[x][dimMinus2] = pieceTypes[FOOTSOLDIERS]->clonePiece(tmpCoord2,2);
	}
	
// Create knights team 1
	tmpCoord1.setCoordXY(1,0);
	board[1][0] = pieceTypes[KNIGHTS]->clonePiece(tmpCoord1,1);
	tmpCoord1.setCoordXY(7,0);
	board[7][0] = pieceTypes[KNIGHTS]->clonePiece(tmpCoord1,1);	
// Create knights team 2
	tmpCoord2.setCoordXY(1,dimMinus1);
	board[1][dimMinus1] = pieceTypes[KNIGHTS]->clonePiece(tmpCoord2,2);
	tmpCoord2.setCoordXY(7,dimMinus1);
	board[7][dimMinus1] = pieceTypes[KNIGHTS]->clonePiece(tmpCoord2,2);
	
// Create Dragons team 1
	tmpCoord1.setCoordXY(0,0);
	board[0][0] = pieceTypes[DRAGONS]->clonePiece(tmpCoord1,1);
	tmpCoord1.setCoordXY(dimension-1,0);
	board[dimension-1][0] = pieceTypes[DRAGONS]->clonePiece(tmpCoord1,1);	
// Create Dragons team 2
	tmpCoord2.setCoordXY(0,dimMinus1);
	board[0][dimMinus1] = pieceTypes[DRAGONS]->clonePiece(tmpCoord2,2);
	tmpCoord2.setCoordXY(dimMinus1,dimMinus1);
	board[dimMinus1][dimMinus1] = pieceTypes[DRAGONS]->clonePiece(tmpCoord2,2);
	
// Create Phantoms team 1
	tmpCoord1.setCoordXY(2,0);
	board[2][0] = pieceTypes[PHANTOMS]->clonePiece(tmpCoord1,1);
	tmpCoord1.setCoordXY(6,0);
	board[6][0] = pieceTypes[PHANTOMS]->clonePiece(tmpCoord1,1);	
// Create Phantoms team 2
	tmpCoord2.setCoordXY(2,dimMinus1);
	board[2][dimMinus1] = pieceTypes[PHANTOMS]->clonePiece(tmpCoord2,2);
	tmpCoord2.setCoordXY(6,dimMinus1);
	board[6][dimMinus1] = pieceTypes[PHANTOMS]->clonePiece(tmpCoord2,2);
	
// Create Healer team 1
	tmpCoord1.setCoordXY(5,0);
	board[5][0] = pieceTypes[HEALERS]->clonePiece(tmpCoord1,1);
// Create Healer team 2
	tmpCoord2.setCoordXY(5,dimMinus1);
	board[5][dimMinus1] = pieceTypes[HEALERS]->clonePiece(tmpCoord2,2);
	
// Create Necromancer team 1
	tmpCoord1.setCoordXY(3,0);
	board[3][0] = pieceTypes[NECROMANCERS]->clonePiece(tmpCoord1,1);
// Create Necromancer team 2
	tmpCoord2.setCoordXY(3,dimMinus1);
	board[3][dimMinus1] = pieceTypes[NECROMANCERS]->clonePiece(tmpCoord2,2);
	
	
// This function demonstrates some of the provisions made for an extendible board
// of user defined dimensions.
	if (dimension > 9) {
		for (int x = 8; x < dimMinus1; x++) {
			tmpCoord1.setCoordXY(x,0);
			tmpCoord2.setCoordXY(x,dimMinus1);
			//do {
			//	randomPiece = rand() % TOTALS;
			//} while (randomPiece == KINGS);
			board[x][0] = pieceTypes[FOOTSOLDIERS]->clonePiece(tmpCoord1,1);
			board[x][dimMinus1] = pieceTypes[FOOTSOLDIERS]->clonePiece(tmpCoord2,2);
		}
	}
}



/////////////// RandomSetupStrategy ///////////////
void RandomSetupStrategy::setup(Piece*** board, int dimensions){

// Temp coord for setting pieces
	Coordinate tmpCoord;
	int dimMinus1 = dimensions - 1;
	
// Fixed King position to insure a fair start	
	tmpCoord.setCoordXY((dimMinus1)/2,0);
	board[(dimMinus1)/2][0] = pieceTypes[KINGS]->clonePiece(tmpCoord,1);
	tmpCoord.setCoordXY((dimMinus1)/2,dimMinus1);
	board[(dimMinus1)/2][dimMinus1] = pieceTypes[KINGS]->clonePiece(tmpCoord,2);
	
// Fixed Phantom position to insure a fair start
	tmpCoord.setCoordXY(0,0);
	board[0][0] = pieceTypes[PHANTOMS]->clonePiece(tmpCoord,1);
	tmpCoord.setCoordXY(dimMinus1,0);
	board[dimMinus1][0] = pieceTypes[PHANTOMS]->clonePiece(tmpCoord,1);
	
	tmpCoord.setCoordXY(dimMinus1,dimMinus1);
	board[dimMinus1][dimMinus1] = pieceTypes[PHANTOMS]->clonePiece(tmpCoord,2);
	tmpCoord.setCoordXY(0,dimMinus1);
	board[0][dimMinus1] = pieceTypes[PHANTOMS]->clonePiece(tmpCoord,2);
		
// Use random setup algorithm to initialise 
	int footCnt = 0;
	int playercount = 1;
	srand(time(0));
	int randomx, randomy;
	int extraFootSoldiers = dimensions - 9;
	int necromancerCnt = 1, healerCnt = 1;
	int dragonCnt = 2, knightCnt = 2;
	
	while (playercount <= 2){
		// Insert a row of FootSoldiers each
		while (footCnt < dimensions){
		// Initialise & randomise some coords
			randomx = randomX(dimensions);
			randomy = randomY(dimensions, playercount);
			if (!board[randomx][randomy]){
				tmpCoord.setCoordXY(randomx,randomy);
				board[randomx][randomy] = pieceTypes[FOOTSOLDIERS]->clonePiece(tmpCoord,playercount);
				footCnt++;
			}
		}
	// Initialise special pieces
		// Dragons
		while (dragonCnt > 0) {
			//initialise & randomise some co-ords
			randomx = randomX(dimensions);
			randomy = randomY(dimensions, playercount);
			if (!board[randomx][randomy]){
				tmpCoord.setCoordXY(randomx,randomy);
				board[randomx][randomy] = pieceTypes[DRAGONS]->clonePiece(tmpCoord,playercount);
				dragonCnt--;
			}
		}
		// Knights
		while (knightCnt > 0) {
			//initialise & randomise some co-ords
			randomx = randomX(dimensions);
			randomy = randomY(dimensions, playercount);
			if (!board[randomx][randomy]){
				tmpCoord.setCoordXY(randomx,randomy);
				board[randomx][randomy] = pieceTypes[KNIGHTS]->clonePiece(tmpCoord,playercount);
				knightCnt--;
			
			}
		}
		// Necromancer
		while (necromancerCnt > 0) {
			//initialise & randomise some co-ords
			randomx = randomX(dimensions);
			randomy = randomY(dimensions, playercount);
			if (!board[randomx][randomy]){
				tmpCoord.setCoordXY(randomx,randomy);
				board[randomx][randomy] = pieceTypes[NECROMANCERS]->clonePiece(tmpCoord,playercount);
				necromancerCnt--;
			}
		}
		// Healer
		while (healerCnt > 0) {
			//initialise & randomise some co-ords
			randomx = randomX(dimensions);
			randomy = randomY(dimensions, playercount);
			if (!board[randomx][randomy]){
				tmpCoord.setCoordXY(randomx,randomy);
				board[randomx][randomy] = pieceTypes[HEALERS]->clonePiece(tmpCoord,playercount);
				healerCnt--;
			}
		}
		// Buffer the rest of the board with new Footsoldiers
		while (extraFootSoldiers > 0) {
			//initialise & randomise some co-ords
			randomx = randomX(dimensions);
			randomy = randomY(dimensions, playercount);
			if (!board[randomx][randomy]){
				tmpCoord.setCoordXY(randomx,randomy);
				board[randomx][randomy] = pieceTypes[FOOTSOLDIERS]->clonePiece(tmpCoord,playercount);
				extraFootSoldiers--;
			}
		}
		playercount++;
		footCnt = 0;
		extraFootSoldiers = dimensions - 9;
		necromancerCnt = 1;
		healerCnt = 1;
		dragonCnt = 2;
		knightCnt = 2;
	}
}

int RandomSetupStrategy::randomY(int dimensions, int team){
// These ifs are just to demonstrate calculating randoms for a board
// with even number of x and ys
	int Ycoord = 0;
	if (team == 1){
		if (dimensions % 2 == 0){
			// These are theoretical provided we add functionality 
			// for a custom extended board size.
			Ycoord = rand() % (dimensions/2) -1;
		} else {
			Ycoord = rand() % (dimensions/2);
		}
		return Ycoord;
	} else {
		if (dimensions % 2 == 0){
			Ycoord = rand() % (dimensions/2);
		} else {
			Ycoord = (rand() % (dimensions/2));
		}
		return Ycoord + (dimensions/2)+1;
	}
}

int RandomSetupStrategy::randomX(int dimensions){
	return rand() % dimensions;
}


