/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	BoardCreator.C
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "BoardCreator.h"

///////////////// BoardCreator /////////////////
BoardCreator::BoardCreator() { }

BoardCreator::~BoardCreator() { }

///////////////// TwoDBoardCreator /////////////////
TwoDBoardCreator::TwoDBoardCreator() { }

TwoDBoardCreator::~TwoDBoardCreator() { }

Board* TwoDBoardCreator::createBoard(int){
	return new TwoDBoard();
}
