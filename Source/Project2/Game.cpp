#include "Game.h"
#include <thread>

// create new Game (constructor)
Game::Game(int w, int h)
{
	_xtopLeft = 1; _ytopLeft = 1;
	_width = w - 5;
	_height = h + 1;
	_quit = false;
	_left1 = 'A'; _right1 = 'D';
	_left2 = 'J'; _right2 = 'L';
	//create new object
	_ball = new Ball(w / 2, h / 2);
	_player1 = new Paddle(15, ((w / 2) + _xtopLeft) - 9, _ytopLeft + 2); // size, originalx, originaly
	_player2 = new Paddle(15, ((w / 2) + _xtopLeft) - 9, _ytopLeft + h - 1);

	// set color to each object
	_player1->Setcolor(11);
	_player2->Setcolor(9);
	_ball->Setcolor(14);
	_leftColor = _rightColor = 61;
}

// intro screen 
void Game::Intro()
{
	int choose;

ScreenIntro:
	system("cls");
	// print intro screen in intro.txt
	ifstream FileIn;
	FileIn.open("intro.txt");
	int lineNumber = 0;
	string str1;
	getline(FileIn, str1);
	cout << str1 << endl;
	while (!FileIn.eof())
	{
		string str;
		getline(FileIn, str);
		lineNumber++;
		for (int i = 0; i < str.length(); i++)
		{
			if (lineNumber == 1)
			{
				textcolor(10);
			}
			else if (lineNumber < 5)
			{
				textcolor(9);
			}
			else if (lineNumber == 15)
			{
				textcolor(12);
			}
			else
			{
				textcolor(11);
			}
			cout << str[i];
			Sleep(10);
		}
		cout << endl;
		textcolor(7);
	}
	FileIn.close();
	//

	// choose mode 1,2,3 or 4
	cin >> choose;
	if (choose == 1)
	{
		system("cls");
		Run();
	}
	if (choose == 2)
	{
		system("cls");
		gotoXY(10, 6);
		textcolor(11);
		cout << "* press one key to play game.";
		gotoXY(10, 8);
		cout << "* using 'a', 'd' or 'j','l' to move paddle  ";
		gotoXY(10, 10);
		cout << "* after game:";

		gotoXY(12, 12);
		cout << "press 1 to continue";
		gotoXY(12, 14);
		cout << "press 2 to exit";
		gotoXY(20, 30);
		textcolor(10);
		cout << "press 4 to return ";
		textcolor(7);
		while (_getch() != 52);
		goto ScreenIntro;
	}

	if (choose == 3)
	{
		system("cls");
		textcolor(4);
		gotoXY(10, 10);
		cout << "****** PROGRAMER : NGUYEN TAN DAT ******";
		gotoXY(10, 12);
		cout << "STUDENT'S ID : 18120308";

		textcolor(5);
		gotoXY(10, 16);
		cout << "****** PROGRAMER : NGUYEN TRUONG DUY ******";
		textcolor(5);
		gotoXY(10, 18);
		cout << "STUDENT'S ID : 18120344";
		gotoXY(20, 30);
		textcolor(10);
		printf("PRESS 4 TO RETURN");
		textcolor(7);
		while (_getch() != 52);
		goto ScreenIntro;
	}

	if (choose == 4)
	{
		cout << endl << endl;
	}
}

// run game after you press 1 key
void Game::Run()
{
	DrawBoard();
	clrscr();
	// create thread run _ball->Move() together Game::Input()
	thread t1(&Ball::Move, _ball);
	HANDLE handle_t1 = t1.native_handle();

	while (1)
	{
		Input();
		Logic();
		// after game, quit screen 
		if (_quit == true)
		{
			SuspendThread(handle_t1); // stop thread 
			system("cls");

			gotoXY((_height + _ytopLeft) / 2, _xtopLeft + 10);
			textcolor(14);
			if (_win == 1)
			{
				cout << "        Player1 WIN" << endl << endl;
			}
			else if (_win == 2)
			{
				cout << "        Player2 WIN" << endl;
			}
			textcolor(13);

			cout << "             Ban co muon tiep tuc choi khong ?" << endl;
			cout << "                   1-Co          2-Khong" << endl;
			int temp;
			cout << "Nhap:  ";
			textcolor(7);
			cin >> temp;
			if (temp == 1)
			{
				_quit = false;
				Reset();
				ResumeThread(handle_t1); // continue thread

			}
			else if (temp == 2)
			{
				exit(0);
			}
		}
	}
}

// get input key and move the paddle
void Game::Input()
{
	int x_paddle1 = _player1->GetX();
	int y_paddle1 = _player1->GetY();
	int x_paddle2 = _player2->GetX();
	int y_paddle2 = _player2->GetY();
	if (_kbhit())
	{
		// get key 
		char temp = toupper(_getch());
		{
			// temp = A -> player1 move left
			if (temp == _left1)
			{
				if (x_paddle1 > _xtopLeft + 1)
				{
					_player1->moveLeft();
				}
			}
			// temp = D -> player1 move right
			if (temp == _right1)
			{
				if (x_paddle1 < _xtopLeft + _width - _player1->Getsize() - 1)
				{
					_player1->moveRight();
				}
			}
			// temp = J -> player1 move left
			if (temp == _left2)
			{
				if (x_paddle2 > _xtopLeft + 1)
				{
					_player2->moveLeft();
				}
			}
			// temp = L -> player1 move right
			if (temp == _right2)
			{
				if (x_paddle2 < _xtopLeft + _width - _player2->Getsize() - 1)
				{
					_player2->moveRight();
				}
			}

			if (_ball->GetDirection() == STOP)
			{
				_ball->RandomDirection();
			}
		}
	}
}

// process when ball impact objects
void Game::Logic()
{
	int ballx = _ball->GetX();
	int bally = _ball->GetY();
	int pl1x = _player1->GetX();
	int pl2x = _player2->GetX();
	int pl1y = _player1->GetY();
	int pl2y = _player2->GetY();

	// top paddle
	if (bally - 1 == pl1y)
	{
		for (int i = 0; i < _player1->Getsize(); i++)
		{
			if (ballx == pl1x + i)
			{
				_ball->Set_vacham(true);
				_ball->SetDirection((Dir)(rand() % 3 + 1));
			}
		}
	}

	// bot padde
	if (bally + 1 == pl2y)
	{
		for (int i = 0; i < _player2->Getsize(); i++)
		{
			if (ballx == pl2x + i)
			{
				_ball->Set_vacham(true);
				_ball->SetDirection((Dir)(rand() % 3 + 4));
			}
		}
	}

	// left wall
	if (ballx - 1 == _xtopLeft)
	{
		_leftColor = rand() % 15 + 48;
		if (_ball->GetDirection() == LEFTDOWN)
		{
			_ball->SetDirection(RIGHTDOWN);
		}
		else if (_ball->GetDirection() == LEFTUP)
		{
			_ball->SetDirection(RIGHTUP);
		}
	}

	// right wall
	if (ballx + 1 == _xtopLeft + _width - 1)
	{
		_rightColor = rand() % 15 + 48;
		if (_ball->GetDirection() == RIGHTDOWN)
		{
			_ball->SetDirection(LEFTDOWN);
		}
		else if (_ball->GetDirection() == RIGHTUP)
		{
			_ball->SetDirection(LEFTUP);
		}
	}
	// top wall
	if (bally - 1 == _xtopLeft)
	{
		_win = 2;
		_quit = true;
	}
	//bot wall
	if (bally + 1 == _xtopLeft + _height - 1)
	{
		_win = 1;
		_quit = true;
	}


}

// print board and objects with their color
void Game::DrawBoard()
{
	char top = 220, bot = 223, left = 221, right = 222;
	char center = 176;

	// draw top edge
	textcolor(61);
	gotoXY(_xtopLeft, _ytopLeft);
	for (int i = 0; i <= _width; i++)
	{
		cout << top;
	}
	// draw bot edge
	gotoXY(_xtopLeft, _height + _ytopLeft);
	for (int i = 0; i <= _width; i++)
	{
		cout << bot;
	}
	// draw left and right edge
	for (int i = _ytopLeft + 1; i < _ytopLeft + _height; i++)
	{
		textcolor(_leftColor);
		gotoXY(_xtopLeft, i);
		cout << left;
		textcolor(_rightColor);
		gotoXY(_xtopLeft + _width, i);
		cout << right;
	}
	textcolor(7);
	//draw 2 paddle
	textcolor(_player1->Getcolor());
	gotoXY(_player1->GetX(), _player1->GetY());
	for (int i = 0; i < _player1->Getsize(); i++)
	{
		cout << bot;
	}
	textcolor(7);
	textcolor(_player2->Getcolor());
	gotoXY(_player2->GetX(), _player2->GetY());
	for (int i = 0; i < _player2->Getsize(); i++)
	{
		cout << bot;
	}
	textcolor(7);
	textcolor(7);
}

// reset data in new game
void Game::Reset()
{
	_ball->Reset();
	_player1->Reset();
	_player2->Reset();
	system("cls");
	DrawBoard();

	gotoXY(_ball->GetX(), _ball->GetY());
}

Game::~Game()
{
	delete _player1, _player2, _ball;
}