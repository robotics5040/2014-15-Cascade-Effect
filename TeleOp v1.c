#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     ,               sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     ,               sensorCustom)
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
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
bool liftMotorActivated = false;

void initializeRobot()
{
	// Place code here to sinitialize servos to starting positions.
	// Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.
	nMotorEncoder(motorLft1) = 0;
	nMotorEncoder(motorLft2) = 0;
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                               DirectInput Button Notes
//
// Buttons 0=X 1=A 2=B 3=Y 4=LB 5=RB 6=LT 7=RT 8=Back 9=Start 10=LSD 11=RSD
// POV (D-Pad) -1=None 0-7=Positions (0=up, 1-7 +CW)
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
void stopMotors()
{
	motor[motorR1] = 0;
	motor[motorR2] = 0;
	motor[motorL1] = 0;
	motor[motorL2] = 0;
	motor[motorBlPickup] = 0;
	motor[motorBm] = 0;
	motor[motorLft1] = 0;
	motor[motorLft2] = 0;
}



task eStop() //Emergency Stop (Complete Program Stop)
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(joy1Btn(10) == 1 && joy2Btn(10) == 1) //Program will pause everything when E-Stop button (start) hit on both controllers
		{
			PlaySound(soundException); //debug estop command
			stopMotors();
			StopAllTasks();
		}
	}
}


task lift1() //high
{

	bool runLift = true;

	while(runLift == true)
	{
		motor[motorLft2] = 50;
		motor[motorLft1] = 50;
		if(nMotorEncoder[motorLft2] < -5800)
		{
			runLift = false;
		}
	}
	motor[motorLft2] = 0;
	motor[motorLft1] = 0;
	while(nMotorEncoder[motorBm] > -600)
	{
		motor[motorBm] = -40;
	}
	while(nMotorEncoder[motorBm] > -950)
	{
		motor[motorBm] = -1;
	}
	motor[motorBm] = 10;
	Sleep(700);
	motor[motorBm] = 0;
	motor[motorLft2] = 30;
	motor[motorLft1] = 30;
	Sleep(300);
	motor[motorLft2] = 0;
	motor[motorLft1] = 0;
	servo[servo3] = 230;
	liftMotorActivated = false;
	StopTask(lift1);
}

task lift2() //low
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
	while(nMotorEncoder[motorBm] > -600)
	{
		motor[motorBm] = -40;
	}
	while(nMotorEncoder[motorBm] > -950)
	{
		motor[motorBm] = -20;
	}
	motor[motorBm] = 50;
	Sleep(200);
	motor[motorBm] = 10;
	Sleep(700);
	motor[motorBm] = 0;

	liftMotorActivated = false;
	StopTask(lift2);
}

task lift3() //medium
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
	while(nMotorEncoder[motorBm] > -600)
	{
		motor[motorBm] = -40;
	}
	while(nMotorEncoder[motorBm] > -950)
	{
		motor[motorBm] = -1;
	}
	motor[motorBm] = 10;
	Sleep(700);
	motor[motorBm] = 0;
	motor[motorLft2] = 30;
	motor[motorLft1] = 30;
	Sleep(300);
	motor[motorLft2] = 0;
	motor[motorLft1] = 0;
	servo[servo3] = 230;
	liftMotorActivated = false;
	StopTask(lift3);
}

task liftReset() //stop other lift commands
{
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
		motor[motorBm] = 10;
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
				liftMotorActivated = false;
			}
		}
		else
		{
			motor[motorLft2] = -40;
			motor[motorLft1] = -40;
		}
	}

}
task eReset() //Emergency Reset (Ends All Subroutines)
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(joy1Btn(9) == 1 || joy2Btn(9) == 1) //Program will reset subroutines when E-Reset button (select) hit on one of the controllers
		{
			PlaySound(soundException); //debug ereset command
			stopMotors();
			StopTask(lift1);
			StopTask(lift2);
			StopTask(lift3);
			StopTask(liftReset);
		}
	}
}
task main()
{
	initializeRobot();
	bool LBpressed = false;
	bool ballPickupEnabled = false;
	nMotorEncoder[motorLft2] = 0;
	waitForStart();   // wait for start of tele-op phase
	StartTask(eStop); // start estop task
	StartTask(eReset);// start ereset task
	while (true)
	{
		getJoystickSettings(joystick);

		if (joystick.joy1_y1 > 8 || joystick.joy1_y1 < -8) //If not in deadzone, do motors LEFT
		{
			motor[motorL1] = (joystick.joy1_y1)/1.5;
			motor[motorL2] = (joystick.joy1_y1)/1.5;
		}
		else
		{
			motor[motorL1] = 0;
			motor[motorL2] = 0;
		}

		if (joystick.joy1_y2 > 8 || joystick.joy1_y2 < -8) //If not in deadzone, do motors RIGHT
		{
			motor[motorR1] = (joystick.joy1_y2)/1.5;
			motor[motorR2] = (joystick.joy1_y2)/1.5;
		}
		else
		{
			motor[motorR1] = 0;
			motor[motorR2] = 0;
		}

		//rolling goal clamp code

		if(joy1Btn(8) == 1)
		{
			servo[servo4] = 240;
			servo[servo5] = 80;
		}
		if(joy1Btn(6) == 1)
		{
			servo[servo4] = 172;
			servo[servo5] = 150;
		}
		if(joy2Btn(8) == 1)
		{
			servo[servo3] = 80;

		}
		if(joy2Btn(6) == 1)
		{
			servo[servo3] = 230;

		}

		//toggle ball pickup code
		if(joy1Btn(5) == 1 && LBpressed == false)
		{
			LBpressed = true;
			if(ballPickupEnabled == false)
			{
				motor[motorBlPickup] = 50;
				ballPickupEnabled = true;
			}
			else
			{
				motor[motorBlPickup] = 0;
				ballPickupEnabled = false;
			}

		}
		if(joy1Btn(5) == 0)
		{
			LBpressed = false;
		}

		//autonomous lift control code

		if((joy2Btn(1) == 1|| joy2Btn(3) == 1) && liftMotorActivated == false) //medium height
		{
			liftMotorActivated = true;
			StartTask(lift3);
		}

		if(joy2Btn(4) == 1 && liftMotorActivated == false) //high height
		{
			liftMotorActivated = true;
			StartTask(lift1);
		}

		if(joystick.joy2_TopHat == 4) //reset
		{
			StartTask(liftReset);
			liftMotorActivated = true;
		}
		if (liftMotorActivated == false)
		{

			if (joystick.joy2_y1 > 15 || joystick.joy2_y1 < -15) //If not in deadzone, do motors LEFT
			{
				if(joystick.joy2_y1 < -15 && nMotorEncoder[motorLft2] > -720)
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
					}
				}
				else
				{
					motor[motorLft2] = (joystick.joy2_y1)/1.5;
					motor[motorLft1] = (joystick.joy2_y1)/1.5;
				}
			}
			else
			{
				motor[motorLft2] = 0;
				motor[motorLft1] = 0;
			}

			if (joystick.joy2_y2 > 15 || joystick.joy2_y2 < -15) //If not in deadzone, do motors LEFT
			{
				motor[motorBm] = (joystick.joy2_y2)/3;
			}
			else
			{
				motor[motorBm] = 0;
			}
		}
		// Insert code to have servos and motors respond to joystick and button values.

		// Look in the ROBOTC samples folder for programs that may be similar to what you want to perform.
		// You may be able to find "snippets" of code that are similar to the functions that you want to
		// perform.
	}
}
