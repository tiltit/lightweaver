#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QColor>
#include <QString>
#include <QVector>
#include "ui_ui-main-window.h"
#include "motorcontrol.h"


class MainWindow : public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT
	public:
		MainWindow(QMainWindow *parent = 0);

	private:
		MotorControl motorControl;

		void colorImage();
		void colorStripes();
		void lineWorld();
		void lineWorldColor();
		void perfectImage();
		void colorLinesFull();
		
		
	private slots:
		void onOpenDeviceButtonClicked();
		void onColorWheelColorChange(QColor);
		void onMotorControlGotNewLine(QString line);
		void onSendCommandsButtonClicked();
		void onM1StepClockwiseButtonClicked();
		void onM1StepCounterclockwiseButtonClicked();
		void onM2StepClockwiseButtonClicked();
		void onM2StepCounterclockwiseButtonClicked();
		void onReleaseMotor1Button();
		void onReleaseMotor2Button();
		void actionColorImageTriggered();
		void actionColorStripesTriggered();
		void actionLineWorldColorTriggered();
		void actionLineWorldTriggered();
		void actionPerfectImageTriggered();
		void actionColorLinesFullTriggered();
		void onMotorControlCommandQueueDequeued(int queueSize);
		void onFlushCommandsButtonClick();
		void onToggleShutterButtonClicked();

		QVector<QColor*>* computeGoldenRatioColors(double startHue,double saturation, double value, int size);
     
};

#endif
