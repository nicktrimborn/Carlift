
#include "liftPost.h"

liftPost::liftPost(int encA, int encB, int contactorUpPin, int contactorDownPin) : _rotEnc(encA, encB) 
{
	//initialise private variable
	this->_encA = encA;
	this->_encB = encB;
	this->_contactorUpPin = contactorUpPin;
	this->_contactorDownPin = contactorDownPin;
	_encoderCount = 0;
	_state = STOP;

	//Setup Post Rotary Encoder
		
	//Setup IO Pins for Post control Contactors
	pinMode(_contactorUpPin, OUTPUT);
	pinMode(_contactorDownPin, OUTPUT);
}

liftPost::~liftPost()
{
	
}

void liftPost::stopLift()
{
	Serial.println("State Changed to: " + STOP);
	digitalWrite(_contactorUpPin, LOW);
	digitalWrite(_contactorDownPin, LOW);
}

void liftPost::encoderTick()
{
	_rotEnc.tick();
}

void liftPost::clearEncoderCount()
{
	_encoderCount = 0;
}

unsigned long liftPost::getEncoderCount()
{
	return this->_encoderCount;
}

void liftPost::setLastStopTime(unsigned long time)
{
	_lastStopStart = time;
}

void liftPost::setState(unsigned int state)
{
	this->_state = state;
	Serial.println("State Changed to: " + state);
}

unsigned int liftPost::getState()
{
	return _state;
}

unsigned long liftPost::getLastStopTime()
{
	return this->_lastStopStart;
}