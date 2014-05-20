#include <QApplication>
#include <QWidget>
#include <QThread>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
#ifdef Q_OS_MAC
	QThread::currentThread()->setPriority(QThread::HighPriority);
#endif
	MainWindow window;
	window.show();
	return app.exec();
}

