#include "Window.h"
#include "Cell.h"



Window::Window(int size, int level, int wins, int losts, Start *starter, QWidget *parent)
	: QWidget(parent),size(size),level(level),starter(starter),wins(wins),losts(losts)
{
	
	switch (this->level)
	{
		case 0:
			numBombs = int(size / 2); //Easy
			break;
		case 1:
			numBombs = size; //Medium
			break;
		case 2:
			numBombs = 3 * int(size / 2); //Hard
			break;
		case 3:
			numBombs = size * int(size / 2); //Very Hard
			break;
	}
	flags_left = numBombs;
	setFixedSize(800, 600);
	int ax1, ax2;
	ax1 = (700 - size * 50) / 2;
	ax2 = (600 - size * 50) / 2;
	for (int i = 0; i < size; i++)
	{
		std::vector<Cell *> tmp;
		for (int j = 0; j < size; j++)
		{
			Cell *a = new Cell(0, 0, i, j,this, this);
			a->setText(" ");
			a->setGeometry(ax1 + 50 * j, ax2+ 50 * i, 50, 50);
			tmp.push_back(a);
			connect(tmp[j], SIGNAL(lclicked()), tmp[j], SLOT(Operation()));
			connect(tmp[j], SIGNAL(rclicked()), tmp[j], SLOT(onRightClicked()));
		}
		cells.push_back(tmp);
	}
	srand(time(NULL));
	for (int p = 0; p < numBombs; ++p)
	{
		int c1 = (rand() % this->size);
		int c2 = (rand() % this->size);
		if (cells[c1][c2]->Status == 0)
		{
			cells[c1][c2]->Status = 1;
			setNearNum(c1, c2);
		}
		else if(cells[c1][c2]->Status == 1)
		{
			p--;
			continue;
		}

	}
	
	QPushButton *ex = new QPushButton("Exit", this);
	ex->setGeometry(700, 360, 90, 50);
	connect(ex, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
	QPushButton *re = new QPushButton("Next Round", this);
	re->setGeometry(700, 245, 90, 50);
	connect(re, SIGNAL(clicked()), this, SLOT(restart()));
	QPushButton *cl = new QPushButton("Reset", this);
	cl->setGeometry(700, 305, 90, 50);
	connect(cl, SIGNAL(clicked()), this, SLOT(reset()));

	board= new QLabel(this);
	board->setText(" ");
	board->setGeometry(0, 0, 700, 50);
	board->setAlignment(Qt::AlignCenter);

	QString q = QString::fromStdString(std::to_string(this->wins));
	winL = new QLabel(this);
	winL->setText(q);
	winL->setGeometry(750, 50, 50, 50);
	winL->setAlignment(Qt::AlignCenter);
	QLabel *wLlabel = new QLabel(this);
	wLlabel->setText("Wins:");
	wLlabel->setGeometry(700, 50, 50, 50);
	wLlabel->setAlignment(Qt::AlignCenter);

	q = QString::fromStdString(std::to_string(this->losts));
	lostL = new QLabel(this);
	lostL->setText(q);
	lostL->setGeometry(750, 100, 50, 50);
	lostL->setAlignment(Qt::AlignCenter);
	QLabel *lLlabel = new QLabel(this);
	lLlabel->setText("Losts:");
	lLlabel->setGeometry(700, 100, 50, 50);
	lLlabel->setAlignment(Qt::AlignCenter);

	q = QString::fromStdString(std::to_string(this->flags_left));
	flagL = new QLabel(this);
	flagL->setText(q);
	flagL->setGeometry(750, 150, 50, 50);
	flagL->setAlignment(Qt::AlignCenter);
	QLabel *fLlabel = new QLabel(this);
	fLlabel->setText("Flags:");
	fLlabel->setGeometry(700, 150, 50, 50);
	fLlabel->setAlignment(Qt::AlignCenter);
}

void Window::reset()
{
	this->hide();
	starter->reset();
}

void Window::openCells(int i, int j)
{
	CheckWin();
	Cell *tmp = cells[i][j];
	tmp->setStyleSheet("QPushButton:focus {	border: none; outline: none; }");
	if(tmp->isFlagged == 0) tmp->setDisabled(1);
	if (tmp->nearNum == 0 && tmp->isOpened==0 && tmp->Status==0 && tmp->isFlagged == 0)
	{
		tmp->isOpened = 1;
		tmp->setText("");
		tmp->setDisabled(1);
		for (int c1 = -1; c1 <= 1; c1++)
		{
			for (int c2 = -1; c2 <= 1; c2++)
			{
				if (i + c1 < size && i + c1>=0 && j + c2 < size && j + c2>=0)
				{
					openCells(i + c1, j + c2);
				}
					
			}
		}
	}
	else if(tmp->nearNum !=0 && tmp->isOpened == 0 && tmp->Status == 0 && tmp->isFlagged == 0)
	{
		QString q = QString::fromStdString(std::to_string(tmp->nearNum));
		tmp->setText(q);
		tmp->setDisabled(1);
		tmp->isOpened = 1;
	}
	return;
}

void Window::looser()
{
	QFont f("Arial", 14, QFont::Bold);
	board->setFont(f);
	board->setText("<font color='red'>You Lost. :(</font>");
	GState = 0;
	for (int i = 0; i < size ; i++)
	{
		for (int j = 0; j < size; j++)
		{
			Cell *tmp=cells[i][j];
			tmp->setDisabled(1);
			if (tmp->Status == 1)
			{
				if (tmp->isFlagged == 1)
				{
					tmp->setIcon(QIcon(":/Window/Resources/New Project.ico"));
					tmp->setIconSize(QSize(45, 32));
				}
				else
				{
					tmp->setIcon(QIcon(":/Window/Resources/mine.ico"));
					tmp->setIconSize(QSize(32, 32));
				}
				
			}
				
			else
			{
				if (tmp->nearNum == 0)
					tmp->setText("");
				else
				{
					QString q = QString::fromStdString(std::to_string(tmp->nearNum));
					tmp->setText(q);
					tmp->setIconSize(QSize(24, 24));
				}
			}
		}
	}
}

void Window::setNearNum(int i, int j)
{
	for (int c1 = -1; c1 <= 1; c1++)
	{
		for (int c2 = -1; c2 <= 1; c2++)
		{
			if (i + c1 < size && i + c1>=0 && j + c2 < size && j + c2>=0)
			{
				cells[i + c1][j + c2]->nearNum++;
			}
			
		}
	}
	
}

void Window::CheckWin()
{
	int isWin = 1;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			Cell *tmp = cells[i][j];
			if (tmp->Status == 0 && tmp->isOpened == 0)
			{
				isWin = 0;
			}
		}
	}
	if (isWin == 1)
	{
		GState = 1;
		QFont f("Arial", 14, QFont::Bold);
		board->setFont(f);
		board->setText("<font color='green'>You Win! Yeah!</font>");
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				Cell *tmp = cells[i][j];
				tmp->setDisabled(1);
				if (tmp->isOpened == 0)
				{
					if (tmp->isFlagged == 1)
					{
						tmp->setIcon(QIcon(":/Window/Resources/New Project.ico"));
						tmp->setIconSize(QSize(45, 32));
					}
					else
					{
						tmp->setIcon(QIcon(":/Window/Resources/mine.ico"));
						tmp->setIconSize(QSize(32, 32));
					}
				}
					
			}
		}
	}
}

void Window::restart()
{
	starter->restart(GState);
	this->hide();
}
