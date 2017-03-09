// liftPost.h

#ifndef _LIFTPOST_h
#define _LIFTPOST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

#include <RotaryEncoder.h>

#define	STOP 0
#define UP 1
#define DOWN 2

class liftPost
{
public:
	liftPost(int encA, int encB, int contactorUpPin, int contactorDownPin);
	~liftPost();
	void clearEncoderCount();
	unsigned long getEncoderCount();
	unsigned long getLastStopTime();
	void setLastStopTime(unsigned long time);
	void setState(unsigned int state);
	unsigned int getState();
	void stopLift();
	void encoderTick();
private:
	RotaryEncoder _rotEnc;
	unsigned long _lastStopStart;
	unsigned long _encoderCount;
	unsigned int _state; //0 = stopped, 1 = Move Up, 2 = Move Down
	int _encA, _encB;  //Encoder Phase Pin Number
	int _contactorUpPin, _contactorDownPin; //Contactor Pins
	
};
