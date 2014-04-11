# Fantasy Chess

Fantasy Chess is a command line game written in C++ where the chess pieces have
special characteristics.

Each piece has it's own special movement and attack.


## Design

### Objective

The objective of this assignment was to build a system rich with design patterns
such that is is easy to compose functionality, maintain, extend and many more
niceties that come with GOF design patterns.

The design is pretty well documented in *guide.doc* and has many accompanying
images of UML diagrams in the *UML-Images.zip*, and the UML diagrams in umbrello
in *MASTER UML.xmi*

### GOF Design Patterns

Overview

![Overview Class Diagram](https://dl.dropboxusercontent.com/u/4042547/class-diagram.jpeg)

#### Creational Patterns

*Factory Method* is used to create a board of user-specified dimensions, although
only a 2D board is implemented

![Factory Method](https://dl.dropboxusercontent.com/u/4042547/factory-method.jpeg)


*Prototype* is used to create prototypical instances of the respective piece
types aiding the creation process

![Prototype](https://dl.dropboxusercontent.com/u/4042547/prototype.jpeg)


#### Structural Patterns

*Decorator* harnesses recursive composition to 'decorate' pieces with their appropriate
spells


#### Behavioural Patterns

*State* is used to control the players turn and alternate between teams

*Strategy* is used to setup the board according to a random or fixed placement
of pieces and to transparently treat each piece composing of a reach strategy
that affects the way it moves

![Strategy](https://dl.dropboxusercontent.com/u/4042547/strategy.jpeg)


*Interpreter* is used to parse user input into data the program can process (
this pattern is responsible for much of the preemptive error checking and validation)

![Interpreter](https://dl.dropboxusercontent.com/u/4042547/interpreter.jpeg)


*Template Method* is defined by the 'Team turn cycle' which is comprised of
primitive operations of select, spell and move. This pattern looks surprisingly
like strategy because all of the 'primitive operations' are redefined in subclasses


## Contents

The repo consists of

* `src/`
* `fixtures/`
* `documentation/`
* `README.md`
* `valgrind-memory-check`

The `src/Makefile` is used to perform all operations.


## Getting Started

### I wanna play dammit

To build & run the game

* `$ git clone git@github.com:sighmin/fantasy-chess` to clone the repo
* `$ cd fantasy-chess/src && make && make run` to build & run

Once built you can run it

* `$ make run` or
* `$ ./FantasyChess`


### Tell me more

It should compile on any *nix system with g++.

A full list of available commands

* `$ make`
 * Builds the executable
* `$ make ll`
 * Builds the executable in parallel (linking still takes a while)
* `$ make run`
 * Runs the game
* `$ make clean`
 * Removes all temporary build files (nice to run after you've built)
* `$ make gdb`
 * Starts gdb to run the game to check for memory leaks
* `$ make tar`
 * Compresses the source files and makefile to share
* `$ make dep`
 * Shows auto-generated dependency tree
* `$ make sing`
 * Sings a tunes (turn on your volume)
* `$ make team1wins`
 * Run a set game to test the outcome
* `$ make team2wins`
 * Run a set game to test the outcome
* `$ make stalemate`
 * Run a set game to test the outcome


## Rules

### Game logic

The game is setup as 2 teams of equal, even number of players, playing against
one another on one board, taking turns. Every turn a player can cast all the
spells of every piece on the board, but can only make one move of a piece.

Each piece has a life force, a unique move, and possibly spells.

Every turn a player first selects a piece. Once a piece is selected it will show
the piece's specific characteristics. The piece can then accept commands like a
spell, or a move. Once a move is made, the game changes turn to the alternate
team, and gives the next player on that team a chance to play.


### Game pieces

1. FootSoldier, F
 * Life : 6
 * Move : 2 squares in any direction


2. Knight, K
 * Life : 10
 * Move : L shapes of 3 + 1 move


3. Phantom, P
 * Life : 5
 * Move : 2 squares in any direction
 * Spells : Teleport in any direction. Each square you move, costs your piece one life force


4. Necromancer, N
 * Life : 6
 * Move : 1 square in any direction
 * Spells : Resurrect the last piece that died by sacrificing any piece within a 3 square radius


5. Healer, H
 * Life : 6
 * Move : 5 squares in diagonals
 * Spells : Restore any friendly pieces' life within a 3 square radius
 * *This spell has no effect on Phantoms*


6. King, X
 * Life : 30
 * Move : 3 squares in any direction
 * Spells : Swap king with a friendly piece any where on the board
 * *You may only cast this once per game!*



## License

The MIT License (MIT)

Copyright © 2010 Simon van Dyk, Dean Marsden

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
