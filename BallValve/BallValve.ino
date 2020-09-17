//This program is made to control a ball valve using the input from a flow rate sensor to maintain correct... waterness?
//Interrupt pins for the Arduino Nano are on digital pins 2&3
//I am going to use pin 3 for the PWM (it is 490 Hz)

//These are for counting the spins
volatile unsigned long spinCount = 0;
const int spinTime = 100;
//maximum 90 for 300ms counting time, scales
const int target = 30;

//These are the pins I am using
const int sensorPin = 2;
const int gatePin = 13;

//Function Prototypes
void updatePower();
void addCount();

//for the battery level array
int yn, yn1, yn2, yn3;

void setup() {
	attachInterrupt(digitalPinToInterrupt(sensorPin), addCount, FALLING);
	pinMode(sensorPin, INPUT_PULLUP);
	digitalWrite(gatePin, LOW);
	Serial.begin(115200);
}


void loop() {
	delay(spinTime);
	updatePower();
}


void updatePower() {
	cli();
	yn3 = yn2;
	yn2 = yn1;
	yn1 = yn;
	yn = spinCount;
	int projPoint = (yn + (2 * yn - 4 * yn1 + 3 * yn2 - yn3) / (spinTime/100));
	int projPoint2 = (projPoint + (2 * projPoint - 4 * yn + 3 * yn1 - yn2) / (spinTime/100));
	Serial.print(spinCount);
	Serial.print('\t');
	Serial.print(projPoint);
	Serial.print('\t');
	Serial.println(projPoint2);
	if (spinCount<=18) {
		digitalWrite(gatePin, HIGH);
	}
	else if (spinCount>22) {
		digitalWrite(gatePin, LOW);
	}
	spinCount = 0;
	sei();
}

void addCount() {
	spinCount++;
}