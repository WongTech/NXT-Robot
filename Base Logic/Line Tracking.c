#pragma config(Sensor, S1,     lightSensor,         sensorLightActive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                           - Line Tracker -                                             *|
|*                                            ROBOTC on NXT                                               *|
|*                                                                                                        *|
|*  This program allows your taskbot to follow a line in reverse.                                         *|
|*                                                                                                        *|
|*                                        ROBOT CONFIGURATION                                             *|
|*    NOTES:                                                                                              *|
|*    1)  The Light Sensor is attached to the back of the robot.                                          *|
|*    2)  Be sure to take readings of your Light Sensor over the light and dark areas.  Once you have     *|
|*        the values, add them and divide by 2 to find your threshold.  Then, use your threshold as a     *|
|*        comparison in your program.                                                                     *|
|*                                                                                                        *|
|*    MOTORS & SENSORS:                                                                                   *|
|*    [I/O Port]              [Name]              [Type]              [Description]                       *|
|*    Port B                  motorB              NXT                 Right motor                         *|
|*    Port C                  motorC              NXT                 Left motor                          *|
|*    Port 1                  lightSensor         Light Sensor        Back mounted                        *|
\*---------------------------------------------------------------------------------------------------4246-*/

// Define the directions.
#define LEFT true
#define RIGHT (!LEFT)

// Define the colour ranges.
#define BLACK_END 37
#define GREEN_START BLACK_END
#define GREEN_END 50
#define WHITE_START GREEN_END

// Define the motor values.
#define HIGH 30
#define LOW 2
#define STRAIGHT ((HIGH + LOW) / 2)

// The current direction we are turning.
bool currentDir;
// The direction we were going when last on black.
bool lastDir;

// The value of the light sensor on this tick.
int light;

// Return whether or not we are currently on black.
bool onBlack() {
	return (light < BLACK_END);
}

// Return whether or not we are currently on green.
bool onGreen() {
	return (light >= GREEN_START && light < GREEN_END);
}

// Return whether or not we are currently on white.
bool onWhite() {
	return (light >= WHITE_START);
}

void goLeft() {
	currentDir = LEFT;
	motor[motorB] = LOW; // Set right motor to low.
	motor[motorC] = HIGH; // Set left motor to high.
}

void goRight() {
	currentDir = RIGHT;
	motor[motorB] = HIGH; // Set right motor to high.
	motor[motorC] = LOW; // Set left motor to low.
}

void straighten() {
	if (currentDir == LEFT) {
		motor[motorB] = STRAIGHT;
		motor[motorC] = STRAIGHT;
	} else {
		motor[motorB] = STRAIGHT;
		motor[motorC] = STRAIGHT;
	}
}

// Set the direction to turn.
void setDirection(bool newDir) {
	if (newDir == LEFT) {
		goLeft();
	} else {
		goRight();
	}
}

task main() {
	wait1Msec(50); // The program waits 50 milliseconds to initialize the light sensor.
	currentDir = LEFT;
	lastDir = LEFT;
	goLeft();
	while (true) {
		light = SensorValue[lightSensor];
		if (onBlack() || onGreen()) {
			lastDir = currentDir;
			straighten();
		} else if (onWhite()) {
			setDirection(!lastDir);
		}
	}
}
