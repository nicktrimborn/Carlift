 #include <OneButton.h>
#include "liftPost.h"


#define	STOP 0
#define UP 1
#define DOWN 2
#define ENCODER1_A 22
#define ENCODER1_B 21
#define ENCODER2_A 11
#define ENCODER2_B 12
#define RAISEBUTTON 7
#define LOWERBUTTON 11
#define MASTERUP 23
#define MASTERDOWN 24
#define SLAVEUP 20
#define SLAVEDOWN 19
#define ENCODERDIFFERENCE 1000
#define DIFFERENCEWAIT 1000

OneButton upButton(RAISEBUTTON, 0);
OneButton downButton(LOWERBUTTON, 0);
liftPost masterPost;
liftPost slavePost;

void setup()
{
	Serial.begin(57600);
	Serial.println("Carlift Software Version 1.0");
	masterPost.setEncoderPins(ENCODER1_A, ENCODER1_B);
	slavePost.setEncoderPins(ENCODER2_A, ENCODER2_B);
	pinMode(MASTERUP, OUTPUT);
	pinMode(MASTERDOWN, OUTPUT);
	pinMode(SLAVEUP, OUTPUT);
	pinMode(SLAVEDOWN, OUTPUT);
}

void moveLiftUP()
{
	if (abs((masterPost.getEncoderCount() - slavePost.getEncoderCount())) < ENCODERDIFFERENCE)
	{
		if (millis() - masterPost.getLastStopTime() > DIFFERENCEWAIT)
		{
			masterPost.setState(UP);
			slavePost.setState(UP);
			digitalWrite(MASTERUP, HIGH);
			digitalWrite(SLAVEUP, HIGH);
			Serial.println("LIFT MOVING UP");
		}
	}
	else if (masterPost.getEncoderCount() - slavePost.getEncoderCount() < 0)
	{
		masterPost.setLastStopTime(millis());
		if (millis() - masterPost.getLastStopTime() > DIFFERENCEWAIT)
		{
			masterPost.setState(STOP);
			digitalWrite(MASTERUP, LOW);
			digitalWrite(SLAVEUP, HIGH);
		}
	}
	else
	{
		slavePost.setLastStopTime(millis());
		if (millis() - slavePost.getLastStopTime() > DIFFERENCEWAIT)
		{
			slavePost.setState(STOP);
			digitalWrite(MASTERUP, HIGH);
			digitalWrite(SLAVEUP, LOW);
		}
	}
}

void moveLiftDown()
{
	if (abs((masterPost.getEncoderCount() - slavePost.getEncoderCount())) < ENCODERDIFFERENCE)
	{
		if (millis() - masterPost.getLastStopTime() > DIFFERENCEWAIT)
		{
			masterPost.setState(DOWN);
			slavePost.setState(DOWN);
			digitalWrite(MASTERDOWN, HIGH);
			digitalWrite(SLAVEDOWN, HIGH);
			Serial.println("LIFT MOVING DOWN");
		}
	}
	else if (masterPost.getEncoderCount() - slavePost.getEncoderCount() < 0)
	{
		masterPost.setLastStopTime(millis());
		if (millis() - masterPost.getLastStopTime() > DIFFERENCEWAIT)
		{
			masterPost.setState(STOP);
			digitalWrite(MASTERDOWN, LOW);
			digitalWrite(SLAVEDOWN, HIGH);
		}
	}
	else
	{
		slavePost.setLastStopTime(millis());
		if (millis() - slavePost.getLastStopTime() > DIFFERENCEWAIT)
		{
			slavePost.setState(STOP);
			digitalWrite(MASTERDOWN, HIGH);
			digitalWrite(SLAVEDOWN, LOW);
		}
	}
}

void upPressed()
{
	if (masterPost.getState() && slavePost.getState() != DOWN)
	{
		moveLiftUP();
	}
	
}
void downPressed()
{
	if (masterPost.getState() && slavePost.getState() != UP)
	{
		moveLiftDown();
	}
}

void loop()
{
	upButton.tick();
	downButton.tick();
}
