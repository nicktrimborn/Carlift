
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
	setState(STOP);
}

void liftPost::encoderTick()
{
	_rotEnc.tick();
}

void liftPost::moveLift(void)
{
	if (_state == UP)
	{
		digitalWrite(_contactorUpPin, HIGH);
		digitalWrite(_contactorUpPin, HIGH);
		Serial.println("LIFT MOVING UP");
	}
	else if (_state == DOWN) {
		digitalWrite(_contactorDownPin, HIGH);
		digitalWrite(_contactorDownPin, HIGH);
		Serial.println("LIFT MOVING UP");
	}
	else
	{
		stopLift();
	}
}

void liftPost::_refresh()
{
	if (_state == UP)
	{
		digitalWrite(_contactorUpPin, HIGH);
		digitalWrite(_contactorUpPin, HIGH);
		Serial.println("LIFT MOVING UP");
	}
	else if (_state == DOWN) {
		digitalWrite(_contactorDownPin, HIGH);
		digitalWrite(_contactorDownPin, HIGH);
		Serial.println("LIFT MOVING UP");
	}
	else
	{
		stopLift();
	}
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
	_state = state;
	_refresh();
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