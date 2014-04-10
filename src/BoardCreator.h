/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	BoardCreator.h
 *
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef BOARDCREATOR
#define BOARDCREATOR

#include "Board.h"
#include "TwoDBoard.h"
using namespace std;

class Board;

class BoardCreator {
public:
	BoardCreator();
	virtual ~BoardCreator();
	virtual Board* createBoard(int) = 0;
};

class TwoDBoardCreator : public	BoardCreator {
public:
	TwoDBoardCreator();
	virtual ~TwoDBoardCreator();
	virtual Board* createBoard(int);
};

#endif
