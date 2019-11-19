#pragma once
#include <Windows.h>
#include "iostream"
#include "Console.h"
#include <thread>
using namespace std;
class Paddle
{
private:
	int _originalx, _originaly;
	int _x, _y;
	int _size;
	int _color;
public:
	int GetX();
	int GetY();
	int Getsize();
	int Getcolor();
	void Setcolor(int color);
	void moveLeft();
	void moveRight();
	void Reset();

public:
	Paddle();
	Paddle(int, int, int);
	~Paddle();

};

