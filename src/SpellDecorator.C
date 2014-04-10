/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	SpellDecorator.C
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "SpellDecorator.h"
#include "Board.h"

////////////// Decorator //////////////
SpellDecorator::SpellDecorator(Piece* pS) {
	pieceSpell = pS;
	mana = true;
}

SpellDecorator::~SpellDecorator(){
	if (pieceSpell) {
		delete pieceSpell;
	}
}

void SpellDecorator::validateSpellReach(const Coordinate& currCoord, const Coordinate& destCoord,
										Piece* selectedPiece, Piece* destPiece){
	// Is the destination square not NULL
	if (destPiece) {
		// Is the destination square friendly (same team)
		if(destPiece->getTeam() == selectedPiece->getTeam()){
			throw "Error: Cannot cast a spell on your own piece.";
		}
		if (!mana) {
			throw "Error: No mana left to cast a spell, select another option.";
		}
	} else {
		throw "Error: There is no piece at that coordinate.";
	}
}

// Accessors
string SpellDecorator::getName() const{
	return pieceSpell->getName();
}
char SpellDecorator::getSymbol() const{
	return pieceSpell->getSymbol();
}
int SpellDecorator::getLife() const{
	return pieceSpell->getLife();
}
int SpellDecorator::getTeam() const{
	return pieceSpell->getTeam();
}
bool SpellDecorator::isSelected() const{
	return pieceSpell->isSelected();
}
Coordinate SpellDecorator::getCoord() const{
	return pieceSpell->getCoord();
}
ReachStrategy* SpellDecorator::getReach() const{
	return pieceSpell->getReach();
}
int SpellDecorator::getMaxLife() const{
	return pieceSpell->getMaxLife();
}
void SpellDecorator::displayOnBoard() const{
	pieceSpell->displayOnBoard();
}
void SpellDecorator::displayInfo() const{
	pieceSpell->displayInfo();
	cout << "\t\tSpells: ";
}

// Mutators
/*void SpellDecorator::setName(const string& _name){ // For extending the game to customly create pieces
	pieceSpell->setName(_name);						// (bonus section), the store
}	
void SpellDecorator::setSymbol(char _symbol){
	pieceSpell->setSymbol(_symbol);
}
void SpellDecorator::setTeam(int _team){
	pieceSpell->setTeam(_team);
}*/
void SpellDecorator::setLife(int _life){
	pieceSpell->setLife(_life);
}
void SpellDecorator::setSelected(bool _selected){
	pieceSpell->setSelected(_selected);
}
void SpellDecorator::setCoord(const Coordinate& coord){
	pieceSpell->setCoord(coord);
}
void SpellDecorator::decLife(int damage){
	pieceSpell->decLife(damage);
}
void SpellDecorator::refresh(){
	mana = true;
}


////////////// Dragon's Spell //////////////
FireBreathing::FireBreathing(Piece* pS) : SpellDecorator(pS){}

Piece* FireBreathing::clonePiece(const Coordinate& _coord, int _team){
	return new FireBreathing(pieceSpell->clonePiece(_coord, _team));
}

void FireBreathing::displayInfo() const{
	SpellDecorator::displayInfo();
	cout << "Firebreath of radius 4 in any direction. Does 6 damage.";
	cout << endl;
}

void FireBreathing::castSpell(Coordinate& currCoord, Coordinate& destCoord, Piece* selectedPiece, 
							  Piece* destPiece, Board& board) {
	// Check spell Reach
	validateSpellReach(currCoord, destCoord, selectedPiece, destPiece);
	
	// Do the damage & set mana to false
	destPiece->decLife(6);
	mana = false;
	//check if s/he/it is dead & 'bury' the piece
	board.buryPiece(destCoord);
}

void FireBreathing::validateSpellReach(const Coordinate& currCoord, const Coordinate& destCoord,
									   Piece* selectedPiece, Piece* destPiece){

	SpellDecorator::validateSpellReach(currCoord, destCoord , selectedPiece, destPiece);
	
	// Is the destination square within reach (4 radius - any direction)
	int xMovement = abs((double)(destCoord.getX() - currCoord.getX()));
	int yMovement = abs((double)(destCoord.getY() - currCoord.getY()));
	// Check straight
	if (!(xMovement <= 4 || yMovement <= 4)){
		throw "Invalid spell cast: coordinate out of reach. I'm no Flame Thrower ^.-.^";
	}
}

////////////// King's Spell //////////////
KingTeleport::KingTeleport(Piece* pS) : SpellDecorator(pS){
	teleportDust = true;
}

Piece* KingTeleport::clonePiece(const Coordinate& _coord, int _team){
	return new KingTeleport(pieceSpell->clonePiece(_coord, _team));
}

void KingTeleport::displayInfo() const{
	SpellDecorator::displayInfo();
	cout << "Swap king with a friendly piece any where on the board." << endl;
	cout << "\t\tYou may only cast this once per game!" << endl;
}

void KingTeleport::castSpell(Coordinate& currCoord, Coordinate& destCoord, Piece* selectedPiece, 
							 Piece* destPiece, Board& board) {
	if(teleportDust == true){
		teleportDust = false;
		if (destPiece) {
			if(destPiece->getTeam() == selectedPiece->getTeam()){
				
				// swap piece*'s
				board.swapPiecesAt(currCoord, destCoord);
				
				cout << "You are now out of teleport dust for that piece." << endl;
			}
		} else {
			throw "Error: There is no piece at that coordinate.";
		}
	} else {
		throw "Ooops, your piece is out of Teleport dust.";
	}
}

void KingTeleport::validateSpellReach(const Coordinate& currCoord, const Coordinate& destCoord,
									  Piece* selectedPiece, Piece* destPiece){ }

////////////// Phantom's Spell //////////////
Teleport::Teleport(Piece* pS) : SpellDecorator(pS){}

Piece* Teleport::clonePiece(const Coordinate& _coord, int _team){
	return new Teleport(pieceSpell->clonePiece(_coord, _team));
}

void Teleport::displayInfo() const{
	SpellDecorator::displayInfo();
	cout << "Teleport in any direction. Each sqaure you move," << endl;
	cout << "\t\tcosts your piece one life force point!" << endl;
}

void Teleport::castSpell(Coordinate& currCoord, Coordinate& destCoord, Piece* selectedPiece, 
						 Piece* destPiece, Board& board) {
	if (!mana) {
		throw "Error: No mana left to cast a spell, select another option.";
	}
	int xMovement = abs((double)(destCoord.getX() - currCoord.getX()));
	int yMovement = abs((double)(destCoord.getY() - currCoord.getY()));
	
	// Check if teleporting onto a piece
	if(!destPiece) {
		// Check reach of the spell
		if ((xMovement <= selectedPiece->getLife() && yMovement == 0)
			|| (yMovement <= selectedPiece->getLife() && xMovement == 0)){
			selectedPiece->decLife(xMovement + yMovement);
			board.movePieces(currCoord, destCoord);
			board.buryPiece(destCoord);
		} else if ((xMovement == yMovement) && (xMovement + yMovement <= selectedPiece->getLife()*2)) { // Check diagonal
			selectedPiece->decLife((xMovement+yMovement)/2);
			board.movePieces(currCoord, destCoord);
			board.buryPiece(destCoord);
		} else {
			throw "Error: invalid coordinate, check the movement again.";
		}
		
	} else {
		throw "Error: you cannot teleport onto another piece.";
	}
	mana = false;
}

void Teleport::validateSpellReach(const Coordinate& currCoord, const Coordinate& destCoord,
								  Piece* selectedPiece, Piece* destPiece){ }

////////////// Necromancer's Spell //////////////
Resurrect::Resurrect(Piece* pS) : SpellDecorator(pS){ }

Piece* Resurrect::clonePiece(const Coordinate& _coord, int _team){
	return new Resurrect(pieceSpell->clonePiece(_coord, _team));
}

void Resurrect::displayInfo() const{
	SpellDecorator::displayInfo();
	cout << "Resurrect the last piece that died by sacrificing any" << endl;
	cout << "\t\tpiece within a 3 square radius." << endl;
}

void Resurrect::castSpell(Coordinate& currCoord, Coordinate& destCoord, Piece* selectedPiece, 
							 Piece* destPiece, Board& board) {
	cout << "Resurrect spell" << endl;
	int sacrificialLife;
	Piece* deadPiece = 0;
	
	// Check mana
	if(!mana) {
		throw "Error: No mana left to cast a spell, select another option.";	
	}
	// Check for a Piece there
	if (!destPiece) {
		throw "Error: There is not piece at that coordinate.";
	}
	// Check if the destination piece is a king
	if (destPiece->getSymbol() == 'X') {
		throw "You cannot, under any circumstance, sacrifice a King.";
	}
	
	// Check if the piece is in reach
	validateSpellReach(currCoord, destCoord , selectedPiece, destPiece);
	
	// Check if the current team has dead pieces!
	if (selectedPiece->getTeam() == 1) {
		if (board.team1GraveYard.isEmpty()) {
			throw "Error: You have no dead pieces to Resurrect.";
		} else {
			// Get the life of the sacrificed piece
			sacrificialLife = destPiece->getLife();
			
			// 'Ressurrect' the dead piece
			board.team1GraveYard.pop(deadPiece);
			
			// Set deadPieces' life
			deadPiece->setLife(sacrificialLife);
			
			// Set the coordinate of the deadPiece to the sacrificed piece coord
			deadPiece->setCoord(destCoord);
			
			// Swap the piece pointers
			board.graveyard.push_back(destPiece);
			board.setPieceAt(destCoord, deadPiece);
			
			// Set necromancer's mana to false
			mana = false;
			
			// Set the resurrected pieces mana to true
			FootSoldier* tempFootSoldierPTR;
			Knight* tempKnightPTR;
			if ((typeid(deadPiece) == typeid(tempFootSoldierPTR))
				&& (typeid(deadPiece) == typeid(tempKnightPTR))) {
			} else {
				board.getPieceAt(destCoord)->refresh();
			}
			
			deadPiece = 0;
		}

	} else {
		if (board.team2GraveYard.isEmpty()) {
			throw "Error: You have no dead pieces to Resurrect.";
		} else {
			// Get the life of the sacrificed piece
			sacrificialLife = destPiece->getLife();
			
			// 'Ressurrect' the dead piece
			board.team2GraveYard.pop(deadPiece);
			
			// Set deadPieces' life
			deadPiece->setLife(sacrificialLife);
			
			// Set the coordinate of the deadPiece to the sacrificed piece coord
			deadPiece->setCoord(destCoord);
			
			// Swap the piece pointers
			board.graveyard.push_back(destPiece);
			board.setPieceAt(destCoord, deadPiece);
			
			// Set necromancer's mana to false
			mana = false;
			
			// Set the resurrected pieces mana to true
			FootSoldier* tempFootSoldierPTR;
			Knight* tempKnightPTR;
			if ((typeid(deadPiece) == typeid(tempFootSoldierPTR))
				&& (typeid(deadPiece) == typeid(tempKnightPTR))) {
			} else {
				board.getPieceAt(destCoord)->refresh();
			}
			
			deadPiece = 0;
		}
	}
}

void Resurrect::validateSpellReach(const Coordinate& currCoord, const Coordinate& destCoord,
									  Piece* selectedPiece, Piece* destPiece){
	// Is the destination square within reach (4 radius - any direction)
	int xMovement = abs((double)(destCoord.getX() - currCoord.getX()));
	int yMovement = abs((double)(destCoord.getY() - currCoord.getY()));
	// Check straight
	if (!(xMovement <= 3 || yMovement <= 3)){
		throw "Invalid spell cast: coordinate out of reach.";
	}

}

////////////// Healer's Spell //////////////
Heal::Heal(Piece* pS) : SpellDecorator(pS){ }

Piece* Heal::clonePiece(const Coordinate& _coord, int _team){
	return new Heal(pieceSpell->clonePiece(_coord, _team));
}

void Heal::displayInfo() const{
	SpellDecorator::displayInfo();
	cout << "Restore any friendly pieces' life within a 3 square radius." << endl;
	cout << "\t\t*This spell has no effect on Phantoms." << endl;
}

void Heal::castSpell(Coordinate& currCoord, Coordinate& destCoord, Piece* selectedPiece, 
						  Piece* destPiece, Board& board) {
	cout << "Heal spell" << endl;
	
	// Is the destination square not NULL
	if (!mana) {
		throw "Error: No mana left to cast a spell, select another option.";
	}
	if (destPiece) {
		// Is the destination square friendly (same team)
		if(destPiece->getTeam() != selectedPiece->getTeam()){
			throw "Error: Cannot cast heal on an enemy piece.";
		}
		if(destPiece->getSymbol() == 'P'){
			throw "Error: Cannot cast heal on a Phantom.";
		}
		if (destPiece->getLife() == destPiece->getMaxLife()) {
			throw "That piece already has full health, heal something else.";
		}
		
		validateSpellReach(currCoord, destCoord , selectedPiece, destPiece);
		
		destPiece->setLife(destPiece->getMaxLife());
		
		mana = false;
		
	} else {
		throw "Error: There is no piece at that coordinate.";
	}
}

void Heal::validateSpellReach(const Coordinate& currCoord, const Coordinate& destCoord,
								   Piece* selectedPiece, Piece* destPiece){

	// Is the destination square within reach (4 radius - any direction)
	int xMovement = abs((double)(destCoord.getX() - currCoord.getX()));
	int yMovement = abs((double)(destCoord.getY() - currCoord.getY()));
	// Check straight
	if (!(xMovement <= 3 || yMovement <= 3)){
		throw "Invalid spell cast: coordinate out of reach.";
	}
}

