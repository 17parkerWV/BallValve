//This program is made to control a ball valve using the input from a flow rate sensor to maintain correct... waterness?

//Gate pin on the FET that controls the ball valve
const int valveGatePin = 13;

//These are for the Counter IC
const int dataPins[10] = { 2,3,4,5,6,7,8,9,10,11 };
const int counterResetPin = 12;
unsigned int counterData;
void getCount();



void setup() {
	for (int pinLoop = 0; pinLoop <= 9; pinLoop++) {
		pinMode(dataPins[pinLoop], INPUT);
	}
	pinMode(valveGatePin, OUTPUT);
	pinMode(counterResetPin, OUTPUT);
	digitalWrite(counterResetPin, LOW);
	counterData = 0b0000000000000000;
	digitalWrite(valveGatePin, HIGH);
	Serial.begin(115200);
	digitalWrite(counterResetPin, LOW);
}


int millisNow;
void loop() {
	millisNow = millis();
	while (millis() < (millisNow + 300)) {
	}													//Epmty loop for now
	getCount();
	Serial.println(counterData,BIN);
}


void getCount() {
	counterData = 0b0000000000000000;
	for (int pin = 0; pin <= 9; pin++) {
		counterData += digitalRead(dataPins[pin]);
		counterData <<= 1;
	}
	digitalWrite(counterResetPin, HIGH);
	delay(2);
	digitalWrite(counterResetPin, LOW);
}