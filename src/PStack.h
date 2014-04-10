/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	PStack.h
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PSTACK
#define PSTACK

#include "Piece.h"

using namespace std;

// Class has the resposibility to delete it's contents
class PStack {
private:
	// Node holding Piece* that was killed
	struct DeadPieceNode {
		Piece* deadPiece;
		DeadPieceNode* next;
	};
	DeadPieceNode* top;
	
	// Recursive display backwards function
	void displayStackREC(DeadPieceNode*);
public:
	PStack();
	~PStack();
	
	void push(Piece*);
	void pop(Piece*&);
	
	bool isEmpty();
	void displayStack();
};

#endif
