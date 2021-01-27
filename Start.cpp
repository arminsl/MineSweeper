#include "Start.h"

Start::Start(QWidget *parent)
	: QWidget(parent),wins(0),losts(0)
{
	

	Tsize = new QLineEdit(this);
	Tsize->setText("5");
	Tsize->setAlignment(Qt::AlignCenter);
	Tsize->setGeometry(125, 100, 50, 30);
	Tlevel = new QLineEdit(this);
	Tlevel->setText("1");
	Tlevel->setAlignment(Qt::AlignCenter);
	Tlevel->setGeometry(125, 140, 50, 30);

	sizeL=new QLabel(this);
	levelL=new QLabel(this);
	sizeL->setText("Size (>=5 , =<10) ");
	sizeL->setGeometry(0, 110, 125, 30);
	sizeL->setAlignment(Qt::AlignRight);
	levelL->setText("Level (>=0 , <=3) ");
	levelL->setGeometry(0, 150, 125, 30);
	levelL->setAlignment(Qt::AlignRight);
	
	setFixedSize(300, 400);
	b = new QPushButton("Start!", this);
	b->setGeometry(100, 250, 100, 50);
	connect(b, SIGNAL(clicked()), this, SLOT(ShowWindow()));
	e = new QPushButton("Exit", this);
	e->setGeometry(100, 310, 100, 50);
	connect(e, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
	q = new QLabel(this);
	q->setText("Welcom to MineSweeper!");
	q->setGeometry(50, 30, 200, 20);
	q->setAlignment(Qt::AlignCenter);
	name = new QLabel(this);
	name->setText("Armin Soleymaniniya");
	name->setGeometry(50, 50, 200, 20);
	name->setAlignment(Qt::AlignCenter);
}

Start::~Start()
{
}

void Start::restart(int isWon)
{
	if (isWon)
		wins++;
	else
		losts++;
	Pwin = new Window(si, le,wins,losts,this);
	Pwin->show();

}

void Start::reset()
{
	wins = 0;
	losts = 0;
	this->show();
}


void Start::ShowWindow()
{
	si = this->Tsize->text().toInt();
	le = this->Tlevel->text().toInt();
	if (si < 5 || si>10 || le < 0 || le>3)
	{
		error.showMessage("Invalid Values.");
	}
	else
	{
		Pwin = new Window(si, le,0,0,this);
		Pwin->show();
		this->hide();
	}
	
}