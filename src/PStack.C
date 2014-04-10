/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	PStack.C
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "PStack.h"

PStack::PStack() {
	top = 0;
}

PStack::~PStack(){
	DeadPieceNode* tmp = top;
	DeadPieceNode* next;
	
	while (tmp) {
		next = tmp->next;
		delete tmp->deadPiece; // this deallocates the Piece* memory
		delete tmp;
		tmp = next;
	}
}

void PStack::push(Piece* pushPiece){
	DeadPieceNode* newNode = new DeadPieceNode();
	newNode->deadPiece = pushPiece;
	
	if (isEmpty()) {
		// Make newNode the first Node
		top = newNode;
		newNode->next = 0;
	} else {
		// Add to the front
		newNode->next = top;
		top = newNode;
	}
}

void PStack::pop(Piece* &popPiece){
	DeadPieceNode* tmp;
	
	if (isEmpty()) {
		throw "There is no dead piece to resurrect!";
	} else {
		popPiece = top->deadPiece;
		tmp = top->next;
		delete top;
		top = tmp;
	}
}

bool PStack::isEmpty(){
	return (!top);
}

void PStack::displayStack(){
	DeadPieceNode* tmp = top;

	cout << "Graveyard: ";
	if(isEmpty()){
		cout << "no pieces dead..." << endl;
	} else {
		displayStackREC(tmp);
		cout << endl;
	}
}

void PStack::displayStackREC(DeadPieceNode* tmp){
	if (tmp) {
		displayStackREC(tmp->next);
		if (tmp->next != 0) {
			cout << ", ";
		}
		cout << tmp->deadPiece->getSymbol();
		cout << tmp->deadPiece->getTeam();
	}
}

