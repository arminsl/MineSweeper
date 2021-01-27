#pragma once
#include <QObject>
#include <QPushButton>
#include <Window.h>
#include <QString>
#include <qpair.h> 
#include <QMouseEvent>
#include <string>
#include <Windows.h>

class Window;
class Cell : public QPushButton
{
	friend class Window;
	Q_OBJECT
		
protected slots:
	void Operation();
	void mousePressEvent(QMouseEvent *e);
	void onRightClicked();
signals:
	void rclicked();
	void lclicked();

public:
	Cell(QWidget *parent=0);
	Cell(int nn,int Stat,int fi,int si, Window *win,QWidget *parent);
	~Cell();
private:
	int nearNum = 0; 
	int Status = 0;
	int isOpened = 0;
	int isFlagged = 0;
	QPair<int, int> CId;
	Window *win;
	void ChangeBoard(QString s);
	void clearBoard();
};
