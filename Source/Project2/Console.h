#pragma once
#include <Windows.h>
#include <thread>

void ResizeConsole(int width, int height);

void textcolor(int color);

void gotoXY(int X, int Y);

void FixConsoleWindow();

void clrscr();

void ancontro();   // An con tro chuot