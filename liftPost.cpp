
#include "liftPost.h"

liftPost::liftPost()
{
	encoderCount = 0;
	state = STOP;
	encA = 0;
	encB = 0;
}

liftPost::~liftPost()
{

}

void liftPost::setEncoderPins(int encA, int encB)
{
	RotaryEncoder encoder(encA, encB);
}

void liftPost::clearEncoderCount()
{
	encoderCount = 0;
}

unsigned long liftPost::getEncoderCount()
{
	return this->encoderCount;
}

void liftPost::setLastStopTime(unsigned long time)
{
	lastStopStart = time;
}

void liftPost::setState(unsigned int state)
{
	this->state = state;
}

unsigned int liftPost::getState()
{
	return state;
}

unsigned long liftPost::getLastStopTime()
{
	return this->lastStopStart;
}