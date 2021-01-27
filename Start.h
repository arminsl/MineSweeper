#pragma once
#include "Window.h"
#include <QWidget>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <QErrorMessage>

class Start : public QWidget
{
	friend class Window;
	Q_OBJECT
protected slots:
	void ShowWindow();
public:
	Start(QWidget *parent= Q_NULLPTR);
	~Start();
	int si;
	int le;
	int wins;
	int losts;
	QPushButton *b;
	QPushButton *e;
	QLabel *q;
	QLabel *name;
	QLineEdit *Tsize;
	QLineEdit *Tlevel;
	QLabel *sizeL;
	QLabel *levelL;
	QErrorMessage error;
	Window *Pwin;
	void restart(int isWon);
	void reset();
};
