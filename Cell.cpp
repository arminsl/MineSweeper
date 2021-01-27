#include "Cell.h"


Cell::Cell(QWidget *parent)
	: QPushButton(parent)
{
	
}

Cell::Cell(int nn, int Stat, int fi, int si,Window *win, QWidget *parent)
	: QPushButton(parent),Status(Stat),isOpened(0),nearNum(nn),win(win), isFlagged(0)
{
	CId = qMakePair(fi, si);
	this->setText("");
}


Cell::~Cell()
{
}

void Cell::Operation()
{
	clearBoard();
	if (this->isFlagged==1)
	{
		clearBoard();
		ChangeBoard("Flagged! First Unflag The Cell.");
	}
	else
	{
		this->setStyleSheet("QPushButton:focus {	border: none; outline: none; }");
		if (this->Status == 1)
			win->looser();
		else
			//win->CheckWin();
			win->openCells(this->CId.first, this->CId.second);
			win->CheckWin();
	}
	
}

void Cell::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::RightButton)
		emit rclicked();
	if (e->button() == Qt::LeftButton)
		emit lclicked();
}

void Cell::onRightClicked()
{
	clearBoard();
	if (this->isFlagged==1)
	{
		//this->setText("");
		this->isFlagged = 0;
		this->setIcon(QIcon());
		this->setIconSize(QSize(32, 32));
		win->flags_left++;
		QString q = QString::fromStdString(std::to_string(win->flags_left));
		win->flagL->setText(q);
	}
		
	else if (win->flags_left > 0)
	{
		this->isFlagged = 1;
		this->setIcon(QIcon(":/Window/Resources/clipart786779_wAa_icon.ico"));
		this->setIconSize(QSize(32, 32));
		//this->setText("F");
		win->flags_left--;
		QString q = QString::fromStdString(std::to_string(win->flags_left));
		win->flagL->setText(q);
	}
		
	win->CheckWin();
}
void Cell::ChangeBoard(QString s)
{
	QFont f("Arial", 12);
	win->board->setFont(f);
	win->board->setText(s);
}

void Cell::clearBoard()
{
	ChangeBoard("");
}