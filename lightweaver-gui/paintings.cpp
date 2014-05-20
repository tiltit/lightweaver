#include <QFileDialog>
#include <QStringList>
#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDebug>
#include <random>
#include <QColor>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QFileDialog>

#include "MainWindow.h"

using namespace cv;

QVector<QColor*>* MainWindow::computeGoldenRatioColors(double startHue,double saturation, double value, int size) 
{
	int i;
	double h = startHue;
	QVector<QColor*> *v = new QVector<QColor*>;

	for(i=0;i!=size;++i) {
		QColor *color = new QColor(255,255,255);
		h = fmod( startHue + (0.618033988749895 * i), 1.0);
		color->setHsvF(h, saturation, value);
		v->push_back(color);
	}

	return v;
}

void MainWindow::colorImage()
{
	int x, y;
	Mat image;
	QColor color;
	
	QFileDialog *dialog = new QFileDialog();
	dialog->setNameFilter("PNG Files (*.png)");
	dialog->setOption(QFileDialog::ReadOnly);
	//dialog->setOption(QFileDialog::DontUseNativeDialog);
	dialog->setDirectory(".");
	QStringList fileNames;
	if (dialog->exec()) {
		fileNames = dialog->selectedFiles();
		QString fileName = fileNames.at(0);
		image = imread(fileName.toStdString(), CV_LOAD_IMAGE_COLOR);

		for( y=0; y!=image.rows; ++y) {
			if((y%2) == 0) {
				for(x=0;x!=image.cols;++x) {
					color.setBlue(image.data[((y*image.cols)+x)*3]);
					color.setGreen(image.data[((y*image.cols)+x)*3+1]);
					color.setRed(image.data[((y*image.cols)+x)*3+2]);
					motorControl.setLedColor(color);
					motorControl.commandMotor1(3, -4);
				}
			} else {
				for(x=image.cols-1;x!=-1;--x) {
					color.setBlue(image.data[((y*image.cols)+x)*3]);
					color.setGreen(image.data[((y*image.cols)+x)*3+1]);
					color.setRed(image.data[((y*image.cols)+x)*3+2]);
					motorControl.setLedColor(color);
					motorControl.commandMotor1(3, 4);
				}
			}
			motorControl.commandMotor2(6, -4);
		}
		color.setRed(0);
		color.setGreen(0);
		color.setBlue(0);
		motorControl.setLedColor(color);
		motorControl.releaseMotor1();
		motorControl.releaseMotor2();
	}	
}

void MainWindow::colorStripes()
{
	QColor color;
	int x, y;

	int number = 0;
	bool onOff = false;

	int width = 100;
	int height = 100;

	int stepSize = 16;


	std::default_random_engine generator;
	std::normal_distribution<double> onDistribution(30.0,10.0);
	std::normal_distribution<double> offDistribution(40.0,20.0);
	QVector<QColor*> *colorVector;
	colorVector = computeGoldenRatioColors(0.01,0.7,1,100);

	motorControl.openShutter();
	for (y=0;y!=height;++y) {
		for(x=0;x!=width; x++) {
			motorControl.setLedColor(color);
			if (number<=0) {
				if(onOff) {
					color.setRed(0);
					color.setGreen(0);
					color.setBlue(0);
					motorControl.setLedColor(color);
					onOff = false;
					number = int(offDistribution(generator));
				} else {
					QColor *pColor = colorVector->at(rand() % 100);
					color.setRed(pColor->red());
					color.setGreen(pColor->green());
					color.setBlue(pColor->blue());

					motorControl.setLedColor(color);
					onOff = true;
					number = int(onDistribution(generator));
				}
			}

			motorControl.commandMotor1(3, -stepSize);


			number--;

		}
		motorControl.setLedColor(QColor(0,0,0));
		motorControl.commandMotor1(3, stepSize * width);		

		motorControl.commandMotor2(6, -stepSize);
	}
	motorControl.closeShutter();


	// Reset x axis to initial position if the width is uneven
	if( width%2 != 0) {
		motorControl.commandMotor1(6, stepSize * width);
	}

	// Reset y axis to initial position
	motorControl.commandMotor2(6, stepSize * height);

	motorControl.releaseMotor1();
	motorControl.releaseMotor2();
}

void MainWindow::lineWorld()
{
	QColor color;
	Mat image;
	std::default_random_engine generator;
	std::normal_distribution<double> onDistribution(30.0,10.0);
	std::normal_distribution<double> offDistribution(10.0,5.0);
	int x, y;

	int number = 0;
	bool onOff = false;

	int width = 100;
	int height = 100;

	int stepSizeX = 11;
	int stepSizeY = 12;

	QFileDialog *dialog = new QFileDialog();
	dialog->setNameFilter("PNG Files (*.png)");
	dialog->setOption(QFileDialog::ReadOnly);
	//dialog->setOption(QFileDialog::DontUseNativeDialog);
	dialog->setDirectory(".");
	QStringList fileNames;
	if (dialog->exec()) {
		fileNames = dialog->selectedFiles();
		QString fileName = fileNames.at(0);
		image = imread(fileName.toStdString(), CV_LOAD_IMAGE_COLOR);
		height = image.rows;
		width = image.cols;


			motorControl.openShutter();
			for (y=0;y!=height;++y) {
				for(x=0;x!=width; x++) {
					motorControl.setLedColor(color);
					if (number<=0) {
						if(onOff) {
							color.setRed(0);
							color.setGreen(0);
							color.setBlue(0);
							motorControl.setLedColor(color);
							onOff = false;
							number = int(offDistribution(generator));
						} else {
							onOff = true;
							number = int(onDistribution(generator));
						}
					}

					if(onOff) {
						color.setBlue( image.data[((y*image.cols)+x)*3] );
						color.setGreen( image.data[((y*image.cols)+x)*3+1] );
						color.setRed( image.data[((y*image.cols)+x)*3+2] );
						motorControl.setLedColor(color);
					}

					motorControl.commandMotor1(3, -stepSizeX);


					number--;

				}
				motorControl.setLedColor(QColor(0,0,0));
				motorControl.commandMotor1(3, stepSizeX * width);		

				motorControl.commandMotor2(6, -stepSizeY);
			}
			motorControl.closeShutter();


			// Reset x axis to initial position if the width is uneven
			if( width%2 != 0) {
				motorControl.commandMotor1(6, stepSizeX * width);
			}

			// Reset y axis to initial position
			motorControl.commandMotor2(6, stepSizeY * height);

			motorControl.releaseMotor1();
			motorControl.releaseMotor2();


	}
}

void MainWindow::lineWorldColor()
{
	QColor color;
	QColor *pColor;
	Mat image;
	std::default_random_engine generator;
	std::normal_distribution<double> onDistribution(30.0,10.0);
	std::normal_distribution<double> offDistribution(10.0,5.0);

	QVector<QColor*> *colorVector;
	colorVector = computeGoldenRatioColors(0.01,0.99,1,100);

	int x, y;

	int number = 0;
	bool onOff = false;

	int width = 100;
	int height = 100;

	int stepSizeX = 11;
	int stepSizeY = 12;

	QFileDialog *dialog = new QFileDialog();
	dialog->setNameFilter("PNG Files (*.png)");
	dialog->setOption(QFileDialog::ReadOnly);
	//dialog->setOption(QFileDialog::DontUseNativeDialog);
	dialog->setDirectory(".");
	QStringList fileNames;
	if (dialog->exec()) {
		fileNames = dialog->selectedFiles();
		QString fileName = fileNames.at(0);
		image = imread(fileName.toStdString(), CV_LOAD_IMAGE_COLOR);
		height = image.rows;
		width = image.cols;


			motorControl.openShutter();
			for (y=0;y!=height;++y) {
				for(x=0;x!=width; x++) {
					motorControl.setLedColor(color);
					if (number<=0) {
						if(onOff) {
							color.setRed(0);
							color.setGreen(0);
							color.setBlue(0);
							motorControl.setLedColor(color);
							onOff = false;
							number = int(offDistribution(generator));
						} else {
							onOff = true;
							number = int(onDistribution(generator));
							pColor = colorVector->at(rand() % 100);
						}
					}

					if(onOff) {
						color.setBlue((image.data[((y*image.cols)+x)*3] / 4 * 3) + ( pColor->blue() / 4 ));
						color.setGreen((image.data[((y*image.cols)+x)*3+1] / 4 * 3)  + ( pColor->green() / 4));
						color.setRed((image.data[((y*image.cols)+x)*3+2] / 4 * 3) + ( pColor->red() / 4));
						motorControl.setLedColor(color);
					}

					motorControl.commandMotor1(3, -stepSizeX);


					number--;

				}
				motorControl.setLedColor(QColor(0,0,0));
				motorControl.commandMotor1(3, stepSizeX * width);		

				motorControl.commandMotor2(6, -stepSizeY);
			}
			motorControl.closeShutter();


			// Reset x axis to initial position if the width is uneven
			if( width%2 != 0) {
				motorControl.commandMotor1(6, stepSizeX * width);
			}

			// Reset y axis to initial position
			motorControl.commandMotor2(6, stepSizeY * height);

			motorControl.releaseMotor1();
			motorControl.releaseMotor2();


	}
}

void MainWindow::perfectImage() 
{
	QColor color;
	Mat image;

	int x, y;

	int width, height;

	int stepSizeX = 11;
	int stepSizeY = 12;

	QFileDialog *dialog = new QFileDialog();
	dialog->setNameFilter("PNG Files (*.png)");
	dialog->setOption(QFileDialog::ReadOnly);
	//dialog->setOption(QFileDialog::DontUseNativeDialog);
	dialog->setDirectory(".");
	QStringList fileNames;
	if (dialog->exec()) {
		fileNames = dialog->selectedFiles();
		QString fileName = fileNames.at(0);
		image = imread(fileName.toStdString(), CV_LOAD_IMAGE_COLOR);
		height = image.rows;
		width = image.cols;

			motorControl.commandMotor1(3, 5);  // Go a few steps back
			motorControl.openShutter();
			for (y=0;y!=height;++y) {
				motorControl.commandMotor1(3, -5);  // Go a few steps forth
				for(x=0;x!=width; x++) {
					motorControl.setLedColor(color);
					
					color.setBlue( image.data[((y*image.cols)+x)*3] );
					color.setGreen( image.data[((y*image.cols)+x)*3+1] );
					color.setRed( image.data[((y*image.cols)+x)*3+2] );
					motorControl.setLedColor(color);

					motorControl.commandMotor1(3, -stepSizeX);

				}
				motorControl.setLedColor(QColor(0,0,0));
				motorControl.commandMotor1(3, stepSizeX * width);
				motorControl.commandMotor1(3, 5);  // Go a few steps back

				motorControl.commandMotor2(6, -stepSizeY);
			}
			motorControl.closeShutter();


			// Reset x axis to initial position if the width is uneven
			if( width%2 != 0) {
				motorControl.commandMotor1(6, stepSizeX * width);
			}

			// Reset y axis to initial position
			motorControl.commandMotor2(6, stepSizeY * height);

			motorControl.releaseMotor1();
			motorControl.releaseMotor2();


	}
}

void MainWindow::colorLinesFull()
{
	QColor color;
	QColor *pColor;
	Mat image;
	std::default_random_engine generator;
	std::normal_distribution<double> onDistribution(30.0,10.0);

	QVector<QColor*> *colorVector;
	colorVector = computeGoldenRatioColors(0.01,0.99,1,100);

	int x, y;

	int number = 0;

	int width, height;

	int stepSizeX = 11;
	int stepSizeY = 12;

	QFileDialog *dialog = new QFileDialog();
	dialog->setNameFilter("PNG Files (*.png)");
	dialog->setOption(QFileDialog::ReadOnly);
	//dialog->setOption(QFileDialog::DontUseNativeDialog);
	dialog->setDirectory(".");
	QStringList fileNames;
	if (dialog->exec()) {
		fileNames = dialog->selectedFiles();
		QString fileName = fileNames.at(0);
		image = imread(fileName.toStdString(), CV_LOAD_IMAGE_COLOR);
		height = image.rows;
		width = image.cols;


			motorControl.openShutter();
			motorControl.commandMotor1(3, 5);  // Go a few steps back
			for (y=0;y!=height;++y) {
				motorControl.commandMotor1(3, -5);  // Go a few steps forth
				for(x=0;x!=width; x++) {
					motorControl.setLedColor(color);
					if (number<=0) {
						number = int(onDistribution(generator));
						pColor = colorVector->at(rand() % 100);
					}

					
					color.setBlue((image.data[((y*image.cols)+x)*3] / 6 * 5) + ( pColor->blue() / 6 ));
					color.setGreen((image.data[((y*image.cols)+x)*3+1] / 6 * 5)  + ( pColor->green() / 6));
					color.setRed((image.data[((y*image.cols)+x)*3+2] / 6 * 5) + ( pColor->red() / 6));
					motorControl.setLedColor(color);
					

					motorControl.commandMotor1(3, -stepSizeX);


					number--;

				}
				motorControl.setLedColor(QColor(0,0,0));
				motorControl.commandMotor1(3, stepSizeX * width);
				motorControl.commandMotor1(3, 5);  // Go a few steps back

				motorControl.commandMotor2(6, -stepSizeY);
			}
			motorControl.closeShutter();


			// Reset x axis to initial position if the width is uneven
			if( width%2 != 0) {
				motorControl.commandMotor1(6, stepSizeX * width);
			}

			// Reset y axis to initial position
			motorControl.commandMotor2(6, stepSizeY * height);

			motorControl.releaseMotor1();
			motorControl.releaseMotor2();


	}
}





