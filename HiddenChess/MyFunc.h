#pragma once
#include <QtWidgets>
#include <qmap.h>
#include<qstring.h>


class Figures {

	enum FigureType {
		no,
		pawn,
		king,
		queen, 
		rook,
		knight,
		bishop
	};

	const QString a = "../HiddenChess/Figures/";
	const QString w = "W";
	const QString b = "B";

	QMap<FigureType, QString> FigureImages =
											{ {no, ""}, {pawn,"p.png"}, {king, "k.png"},
							{queen, "q.png"},{rook, "r.png"}, {knight, "n.png"},
				{bishop, "b.png"} };



};