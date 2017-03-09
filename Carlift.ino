#include <Adafruit_NeoPixel.h>
#include <OneButton.h>
#include "liftPost.h"

#define	STOP 0
#define UP 1
#define DOWN 2

//State Machine Variables
#define WAITINGFORINPUT 0
#define LIFTSTOP 1
#define LIFTMOVEUP 2
#define LIFTMOVEDOWN 3
#define LIFTBALANCEMASTER 4
#define LIFTBALANCESLAVE 5

//Pin Definitions
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

//Tuning Variable
#define ENCODERDIFFERENCE 1000
#define DIFFERENCEWAIT 1000
#define NUMPIXELS 12

OneButton upButton(RAISEBUTTON, 0);
OneButton downButton(LOWERBUTTON, 0);
liftPost masterPost(ENCODER1_A, ENCODER1_B, MASTERUP, MASTERDOWN);
liftPost slavePost(ENCODER2_A, ENCODER2_B, SLAVEUP, SLAVEDOWN);

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIND5, NEO_GRB + NEO_KHZ800);
int delayval = 500; // delay for half a second

unsigned int state;
unsigned long globalTime;


void setup()
{
	//Initialise Variables
	globalTime = 0;
	state = WAITINGFORINPUT;

	//Interupt Routine
	cli();
	PCICR |= 0b0000011; // Enables Ports B and C Pin Change Interrupts
	PCMSK0 |= 0b00000011; // PCINT01 & PCINT02
	PCMSK1 |= 0b00001100; // PCINT10 & PCINT11
	sei();

	//Serial Setup	
	Serial.begin(57600);
	Serial.println("Carlift Software Version 1.0");
	
	//Button Configuration
	upButton.setPressTicks(600);
	upButton.attachLongPressStart(upPressedStart);
	downButton.attachLongPressStart(downPressedStart);
	upButton.attachLongPressStop(upPressedStop);
	downButton.attachLongPressStop(downPressedStop);
	
	//pixels.begin();
}

void tick()
{
	unsigned long now = millis();
	globalTime = millis();

	//State Machine
	if (state == WAITINGFORINPUT)
	{
		// do nothing
	}
	else if (state == LIFTSTOP)	
	{
		stopLift();
	}
	else if (state == LIFTMOVEUP) 
	{
		masterPost.setState(UP);
		slavePost.setState(UP);
	}
	else if (state == LIFTMOVEDOWN) 
	{
		masterPost.setState(DOWN);
		slavePost.setState(DOWN);
	}
	else if (state == LIFTBALANCEMASTER) 
	{

	}
	else if (state == LIFTBALANCESLAVE)
	{

	}
	else {
		//should not get here 
		Serial.println("FSM Undefined State - Should Not Be Here");
	}

}

void moveLiftUP()
{
	if (abs((masterPost.getEncoderCount() - slavePost.getEncoderCount())) <= ENCODERDIFFERENCE)
	{
		//Lift within Balance Tolerance
		state = LIFTMOVEUP;
	}
	else if (masterPost.getEncoderCount() - slavePost.getEncoderCount() < 0)
	{
		// Slave Unbalanced	
		state = LIFTBALANCESLAVE;
	}
	else if(masterPost.getEncoderCount() - slavePost.getEncoderCount() > ENCODERDIFFERENCE)	
	{
		//Master Unbalanced
		state = LIFTBALANCEMASTER;
	}
	else {
		stopLift();
		Serial.println("Ëncoder Error");
	}
}

void moveLiftDown()
{
	if (abs((masterPost.getEncoderCount() - slavePost.getEncoderCount())) <= ENCODERDIFFERENCE)
	{
		//Lift within Balance Tolerance
		state = LIFTMOVEDOWN;
	}
	else if (masterPost.getEncoderCount() - slavePost.getEncoderCount() < 0)
	{
		// Slave Unbalanced	
		state = LIFTBALANCESLAVE;
	}
	else if (masterPost.getEncoderCount() - slavePost.getEncoderCount() > ENCODERDIFFERENCE)
	{
		//Master Unbalanced
		state = LIFTBALANCEMASTER;
	}
	else {
		stopLift();
		Serial.println("Ëncoder Error");
	}
}

void stopLift()
{
	state = LIFTSTOP;
	masterPost.setState(STOP);
	slavePost.setState(STOP);
	Serial.println("STOP LIFT");
}

void upPressedStart()
{
	//pixels.clear();
	Serial.println("UP BUTTON PRESSED");
	//pixels.setPixelColor(0, pixels.Color(0, 150, 0));
	//pixels.show();
	state = LIFTMOVEUP;
	
}
void downPressedStart()
{
	Serial.println("DOWN BUTTON PRESSED");
	//pixels.clear();
	state = LIFTMOVEDOWN;
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
	tick();
	pixels.clear();
	//for (int i = 0; i<NUMPIXELS; i++) {
	    //pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
	//pixels.setPixelColor(i, pixels.Color(0, 150, 0)); // Moderately bright green color.
	//pixels.show(); // This sends the updated pixel color to the hardware.
	//delay(delayval); // Delay for a period of time (in milliseconds).
   // }
}


ISR(PCINT0_vect) {
	//value++;
	masterPost.encoderTick();
		//Serial.println("test");
}

ISR(PCINT1_vect) {
	//value++;
	slavePost.encoderTick();
	//Serial.println("test");
}
