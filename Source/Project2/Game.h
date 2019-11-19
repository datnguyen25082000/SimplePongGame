#pragma once
#include "Console.h"
#include "Paddle.h"
#include "Ball.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "thread"
#include "fstream"

using namespace std;
class Game
{
private:
	int _xtopLeft, _ytopLeft;
	int _width, _height;
	char _left1, _right1, _left2, _right2;
	bool _quit;
	int _win;
	int _leftColor;
	int _rightColor;
	Paddle* _player1;
	Paddle* _player2;
	Ball* _ball;
public:
	void Intro();
	void Run();
	void Logic();
	void DrawBoard();
	void Input();
	void DrawPaddle(char, char);
	void Reset();
public:
	Game(int, int);
	~Game();
};

