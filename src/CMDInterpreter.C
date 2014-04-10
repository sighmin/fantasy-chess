/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	CMDInterpreter.C
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "CMDInterpreter.h"

////////////////// CMDInterpreter //////////////////

CMDInterpreter::CMDInterpreter(){
	menuOption = new MenuOption(1);
	coordinates = new Coordinates(1);
}

CMDInterpreter::CMDInterpreter(int){ }

CMDInterpreter::~CMDInterpreter(){
	if (menuOption) { 
		delete menuOption;
	}
	if (coordinates) { 
		delete coordinates;
	}
}

void CMDInterpreter::interpret(char* input, int& menu, Coordinate& coord){
	
	// do preemptive validation - saves resources
	preemptiveValidation(input, menu);
		
	menuOption->interpret(input,menu,coord,1);
	coordinates->interpret(input,menu,coord,1);
	
}

void CMDInterpreter::interpret(char* inputToken, int& menuoption, Coordinate& coord, int){
	////////////////// Parse input //////////////////
	
	int collected = 0;
	int length = strlen(inputToken);
	
	if (length == 4) {
		if (inputToken[0] == option0() || inputToken[0] == option1() || inputToken[0] == option2()) {
			collected += 2;
			menuoption = (int)(inputToken[0]) - 48;
		} else {
			throw CMDInterpreter::GeneralException("Invalid menu option. Try again punk.\n");
		}
	}
	
	if (length == 2) {
		int tempX = (int)(tolower(inputToken[0])) - 97;
		int tempY = (int)(inputToken[1]) - 48;
		
		if (tempX < coordXa() || tempX > coordXi()) {
			throw CMDInterpreter::GeneralException("Invalid X coordinate: out of bounds. "
												   "Try again punk.\n");
		} else {
			if (tempY < coordY0() || tempY > coordY8()) {
				throw CMDInterpreter::GeneralException("Invalid Y coordinate: out of bounds. "
													   "Try again punk.\n");
			} else {
				collected += 2;
				coord.setX(tempX);
				coord.setY(tempY);
			}
		}
	}
	//remove preceeding chars in input, do interpret again
	strcpy(inputToken, &(inputToken[collected]));
}

void CMDInterpreter::preemptiveValidation(char* input, int& menu){
	////////////////// Validating length of input //////////////////
	bool allowExit_Forfeit = false;
	
	// Check if the accidently hit a space
	if (input[0] == ' ') {
		throw CMDInterpreter::GeneralException("Invalid command: space is not a valid"
											   " menu option.\n");
	}
	
	// Check option 4(exit) - catch in CMDInterpreter::interpret
	int length = strlen(input);
	if (input[0] == '4' && length == 1) {
		// Check: if they chose exit option by accident
		cout << "Are you sure you would like to exit? Y/N" << endl << "> ";
		char temp;
		cin >> temp;
		if (temp == 'Y' || temp == 'y') {
			//set menu option
			menu = (int)(menuOption->option4())  - 48;
			allowExit_Forfeit = true;
		} else {
			throw CMDInterpreter::Exception("Please enter your command again.\n");
		}
	}
	
	// Check option 3(forfeit) - catch in CMDInterpreter::interpret
	if (input[0] == '3' && length == 1) {
		// Check: if they chose forfeit option by accident
		cout << "Are you sure you would like to forfeit? Y/N" << endl << "> ";
		char temp;
		cin >> temp;
		if (temp == 'Y' || temp == 'y') {
			//set menu option
			menu = (int)(menuOption->option3()) - 48;
			allowExit_Forfeit = true;
		} else {
			throw CMDInterpreter::Exception("Please enter your command again.\n");
		}
	}
	
	// Check if they accidently pressed an extra key or missed a key
	if (length != 4 && !allowExit_Forfeit) {
		if (length < 4) {
			if (length == 3 && input[1] != ' '){
				throw CMDInterpreter::GeneralException("Invalid command: please separate"
											" your command with a whitespace.\n");
			}
			throw CMDInterpreter::GeneralException("Invalid command: not enough "
											"information to complete your task.\n");
		}
	}
}

////////////////// MenuOption //////////////////

MenuOption::MenuOption(int) : CMDInterpreter(1) {}

// MenuOptions
char MenuOption::option0() { return '0'; }
char MenuOption::option1() { return '1'; }
char MenuOption::option2() { return '2'; }
char MenuOption::option3() { return '3'; }
char MenuOption::option4() { return '4'; }

////////////////// Coordinates //////////////////

Coordinates::Coordinates(int) : CMDInterpreter(1) {}

// Y Coordinates 
int Coordinates::coordY0() { return 0; }
int Coordinates::coordY8() { return 8; }
// X Coordinates 
int Coordinates::coordXa() { return 0; } //these 2 functions are simply shown
int Coordinates::coordXi() { return 8; } //explicitly



