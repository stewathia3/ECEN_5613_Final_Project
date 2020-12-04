#include <Arduino.h>

/*
  Turns stepper motor CW and CCW based on serial command.
*/

// Define Stepper GPIO pins in ATMEGA
#define AIN1 9
#define AIN2 10
#define BIN1 11
#define BIN2 12

// Define delay (in ms) between each step
// Note: a larger delay means a lower speed
#define DELAY 1

volatile unsigned char step_num = 1;

void step(unsigned char direction);

// Stepper motor 4 pin control truth table
// Step   AIN1   AIN2   BIN1   BIN2
//   1      1      0      1      0
//   2      0      1      1      0
//   3      0      1      0      1
//   4      1      0      0      1

void setup()
{
	Serial.begin(9600);

	// Initialize all 4 GPIOs as output pins
	pinMode(AIN1, OUTPUT);
	pinMode(AIN2, OUTPUT);
	pinMode(BIN1, OUTPUT);
	pinMode(BIN2, OUTPUT);
}

void loop()
{
	Serial.println("Press a command to turn the motor:");
	Serial.println(" '1' to step CW 1 step");
	Serial.println(" '2' to step CCW 1 step");
	Serial.println(" '3' to step CW 1 rev");
	Serial.println(" '4' to step CCW 1 rev");

    unsigned char direction = 1; // CW = 1, CCW = 0

    while( Serial.available()) {
        unsigned char command = Serial.read();

        if (command == '1') {
            // Step CW 1 step
            direction = 1;
            step(direction);

        } else if (command == '2') {
            // Step CCW 1 step
            direction = 0;
            step(direction);

        } else if (command == '3') {
            // Step CW 200 steps (1 rev)
            direction = 1;
            for (int i = 0; i < 200; i++) {
                step(direction);
                delay(DELAY);
            }

        } else if (command == '4') {
            // Step CCW 200 steps (1 rev)
            direction = 0;
            for (int i = 0; i < 200; i++) {
                step(direction);
            }
        } else {
            Serial.println("Invalid command entered.");
        }
    }

}

void step(unsigned char direction) {

    if (step_num == 1) {

        // 1010
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);

        if (direction == 1) {
            step_num++;
        } else {
            step_num = 4;
        }

    } else if (step_num == 2) {

        // 0110
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);

        if (direction == 1) {
            step_num++;
        } else {
            step_num--;
        }

    } else if (step_num == 3) {

        // 0101
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);

        if (direction == 1) {
            step_num++;
        } else {
            step_num--;
        }

    } else { // (step_num == 4)

        // 1001
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);

        if (direction == 1) {
            step_num = 1;
        } else {
            step_num--;
        }
    }

}
