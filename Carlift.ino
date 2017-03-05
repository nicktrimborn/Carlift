#include <Adafruit_NeoPixel.h>
#include <OneButton.h>
#include "liftPost.h"

#define	STOP 0
#define UP 1
#define DOWN 2
#define ENCODER1_A 17
#define ENCODER1_B 16
#define ENCODER2_A 8
#define ENCODER2_B 9
#define RAISEBUTTON 4
#define LOWERBUTTON 7
#define MASTERUP 18
#define MASTERDOWN 19
#define SLAVEUP 15
#define SLAVEDOWN 14
#define ENCODERDIFFERENCE 1000
#define DIFFERENCEWAIT 1000
#define NUMPIXELS 12

OneButton upButton(RAISEBUTTON, 0);
OneButton downButton(LOWERBUTTON, 0);
liftPost masterPost;
liftPost slavePost;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIND5, NEO_GRB + NEO_KHZ800);
int delayval = 500; // delay for half a second


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
	upButton.setPressTicks(600);
	upButton.attachLongPressStart(upPressedStart);
	downButton.attachLongPressStart(downPressedStart);
	upButton.attachLongPressStop(upPressedStop);
	downButton.attachLongPressStop(downPressedStop);
	pixels.begin();
	
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

void stopLift()
{
	Serial.println("STOP LIFT");
	masterPost.setState(STOP);
	slavePost.setState(STOP);
	digitalWrite(MASTERUP, LOW);
	digitalWrite(MASTERDOWN, LOW);
	digitalWrite(SLAVEUP, LOW);
	digitalWrite(SLAVEDOWN, LOW);
}

void upPressedStart()
{
	//pixels.clear();
	Serial.println("UP BUTTON PRESSED");
	pixels.setPixelColor(0, pixels.Color(0, 150, 0));
	pixels.show();
	masterPost.setState(UP);
	slavePost.setState(UP);
	if (masterPost.getState() && slavePost.getState() != DOWN)
	{
		moveLiftUP();
	}
	
}
void downPressedStart()
{
	Serial.println("DOWN BUTTON PRESSED");
	//pixels.clear();
	
	if (!(masterPost.getState() && slavePost.getState()))
	{
		masterPost.setState(DOWN);
		slavePost.setState(DOWN);
		pixels.setPixelColor(1, pixels.Color(0, 150, 0));
		pixels.show();
		moveLiftDown();
	}
}

void upPressedStop()
{
	//pixels.clear();
	pixels.setPixelColor(6, pixels.Color(150, 0, 0));
	pixels.show();
	Serial.println("UP BUTTON RELEASED");
	stopLift();
}
void downPressedStop()
{
	pixels.setPixelColor(7, pixels.Color(150, 0, 0));
	pixels.show();
	Serial.println("DOWN BUTTON Released");
	stopLift();
}

void loop()
{
	upButton.tick();
	downButton.tick();
	pixels.clear();
	//for (int i = 0; i<NUMPIXELS; i++) {
	    //pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
	//pixels.setPixelColor(i, pixels.Color(0, 150, 0)); // Moderately bright green color.
	//pixels.show(); // This sends the updated pixel color to the hardware.
	//delay(delayval); // Delay for a period of time (in milliseconds).
   // }
}
