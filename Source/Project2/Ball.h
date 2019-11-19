#pragma once
#include "iostream"
#include "time.h"
#include "stdlib.h"
#include "Console.h"
#include <Windows.h>
#include <conio.h>
using namespace std;

enum Dir { STOP = 0, DOWN = 1, LEFTDOWN = 2, RIGHTDOWN = 3, UP = 4, LEFTUP = 5, RIGHTUP = 6 };

class Ball
{
private:
	int _speed = 200;
	int _originalX, _originalY;
	int _x, _y;
	int _color;
	Dir _direction;
	bool _vacham;
public:
	int GetX();
	int GetY();
	int Get_speed();
	int Getcolor();
	void Setcolor(int color);
	void Set_vacham(bool);
	Dir GetDirection();
	void SetDirection(Dir d);
	void Set_speed(int);
public:
	void Reset();
	void RandomDirection();
	void Move();
public:
	Ball(int X, int Y);
};

