//This program is made to control a ball valve using the input from a flow rate sensor to maintain correct... waterness?
//Interrupt pins for the Arduino Nano are on digital pins 2&3

//These are for counting the spins
volatile unsigned int spinCount = 0;
const int spinTime = 300;

//These are the pins I am using
const int sensorPin = 2;
const int gatePin = 13;
const int outPin = 12;

//Function Prototypes
void goCount();
int resetCount();


void setup() {
	Serial.begin(115200);
	attachInterrupt(digitalPinToInterrupt(sensorPin), goCount, FALLING);
	//pinMode(gatePin, OUTPUT);
	pinMode(outPin, OUTPUT);
	digitalWrite(outPin, HIGH);
	//digitalWrite(gatePin, LOW);
}


void loop() {
	int currentMillis = millis();
	while (millis() - currentMillis < spinTime) {}
	detachInterrupt(sensorPin);
	resetCount();
	attachInterrupt(sensorPin, goCount, FALLING);
}


void goCount() {
	spinCount++;
}

int resetCount() {
	Serial.println(spinCount);
	spinCount = 0;
}
