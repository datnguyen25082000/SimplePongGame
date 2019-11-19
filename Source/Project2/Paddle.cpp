#include "Paddle.h"

// get x(y) value of object
int Paddle::GetX()
{
	return _x;
}
int Paddle::GetY()
{
	return _y;
}
// get and set color of Paddle object
int Paddle::Getcolor()
{
	return _color;
}
void Paddle::Setcolor(int color)
{
	_color = color;
}

int Paddle::Getsize()
{
	return _size;
}

// reset paddle with old data
void Paddle::Reset()
{
	_x = _originalx;
	_y = _originaly;
}

// Paddle move left
void Paddle::moveLeft()
{
	char bot = 223;
	textcolor(_color);
	gotoXY(_x + this->Getsize() - 1, _y);
	cout << ' ';
	_x--;
	gotoXY(_x, _y);
	cout << bot;
	textcolor(7);
	Sleep(5);
}

// Paddle move right
void Paddle::moveRight()
{
	char bot = 223;
	textcolor(_color);
	gotoXY(_x, _y);
	cout << ' ';
	_x++;
	gotoXY(_x + this->Getsize() - 1, _y);
	cout << bot;
	textcolor(7);
	Sleep(5);
}

Paddle::Paddle()
{

}

// constructor to create new object with parameter
Paddle::Paddle(int size, int originalx, int originaly)
{
	_originalx = originalx;
	_originaly = originaly;
	_x = _originalx;
	_y = _originaly;
	_size = size;
}

Paddle::~Paddle()
{

}