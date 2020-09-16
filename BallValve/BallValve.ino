//This program is made to control a ball valve using the input from a flow rate sensor to maintain correct... waterness?
//Interrupt pins for the Arduino Nano are on digital pins 2&3

//These are for counting the spins
volatile unsigned long spinCount = 0;
const int spinTime = 300;

//These are the pins I am using
const int sensorPin = 2;
const int gatePin = 13;

//Function Prototypes
void updatePower();
void addCount();
void resetCount();


void setup() {
	attachInterrupt(digitalPinToInterrupt(sensorPin), addCount, FALLING);
	pinMode(gatePin, OUTPUT);
	pinMode(sensorPin, INPUT_PULLUP);
	digitalWrite(gatePin, LOW);
}


void loop() {
	delay(spinTime);
	updatePower();
	resetCount();
}

void updatePower() {
	cli();
	if (spinCount <= 40) {
		digitalWrite(gatePin, HIGH);
	}
	else if (spinCount >= 50) {
		digitalWrite(gatePin, LOW);
	}
	sei();
}



void addCount() {
	spinCount++;
}

void resetCount() {
	cli();
	spinCount = 0;
	sei();
}
