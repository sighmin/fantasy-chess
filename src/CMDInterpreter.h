/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	CMDInterpreter.h
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CMDINTERPRETER
#define CMDINTERPRETER

#include <iostream>
#include <cctype> //for function tolower
#include <string>
#include <cstring>
#include <cstdlib>
#include "Coordinate.h"
using namespace std;

class MenuOption;
class Coordinates;

class CMDInterpreter {
private:
	CMDInterpreter* menuOption;
	CMDInterpreter* coordinates;
public:
	CMDInterpreter();
	CMDInterpreter(int); //constructor for subclasses, avoids infinte loop
	virtual ~CMDInterpreter();

	virtual void interpret(char*, int&, Coordinate&,int); //last int is a dummy parameter
	void interpret(char*, int&, Coordinate&);
	void preemptiveValidation(char*, int&);
	
// Exception classes for validation
	class Exception {
	private:
		string msg;
	public:
		Exception(string s) : msg(s) { }
		void print(){ cout << msg; } 
	};
	
	class GeneralException {
	private:
		string msg;
	public:
		GeneralException(string s) : msg(s) {}
		void print(){ cout << msg; }
	};
	
protected:
// MenuOptions
	virtual char option0(){ return ' '; } //dummy returns
	virtual char option1(){ return ' '; } 
	virtual char option2(){ return ' '; } 
	virtual char option3(){ return ' '; }
	virtual char option4(){ return ' '; }
// Y Coordinates 
	virtual int coordY0(){ return 0; } //dummy returns
	virtual int coordY8(){ return 0; }
// X Coordinates 
	virtual int coordXa(){ return 0; } //dummy returns
	virtual int coordXi(){ return 0; }
};


class MenuOption : public CMDInterpreter {
public:
	MenuOption(int);
protected:
	// MenuOptions
	char option0(); //{ return '0'; }
	char option1();
	char option2();
	char option3();
	char option4();
};

class Coordinates : public CMDInterpreter {
public:
	Coordinates(int);
protected:
	// Y Coordinates 
	int coordY0(); //{ return '0'; }
	int coordY8();
	// X Coordinates 
	int coordXa(); //{ return 'a'; }
	int coordXi();
};

#endif

