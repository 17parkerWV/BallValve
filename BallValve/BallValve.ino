//This program is made to control a ball valve using the input from a flow rate sensor to maintain correct... waterness?
#include <SPI.h>
//To get the shift register to send data. Not actually an enable pin but in this case it essentially is an enable pin
const int shiftEnablePin = 4;

//for the MOSFET and to kick the motor if it is at 0
const int valveGatePin = 8;
void kick();

//These are for the Counter IC
const int counterResetPin = 9;
byte counterData;
void getCount();
void counterReset();

//flipFlop() is just to maintain the state of the valve
void flipFlop();
//These variables are for the timing of the valve
unsigned int millisNow;
int timeValue = 150;
int targetHall = 8;
int targetRange[2] = { 6,10 };
const int deltaX = 150;
int yn, yn1, yn2, yn3, ynPlus;
int posLogic = 0;


void setup() {
	pinMode(shiftEnablePin, OUTPUT);
	pinMode(counterResetPin, OUTPUT);
	pinMode(valveGatePin, OUTPUT);
	digitalWrite(valveGatePin, LOW);
	digitalWrite(shiftEnablePin, HIGH);
	SPI.begin();
	Serial.begin(115200);
	kick();
	counterReset();
}


void loop() {
	millisNow = millis();
	getCount();
	flipFlop();
	Serial.println(counterData, DEC);
}


void getCount() {
	posLogic = 0;
	digitalWrite(shiftEnablePin, LOW);
	counterData = SPI.transfer(0);
	digitalWrite(shiftEnablePin, HIGH);
	yn3 = yn2;
	yn2 = yn1;
	yn1 = yn;
	yn = counterData;
	ynPlus = (yn + (2 * yn - 4 * yn1 + 3 * yn2 - yn3) / deltaX);
	//Logic Time
	//This section needs to be updated to calculate the time range by itself
	if (ynPlus > targetRange[1]) {
		posLogic = 3;
	}
	else if (ynPlus <= targetRange[1] && ynPlus >= targetHall) {
		posLogic = 1;
	}
	if (ynPlus < targetRange[0]) {
		posLogic = 4;
	}
	else if (ynPlus >= targetRange[0] && ynPlus < targetHall) {
		posLogic = 2;
	}
	switch (posLogic) {
	case 3:
		timeValue = 5;
		break;
	case 1:
		timeValue = 14;
		break;
	case 4:
		timeValue = 45;
		break;
	case 2:
		timeValue = 30;
		break;
	default:
		timeValue = 15;
		break;
	}
	counterReset();
}

void flipFlop() {
	digitalWrite(valveGatePin, HIGH);
	delay(timeValue);
	digitalWrite(valveGatePin, LOW);
	delay(deltaX - timeValue);
}

void counterReset() {
	digitalWrite(counterResetPin, HIGH);
	delay(2);
	digitalWrite(counterResetPin, LOW);
}

void kick() {
	digitalWrite(valveGatePin, HIGH);
	delay(150);
	digitalWrite(valveGatePin, LOW);
}