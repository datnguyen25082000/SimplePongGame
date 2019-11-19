#include "Ball.h"

// get x(y) value of ball object
int Ball::GetX() { return _x; }
int Ball::GetY() { return _y; }

// lay va gan gia tri cho bien _direction (huong di chuyen cua qua bong)
// get and set value to _direction(direction of ball)
Dir Ball::GetDirection() { return _direction; }
void Ball::SetDirection(Dir d) { _direction = d; }

// get and set color of ball 
int Ball::Getcolor()
{
	return _color;
}
void Ball::Setcolor(int color)
{
	_color = color;
}

// reset data to start new game
void Ball::Reset()
{
	_x = _originalX;
	_y = _originalY;
	_direction = STOP;
	_speed = 200;
}

void Ball::RandomDirection()
{
	_direction = (Dir)(rand() % 6 + 1); //random direction of ball
}

void Ball::Move()
{
	while (1)
	{
		// clear ball at old position
		gotoXY(_x, _y);
		cout << ' ';
		if (_vacham == true)
		{
			_speed = _speed - _speed / 10;
		}
		switch (_direction)
		{
		case STOP:
			break;
		case UP:
			_y--;
			break;
		case RIGHTUP:
			_y--;
			_x++;
			break;
		case LEFTUP:
			_y--;
			_x--;
			break;
		case DOWN:
			_y++;
			break;
		case RIGHTDOWN:
			_y++;
			_x++;
			break;
		case LEFTDOWN:
			_y++;
			_x--;
			break;
		default:
			break;
		}
		// print ball at new position with color
		gotoXY(_x, _y);
		textcolor(_color);
		cout << 'O';

		textcolor(7);
		// sleep : feature of speed of ball
		Sleep(_speed);
		_vacham = false;
	}
}

// constructor function to create new object
Ball::Ball(int X, int Y)
{
	_originalX = X;
	_originalY = Y;
	_x = X;
	_y = Y;
	_direction = STOP;
}

// get and set _speed value of ball
int Ball::Get_speed()
{
	return _speed;
}
void Ball::Set_speed(int speed)
{
	_speed = speed;
}

void Ball::Set_vacham(bool value)
{
	_vacham = value;
}