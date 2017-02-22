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
	liftPost();
	~liftPost();
	void setEncoderPins(int encA, int encB);
	void clearEncoderCount();
	unsigned long getEncoderCount();
	unsigned long getLastStopTime();
	void setLastStopTime(unsigned long time);
	void setState(unsigned int state);
	unsigned int getState();

private:
	unsigned long lastStopStart;
	unsigned long encoderCount;
	unsigned int state; //0 = stopped, 1 = Move Up, 2 = Move Down
	int encA, encB;
};
