#pragma once
#include "MyFunc.h"


struct DnData {

	Figure* Ffigure;
	QPoint prevPos;

	DnData(Figure* _ffigure, int x, int y) : Ffigure(_ffigure), prevPos({x, y}) {};

};

