# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#	FileName	Makefile
#
#	Authors		Dean Marsden		29143332
#			Simon van Dyk		10266764
#
#	Date		October 2010
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

CC = g++
FLAGS = -Wall -Werror -pedantic -g -O3

TARGET = FantasyChess
EXT =
TARNAME = fantasy-chess.tgz

OBJECTS = Coordinate.o ReachStrategy.o \
		  PStack.o \
		  FootSoldier.o Knight.o King.o Dragon.o Phantom.o Healer.o Necromancer.o \
		  SpellDecorator.o \
		  Piece.o \
		  Board.o TwoDBoard.o\
		  BoardCreator.o \
		  SetupStrategy.o CMDInterpreter.o \
		  Players.o PlayerSwitch.o \
		  Game.o GameLogic.o \
		  main.o

XTRAFILES = ../fixtures/fixedStaleMate ../fixtures/fixedTeam1Wins ../fixtures/fixedTeam2Wins

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Generic variables, rules, patterns & recipes:
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

SOURCES = $(OBJECTS:.o=.C)
DEPENDENCIES = $(OBJECTS:.o=.d)

# Linking rule:
.PHONY: all
all: $(OBJECTS)
	@echo "---Linking objects---"
	$(CC) $(FLAGS) $(OBJECTS) -o $(TARGET)$(EXT)

# Compilation pattern rule:
%.o: %.C %.d
	$(CC) $(FLAGS) -c $< -o $@

# Dependencies pattern rule:
%.d: %.C
	@set -e; \
	rm -f $@; \
	$(CC) -MM $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# If you running make clean, don't make the .d's
ifneq ($(MAKECMDGOALS),clean)
sinclude $(DEPENDENCIES)
endif

# Custom commands:
.PHONY: clean
clean:
	clear
	-rm -f $(TARGET)$(EXT) *.o *~ *.d*

.PHONY: run
run:
	clear
	./$(TARGET)$(EXT)

.PHONY: gdb
gdb:
	clear
	make
	gdb $(TARGET)$(EXT)

.PHONY: team1wins
team1wins:
	make
	clear
	cat ../fixtures/team1wins | ./$(TARGET)$(EXT)

.PHONY: team2wins
team2wins:
	make
	clear
	cat ../fixtures/team2wins | ./$(TARGET)$(EXT)

.PHONY: stalemate
stalemate:
	make
	clear
	cat ../fixtures/stalemate | ./$(TARGET)$(EXT)

.PHONY: tar
tar:
	tar -zcvf $(TARNAME) Makefile *.C *.h $(XTRAFILES)

.PHONY: dep
dep:
	@echo "Dependencies list:"
	g++ -MM *.C

.PHONY: ll
ll:
	make -j

.PHONY: sing
sing:
	say -v Cellos "di di di di di di di di di di di di \
	di di di di di di di di di di di di di di"

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Comments:
#
# .PHONY indicates that the rules' name is in fact a rule
#        and not the name of a file in the same directory
#
# The pattern rules create a .d file for every .C file in
#        the current directory containing a list of dependencies,
#        it then uses that .d file to include the relevent
#        classes in the object file
#
# The OBJECTS variable must be a list of .o files that
#        correspond to each .C file. It is important that
#        these are in the correct order(low->high) and that
#        the .C with the main function is mentioned last.
#
# All the makefile requires is that you type the .o files
#        needed in the correct order and specify a executable
#        name for the TARGET variable.
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
