#include <iostream>
#include "Console.h"
#include "Game.h"
using namespace std;

int main()
{
	char temp;
	// set size console window and fix it
	ResizeConsole(500, 600);
	FixConsoleWindow();
	ancontro();
	// Create new Game Object
	Game game(60, 30);
	game.Intro();
	return 1;
}


