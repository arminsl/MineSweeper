#include "Window.h"
#include "Cell.h"
#include "Start.h"
#include <qpushbutton.h>
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setWindowIcon(QIcon(":/Window/Resources/appmine.ico"));
	//Window *win;
	Start s;
	s.show();
	
	return a.exec();
}
