#include <Servo.h>

#define PIN_COMPRESSOR 5
#define PIN_WHEEL 6
#define PIN_PLUNGER 7
#define PIN_GATE 4
#define PIN_COMPRESSOR_SENSOR 8
#define SWITCH_OFF 12
#define SWITCH_FIRE 11

bool primed = false;

Servo spinner;

#define DELAY 500

void setup() {
	pinMode(PIN_COMPRESSOR, OUTPUT);
	spinner.attach(PIN_WHEEL, 1000, 2000);
	spinner.write(1500);
	pinMode(PIN_PLUNGER, OUTPUT);
	digitalWrite(PIN_PLUNGER, HIGH);
	pinMode(PIN_GATE, OUTPUT);
	digitalWrite(PIN_GATE, HIGH);
	pinMode(PIN_COMPRESSOR_SENSOR, INPUT);
	pinMode(SWITCH_OFF, INPUT_PULLUP);
	pinMode(SWITCH_FIRE, INPUT_PULLUP);
	Serial.begin(9600);
}

void loop() {
	if (digitalRead(PIN_COMPRESSOR_SENSOR)) {
		digitalWrite(PIN_COMPRESSOR, HIGH);
	} else {
		digitalWrite(PIN_COMPRESSOR, LOW);
	}

	if (!digitalRead(SWITCH_OFF)) {
		Serial.println("Stopping spinner");
		spinner.write(1500);
	} else {
		Serial.println("Spinning...");
		spinner.write(2000);
	}

	// pulled to fire, about to go
	if (!digitalRead(SWITCH_FIRE)) {
		primed = true;
	}
	// fire when released back to arm
	if (!!digitalRead(SWITCH_OFF) && !!digitalRead(SWITCH_FIRE) && primed) {
		primed = false;
		Serial.println("Shooting!");
		digitalWrite(PIN_PLUNGER, LOW);
		delay(1000);
		digitalWrite(PIN_GATE, LOW);
		delay(100);
		digitalWrite(PIN_PLUNGER, HIGH);
		delay(500);
		digitalWrite(PIN_GATE, HIGH);
	}
}
