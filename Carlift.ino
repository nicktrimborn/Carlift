 #include <RotaryEncoder.h>

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


class liftPost
{
public:
	liftPost();
	~liftPost();
	void setEncoderPins(int encA, int encB);

private:
	int encoderCount;
	int state; //0 = stopped, 1 = Move Up, 2 = Move Down
	int encA, encB;
};

liftPost::liftPost()
{
	encoderCount = 0;
	state = 0;
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


void setup()
{
	Serial.begin(57600);
	Serial.println("Carlift Software Version 1.0");
	liftPost masterPost;
	//masterPost
	liftPost slavePost;

	
  /* add setup code here */

}

void loop()
{

  /* add main program code here */

}
