#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <QObject>
#include <QQueue>
#include <QByteArray>
#include <QColor>
#include <QTimer>
#include <stdint.h>
#include <QString>
#include "Serial.h"

class MotorControl: public QObject
 {
    Q_OBJECT

	public:
		MotorControl(QObject *parent = 0);
		void processLine(uint8_t *line);
		void openShutter();
		void closeShutter();
		void setLedColor(QColor color);
		void commandMotor1(uint8_t speed, int steps);
		void commandMotor2(uint8_t speed, int steps);
		void releaseMotor1();
		void releaseMotor2();
		void startSending();
		void stopSending();
		bool isSending() const { return sending; };
		bool isShutterOpen() const { return shuterState; };

		Serial serial;
		QQueue<QByteArray> commandQueue;


	private:
		int sendNextCommand();
		void fillPacketHeader(QByteArray *ba);
		bool sending = false;
		bool shuterState = false;
		int remotePending = 0;
		uint8_t line[1000];
		int line_index = 0;

	signals:
		void gotNewLine(QString newLine);
		void commandQueueDequeued(int queueSize);

	private slots:
		void onTic();
};

#endif