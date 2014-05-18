#include "motorcontrol.h"
//#include <stdio.h>
#include <string.h>


#include <QTimer>
#include <QDebug>
#include "Serial.h"
#include "../serial_commands.h"

MotorControl::MotorControl(QObject *parent) 
	: QObject(parent)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(onTic()));
	timer->start(0);
}

void MotorControl::fillPacketHeader(QByteArray *ba)
{
	ba->resize(5);
	ba->fill(0);
}

void MotorControl::openShutter() 
{
	QByteArray ba;
	// ba.resize(8);
	// ba.fill(0);
	fillPacketHeader(&ba);
	ba.append((char)((uint8_t)(1))); // Size of the packet
	ba.append((char)((uint8_t)(CMD_SHUTTER_OPEN)));
	commandQueue.enqueue(ba);
	shuterState = true;
}

void MotorControl::closeShutter() 
{
	QByteArray ba;
	//ba.resize(8);
	//ba.fill(0);
	fillPacketHeader(&ba);
	ba.append((char)((uint8_t)(1))); // Size of the packet
	ba.append((char)((uint8_t)(CMD_SHUTTER_CLOSE)));
	commandQueue.enqueue(ba);
	shuterState = false;
}

void MotorControl::setLedColor(QColor color)
{
	QByteArray ba;
	//ba.resize(8);
	//ba.fill(0);
	fillPacketHeader(&ba);
	ba.append((char)((uint8_t)(4))); // Size of the packet
	ba.append((char)((uint8_t)(CMD_LED_COLOR)));
	ba.append((char)((uint8_t)(color.red())));
	ba.append((char)((uint8_t)(color.green())));
	ba.append((char)((uint8_t)(color.blue())));

	commandQueue.enqueue(ba);
	//emit commandQueueChanged(commandQueue.size());
}

void MotorControl::commandMotor1(uint8_t speed, int steps)
{
	int16_t steps16 = steps;
	QByteArray ba;
	//ba.resize(8);
	//ba.fill(0);
	fillPacketHeader(&ba);
	ba.append((char)((uint8_t)(4))); // Size of the packet
	ba.append((char)((uint8_t)(CMD_MOTOR1)));
	ba.append((char)((uint8_t)(speed)));
	ba.append((char)((uint8_t)(steps16 >> 8)));
	ba.append((char)((uint8_t)(steps16)));
	commandQueue.enqueue(ba);
	//emit commandQueueChanged(commandQueue.size());
}

void MotorControl::commandMotor2(uint8_t speed, int steps)
{
	int16_t steps16 = steps;
	QByteArray ba;
	//ba.resize(8);
	//ba.fill(0);
	fillPacketHeader(&ba);
	ba.append((char)((uint8_t)(4))); // Size of the packet
	ba.append((char)((uint8_t)(CMD_MOTOR2)));
	ba.append((char)((uint8_t)(speed)));
	ba.append((char)((uint8_t)(steps16 >> 8)));
	ba.append((char)((uint8_t)(steps16)));
	commandQueue.enqueue(ba);
	//emit commandQueueChanged(commandQueue.size());
}

void MotorControl::releaseMotor1()
{
	QByteArray ba;
	//ba.resize(8);
	//ba.fill(0);
	fillPacketHeader(&ba);
	ba.append((char)((uint8_t)(1))); // Size of the packet
	ba.append((char)((uint8_t)(CMD_RELEASE_MOTOR1)));
	commandQueue.enqueue(ba);
}

void MotorControl::releaseMotor2()
{
	QByteArray ba;
	//ba.resize(8);
	//ba.fill(0);
	fillPacketHeader(&ba);
	ba.append((char)((uint8_t)(1))); // Size of the packet
	ba.append((char)((uint8_t)(CMD_RELEASE_MOTOR2)));
	commandQueue.enqueue(ba);
}

void MotorControl::processLine(uint8_t *line) 
{
	char neddle[] = "_BP ";
	int num = 0;

	if(strcmp((char*)line, neddle) > 0) {
	 	num = strtol((char*)(line + 4),NULL,10);
	 	//printf("\n got:\t%d\n", num);
	 	remotePending -= num;
	}
	emit gotNewLine(QString::fromLocal8Bit((char*)line));
}

int MotorControl::sendNextCommand()
{
	if(commandQueue.size() > 0) {
		QByteArray ba = commandQueue.dequeue();
		serial.uartWrite((uint8_t*)ba.data(), ba.size());
		remotePending+=ba.size();
		emit commandQueueDequeued(commandQueue.size());
		return 0;
	}
	return -1;
}

void MotorControl::onTic()
{
	int size, i;
	uint8_t s[100];

	if (serial.isOpen()) {
		if(sending) {
			while ( remotePending<70 ) {
				if(sendNextCommand() < 0) {
					break;
				}
				//sendNextCommand();
			}
		}
		
		size = serial.uartRead(s);
		if (size>0) {
			for(i=0;i!=size;++i) {
				if(s[i]=='\n') {
					// Got a new line
					line[line_index] = '\0';
					line_index = 0;
					processLine(line);
				} else {
					line[line_index++] = s[i];
				}
			}
		}
	}
}

void MotorControl::startSending()
{
	sending = true;
}

void MotorControl::stopSending()
{
	sending = false;
}