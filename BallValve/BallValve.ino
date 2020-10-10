//This program is made to control a ball valve using the input from a flow rate sensor to maintain correct... waterness?

#include <SPI.h>
const int shiftEnablePin = 4;

//for the MOSFET
const int valveGatePin = 8;

//These are for the Counter IC
const int dataPins[10] = { 2,3,4,5,6,7,8,9,10,11 };
const int counterResetPin = 9;
byte counterData;
void getCount();

//goingUp() is the initial boost to kick the valve open, probably can be lowered.
void goingUp();
//flipFlop() is just to maintain the state of the valve
void flipFlop();
//These two have the valve open slightly or close slightly
void flipFlipFlop();
void flipFlopFlop();



void setup() {
	for (int pinLoop = 0; pinLoop <= 9; pinLoop++) {
		pinMode(dataPins[pinLoop], INPUT);
	}
	pinMode(shiftEnablePin, OUTPUT);
	pinMode(counterResetPin, OUTPUT);
	pinMode(valveGatePin, OUTPUT);
	digitalWrite(valveGatePin, LOW);
	digitalWrite(counterResetPin, HIGH);
	delay(2);
	digitalWrite(counterResetPin, LOW);
	digitalWrite(shiftEnablePin, HIGH);
	goingUp();
	SPI.begin();
	Serial.begin(115200);
}


int millisNow;
void loop() {
	millisNow = millis();
	while (millis() - 300 < millisNow) {
		flipFlop();
	}
	getCount();
	Serial.println(counterData,DEC);
}

void getCount() {
	digitalWrite(shiftEnablePin, LOW);
	counterData = SPI.transfer(0);
	digitalWrite(shiftEnablePin, HIGH);
	digitalWrite(counterResetPin, HIGH);
	delay(2);
	digitalWrite(counterResetPin, LOW);
}

void flipFlop() {
	digitalWrite(valveGatePin, HIGH);
	delay(80);
	digitalWrite(valveGatePin, LOW);
	delay(250);
}

void flipFlipFlop() {
	digitalWrite(valveGatePin, HIGH);
	delay(90);
	digitalWrite(valveGatePin, LOW);
	delay(30);
}

void flipFlopFlop() {
	digitalWrite(valveGatePin, HIGH);
	delay(30);
	digitalWrite(valveGatePin, LOW);
	delay(90);
}

void goingUp() {
	digitalWrite(valveGatePin, HIGH);
	delay(3000);
	digitalWrite(valveGatePin, LOW);
}