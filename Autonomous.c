#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S4,     sensorIR,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorC,          motorIR,       tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorR1,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorR2,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorL1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorL2,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorBlPickup, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorBm,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     motorLft1,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     motorLft2,     tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

  string actS = "lower"; //Starting place
  string act1 = "IR"; //First action
  string act2 = "dropMed"; //Second action

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an TETRIX robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

//#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  return;
}

/*
*
* HELPER TASKS
*
*/

//Travel set rotations
void forward(int dist, int power)
{
	nMotorEncoder[motorR2] = 0;
	nMotorEncoder[motorL2] = 0;

	while (abs(nMotorEncoder[motorR2]) <= abs(dist))
	{
		if (abs(nMotorEncoder[motorR2]) > abs(nMotorEncoder[motorL2]))
		{
			motor[motorR1] = power;
			motor[motorL1] = power - 10;
			motor[motorR2] = power;
			motor[motorL2] = power - 10;
		}
		else if (abs(nMotorEncoder[motorR2]) < abs(nMotorEncoder[motorL2]))
		{
			motor[motorR1] = power - 10;
			motor[motorL1] = power;
			motor[motorR2] = power - 10;
			motor[motorL2] = power;
		}
		else
		{
			motor[motorR1] = power;
			motor[motorL1] = power;
			motor[motorR2] = power;
			motor[motorL2] = power;
		}
	}
}

//Turn set rotations - 1800 = 45 degrees
void turn(int dist, int powerL, int powerR)
{
	if (powerL < powerR)
	{
		nMotorEncoder[motorL2] = 0;

		while (abs(nMotorEncoder[motorL2]) <= abs(dist))
		{
			motor[motorR1] = powerR;
			motor[motorR2] = powerR;
			motor[motorL1] = powerL;
			motor[motorL2] = powerL;
		}
	}
	else
	{
		nMotorEncoder[motorR2] = 0;

		while (abs(nMotorEncoder[motorR2]) <= abs(dist))
		{
			motor[motorR1] = powerR;
			motor[motorR2] = powerR;
			motor[motorL1] = powerL;
			motor[motorL2] = powerL;
		}
	}
}

//Travel set rotations
void stopMotors()
{
	motor[motorR1] = 0;
	motor[motorL1] = 0;
	motor[motorR2] = 0;
	motor[motorL2] = 0;
}

/*
*
* Core Code
*
*/

//Travel from the scoring zone to the tubes
void lowerToTubes()
{
  forward(2100, -70);
  turn(1400, 10, -60);
  forward(2000, -50);
  turn(1500, -60, 10);
  forward(3600, -40);
}

//Score in medium tube
void dumpMed()
{
	bool runLift = true;

	while(runLift == true)
	{
		motor[motorLft2] = 50;
	 	motor[motorLft1] = 50;
		if(nMotorEncoder[motorLft2] < -2500)
		{
			runLift = false;
		}
	}
	motor[motorLft2] = 0;
	motor[motorLft1] = 0;
	while(nMotorEncoder[motorBm] > -650)
	{
		motor[motorBm] = -30;
	}
	while(nMotorEncoder[motorBm] > -1000)
	{
		motor[motorBm] = -1;
	}
	motor[motorBm] = 10;
	Sleep(700);
	motor[motorBm] = 0;
	Sleep(300);
	servo[servo3] = 120;
	Sleep(1000);

	int LiftRunning = 1;

	while(nMotorEncoder[motorBm] < -650)
	{
		motor[motorBm] = 30;
	}
	while(nMotorEncoder[motorBm] < -300)
	{
		motor[motorBm] = 1;
	}
	motor[motorBm] = 0;
	Sleep(300);
	while(nMotorEncoder[motorBm] < -25)
	{
		motor[motorBm] = 7;
	}
	motor[motorBm] = 0;
	Sleep(300);
	while(LiftRunning == 1)
	{
		if(nMotorEncoder[motorLft2] > -720)
		{
			if(nMotorEncoder[motorLft2] < -200)
			{
				motor[motorLft2] = -20;
				motor[motorLft1] = -20;
			}
			else
			{
				motor[motorLft2] = 0;
				motor[motorLft1] = 0;
				LiftRunning = 0;
			}
		}
		else
		{
			motor[motorLft2] = -40;
			motor[motorLft1] = -40;
		}
	}
}


//Score in medium tube
void dumpCenter()
{
	bool runLift = true;

	while(runLift == true)
	{
		motor[motorLft2] = 50;
	 	motor[motorLft1] = 50;
		if(nMotorEncoder[motorLft2] < -5850)
		{
			runLift = false;
		}
	}
	motor[motorLft2] = 0;
	motor[motorLft1] = 0;
	servo[servo3] = 180;
	while(nMotorEncoder[motorBm] > -650)
	{
		motor[motorBm] = -30;
	}

	while(nMotorEncoder[motorBm] > -800)
	{
		motor[motorBm] = -1;
	}
	motor[motorBm] = 10;
	Sleep(500);
	motor[motorBm] = 0;
	Sleep(300);
	Sleep(1000);
	motor[motorBm] = 20;
	Sleep(250);
	motor[motorBm] = -20;
	Sleep(250);
	motor[motorBm] = 20;
	Sleep(250);
	motor[motorBm] = -20;
	Sleep(250);
	servo[servo3] = 0;
	forward(400, 35);
	stopMotors();

	int LiftRunning = 1;

	while(nMotorEncoder[motorBm] < -650)
	{
		motor[motorBm] = 30;
	}
	while(nMotorEncoder[motorBm] < -300)
	{
		motor[motorBm] = 1;
	}
	motor[motorBm] = 0;
	Sleep(300);
	while(nMotorEncoder[motorBm] < -25)
	{
		motor[motorBm] = 7;
	}
	motor[motorBm] = 0;
	Sleep(300);
	while(LiftRunning == 1)
	{
		if(nMotorEncoder[motorLft2] > -720)
		{
			if(nMotorEncoder[motorLft2] < -150)
			{
				motor[motorLft2] = -20;
				motor[motorLft1] = -20;
			}
			else
			{
				motor[motorLft2] = 0;
				motor[motorLft1] = 0;
				LiftRunning = 0;
			}
		}
		else
		{
			motor[motorLft2] = -40;
			motor[motorLft1] = -40;
		}
	}
}

void tubeMed()
{
  turn(1620, 50, -50);
  forward(1300, -50);
  stopMotors();
	dumpMed();
}

void lowerIR()
{
	forward(1600, -65);
	stopMotors();

	nMotorEncoder[motorIR] = 0;

	int ir1 = SensorValue[sensorIR];

	while(nMotorEncoder[motorIR] > -48)
	{
		motor[motorIR] = -10;
	}

	motor[motorIR] = 0;

	int ir2 = SensorValue[sensorIR];

	while(nMotorEncoder[motorIR] < 48)
	{
		motor[motorIR] = 10;
	}

	motor[motorIR] = 0;

	int ir3 = SensorValue[sensorIR];

	while(nMotorEncoder[motorIR] < 94)
	{
		motor[motorIR] = 10;
	}

	motor[motorIR] = 0;

	int ir4 = SensorValue[sensorIR];

	nxtDisplayBigTextLine(1, "%d", ir1);
	nxtDisplayBigTextLine(3, "%d", ir2);
	nxtDisplayBigTextLine(5, "%d", ir3);
	nxtDisplayBigTextLine(7, "%d", ir4);

	while(nMotorEncoder[motorIR] > 0)
	{
		motor[motorIR] = -10;
	}

	motor[motorIR] = 0;

	if((ir1 == 4 || ir1 == 5) && (ir2 == 4 || ir2 == 5) && (ir3 == 6 || ir3 == 7 || ir3 == 0 || ir3 == 7) && (ir4 == 5 || ir4 == 4|| ir4 == 6))
	{
		forward(1200, -65);
	  turn(1550, -50, 50);
	  forward(1000, -35);
	  turn(1550, 50, -50);
	  forward(1450, -35);
	  turn(500, 50, -50);
		while(SensorValue[sensorIR] != 5)
	  {
	  	motor[motorR1] = -40;
			motor[motorR2] = -40;
			motor[motorL1] = 40;
			motor[motorL2] = 40;
	  }
	  forward(450, -35);
	  stopMotors();
	  servo[servo3] = 0;
	  dumpCenter();
	  while(nMotorEncoder[motorIR] > 0)
		{
			motor[motorIR] = -20;
		}
	}
	else if(ir1 == 5 && (ir2 == 4 || ir2 == 5) && (ir3 == 6 || ir3 == 7) && (ir4 == 8 || ir4 == 7))
	{
		nxtDisplayBigTextLine(1, "Pos 2");
		forward(1100, -65);
	  turn(1450, -50, 50);
		forward(1050, -35);
		turn(1450, 50, -50);
		while(SensorValue[sensorIR] != 5)
	  {
	  	motor[motorR1] = -40;
			motor[motorR2] = -40;
			motor[motorL1] = 40;
			motor[motorL2] = 40;
	  }

		forward(1075, -35);
		stopMotors();
		dumpCenter();
		while(nMotorEncoder[motorIR] > 0)
		{
			motor[motorIR] = -20;
		}
	}
	else if(ir1 == 6 && ir2 == 5 && ir3 == 7 && (ir4 == 9 || ir4 == 8))
	{
		nxtDisplayBigTextLine(1, "Pos 3");

		turn(550, 50, -50);
	  forward(1500, -35);
	  turn(750, -50, 50);


	  forward(350, -35);
	  stopMotors();
	  dumpCenter();

	}
	else
	{
		forward(1000, -65);
	  turn(1500, -50, 50);
	  forward(1600, -35);
	  turn(1550, 50, -50);
	  forward(1800, -35);
	  turn(200, 50, -50);
		while(SensorValue[sensorIR] != 5)
	  {
	  	motor[motorR1] = -40;
			motor[motorR2] = -40;
			motor[motorL1] = 40;
			motor[motorL2] = 40;
	  }
	  forward(1050, -35);
	  stopMotors();
	  servo[servo3] = 0;
	  dumpCenter();
	  while(nMotorEncoder[motorIR] > 0)
		{
			motor[motorIR] = -20;
		}
	}
}

task main()
{
  //initializeRobot();

  //waitForStart(); // Wait for the beginning of autonomous pha

  //TODO: Selection Menu
	nMotorEncoder[motorBm] = 0;
	nMotorEncoder[motorLft2] = 0;

  lowerIR();
	stopMotors();

}
