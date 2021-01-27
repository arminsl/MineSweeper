#pragma once
#include<vector>
#include <QtWidgets/QWidget>
#include <qpushbutton.h>
#include <Cell.h>
#include <QtWidgets/QApplication>
#include <qmenu.h>
#include <qmenubar.h>
#include <QLabel>
#include <time.h>
#include <cstdlib>
#include <Start.h>

class Window : public QWidget
{
	friend class Cell;
	friend class Start;
	Q_OBJECT

public:
	Window(int size,int level,int wins,int losts,Start *starter,QWidget *parent = Q_NULLPTR);

protected slots:
	void restart();
	void reset();
private:
	std::vector<std::vector<Cell *>> cells;
	int GState = 0;
	int wins;
	int losts;
	int flags_left;
	Start *starter;
	QLabel *board;
	QLabel *winL;
	QLabel *lostL;
	QLabel *flagL;
	int size=0;
	int level=0;
	int numBombs = 1;
	void openCells(int i,int j);
	void looser();
	void setNearNum(int i, int j);
	void CheckWin();
};
