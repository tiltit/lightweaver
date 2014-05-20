#include "MainWindow.h"

#include <QFileDialog>
#include <QStringList>
#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDebug>
#include <random>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QFileDialog>

using namespace cv;

MainWindow::MainWindow(QMainWindow *parent)
	: QMainWindow(parent)
{
	setupUi(this);

	connect(actionColorImage, SIGNAL(triggered()), this, SLOT(actionColorImageTriggered()));
	connect(actionColor_Stripes, SIGNAL(triggered()), this, SLOT(actionColorStripesTriggered()));
	connect(actionLineworld, SIGNAL(triggered()), this, SLOT(actionLineWorldTriggered()));
	connect(actionLineWorldColor, SIGNAL(triggered()), this, SLOT(actionLineWorldColorTriggered()));
	connect(actionPerfectImage, SIGNAL(triggered()), this, SLOT(actionPerfectImageTriggered()));
	connect(actionColorLinesFull, SIGNAL(triggered()), this, SLOT(actionColorLinesFullTriggered()));
	
	connect(openDeviceButton, SIGNAL(clicked()), this, SLOT(onOpenDeviceButtonClicked()));
	connect(sendCommandsButton, SIGNAL(clicked()), this, SLOT(onSendCommandsButtonClicked()));
	connect(m1StepClockwiseButton, SIGNAL(clicked()), this, SLOT(onM1StepClockwiseButtonClicked()));
	connect(m1StepCounterclockwiseButton, SIGNAL(clicked()), this, SLOT(onM1StepCounterclockwiseButtonClicked()));
	connect(m2StepClockwiseButton, SIGNAL(clicked()), this, SLOT(onM2StepClockwiseButtonClicked()));
	connect(m2StepCounterclockwiseButton, SIGNAL(clicked()), this, SLOT(onM2StepCounterclockwiseButtonClicked()));
	connect(releaseMotor1Button, SIGNAL(clicked()), this, SLOT(onReleaseMotor1Button()));
	connect(releaseMotor2Button, SIGNAL(clicked()), this, SLOT(onReleaseMotor2Button()));
	connect(flushCommandsButton, SIGNAL(clicked()), this, SLOT(onFlushCommandsButtonClick()));
	connect(toggleShutterButton, SIGNAL(clicked()), this, SLOT(onToggleShutterButtonClicked()));

	connect(&motorControl, SIGNAL(gotNewLine(QString)), this, SLOT(onMotorControlGotNewLine(QString)));
	connect(&motorControl, SIGNAL(commandQueueDequeued(int)), this, SLOT(onMotorControlCommandQueueDequeued(int)));
	connect(colorWheel, SIGNAL(colorChange(QColor)), this, SLOT(onColorWheelColorChange(QColor)));
}

void MainWindow::actionColorImageTriggered()
{
	colorImage();
}

void MainWindow::actionColorStripesTriggered()
{
	colorStripes();
}

void MainWindow::actionLineWorldTriggered()
{
	lineWorld();
}

void MainWindow::actionLineWorldColorTriggered()
{
	lineWorldColor();
}

void MainWindow::actionPerfectImageTriggered() 
{
	perfectImage();
}

void MainWindow::actionColorLinesFullTriggered()
{
	colorLinesFull();
}

void MainWindow::onOpenDeviceButtonClicked()
{
	if(motorControl.serial.isOpen()) {
		motorControl.serial.uartClose();
		openDeviceButton->setText("Open Device");
	} else {
		motorControl.serial.init(deviceLineEdit->text().toLocal8Bit());
		openDeviceButton->setText("Close Device");
	}
}

void MainWindow::onColorWheelColorChange(QColor color)
{
	//qDebug() << color;
	motorControl.setLedColor(color);
}

void MainWindow::onMotorControlGotNewLine(QString line)
{
	line.append("\n");
	//serialTextEdit->moveCursor (QTextCursor::End);
	serialTextEdit->insertPlainText(line);
	//serialTextEdit->moveCursor (QTextCursor::End);
	// serialTextEdit->textCursor().insertText("\n");
	// serialTextEdit->moveCursor (QTextCursor::End);
	//serialTextEdit->append(line);
}

void MainWindow::onSendCommandsButtonClicked()
{
	if(motorControl.isSending()) {
		motorControl.stopSending();
		sendCommandsButton->setText("Start sending");		
	} else {
		motorControl.startSending();
		sendCommandsButton->setText("Stop sending");
	}
}

void MainWindow::onM1StepClockwiseButtonClicked()
{
	motorControl.commandMotor1(m1StepDelaySpinBox->value(), -m1StepClockwiseSpinBox->value());
}

void MainWindow::onM1StepCounterclockwiseButtonClicked()
{
	//qDebug() << "onM1StepCounterclockwiseButtonClicked";
	motorControl.commandMotor1(m1StepDelaySpinBox->value(), m1StepCounterclockwiseSpinBox->value());
}

void MainWindow::onM2StepClockwiseButtonClicked()
{
	//qDebug() << "onM2StepClockwiseButtonClicked";
	motorControl.commandMotor2(m2StepDelaySpinBox->value(), -m2StepClockwiseSpinBox->value());
}

void MainWindow::onM2StepCounterclockwiseButtonClicked()
{
	//qDebug() << "onM2StepCounterclockwiseButtonClicked";
	motorControl.commandMotor2(m2StepDelaySpinBox->value(), m2StepCounterclockwiseSpinBox->value());
}

void MainWindow::onReleaseMotor1Button()
{
	motorControl.releaseMotor1();
}

void MainWindow::onReleaseMotor2Button()
{
	motorControl.releaseMotor2();
}

void MainWindow::onMotorControlCommandQueueDequeued(int queueSize)
{
	statusbar->showMessage("Command queue:  " + QString::number(queueSize));
}

void MainWindow::onFlushCommandsButtonClick() 
{
	motorControl.commandQueue.clear();
	statusbar->showMessage("Command queue:  " + QString::number(motorControl.commandQueue.size()));
}

void MainWindow::onToggleShutterButtonClicked()
{
	if (motorControl.isShutterOpen()) {
		motorControl.closeShutter();
	} else {
		motorControl.openShutter();
	}
}