#pragma once
#include "MyFunc.h"


struct DnData {

	Figure* Ffigure;
	int prevX, prevY;

	DnData(Figure* _ffigure, int x, int y) : Ffigure(_ffigure), prevX(x), prevY(y) {};

};

