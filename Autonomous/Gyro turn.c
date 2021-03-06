#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S3,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     ,               sensorCustom)
#pragma config(Motor,  mtr_S1_C1_1,     motorR1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorR2,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorL1,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorL2,       tmotorTetrix, openLoop, reversed)
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

void turn(int degrees, const string direction, const string type) //Input a degree value and a direction
{
	SensorValue(gyro) = 0; //resets gyro sensor
	int value;
	value = degrees * 10; //Comverts to value readable by the gyro sensor
	while(abs(SensorValue(gyro)) != value) //Loop until values match
	{
		if(direction == "left" || direction == "Left") //Decides to go left
		{
			if(type == "point" || type == "Point") //decides if point turn
			{
				if(abs(SensorValue(gyro)) > value + 200 || abs(SensorValue(gyro)) < value - 200) //once the robot gets near the target range,
				{                                                                                //it will slow down
					motor[motorR1] = -25;
					motor[motorR2] = -25;
					motor[motorL1] = 25;
					motor[motorL2] = 25;
				}
				else
				{
					motor[motorR1] = -10;
					motor[motorR2] = -10;
					motor[motorL1] = 10;
					motor[motorL2] = 10;
				}
			}
			if(type == "swing" || type == "Swing") //decides if swing turn
			{
				if(abs(SensorValue(gyro)) > value + 200 || abs(SensorValue(gyro)) < value - 200) //once the robot gets near the target range,
				{                                                                                //it will slow down
					motor[motorR1] = 0;
					motor[motorR2] = 0;
					motor[motorL1] = 50;
					motor[motorL2] = 50;
				}
				else
				{
					motor[motorR1] = 0;
					motor[motorR2] = 0;
					motor[motorL1] = 10;
					motor[motorL2] = 10;
				}
			}
		}
		if(direction == "right" || direction == "Right") //decides to go right
		{
			if(type == "point" || type == "Point") //decides if point turn
			{
				if(abs(SensorValue(gyro)) > value + 200 || abs(SensorValue(gyro)) < value - 200) //once the robot gets near the target range,
				{                                                                                //it will slow down
					motor[motorR1] = 25;
					motor[motorR2] = 25;
					motor[motorL1] = -25;
					motor[motorL2] = -25;
				}
				else
				{
					motor[motorR1] = 10;
					motor[motorR2] = 10;
					motor[motorL1] = -10;
					motor[motorL2] = -10;
				}
			}
			if(type == "swing" || type == "Swing") //decides if swing turn
			{
				if(abs(SensorValue(gyro)) > value + 200 || abs(SensorValue(gyro)) < value - 200) //once the robot gets near the target range,
				{                                                                                //it will slow down
					motor[motorR1] = 50;
					motor[motorR2] = 50;
					motor[motorL1] = 0;
					motor[motorL2] = 0;
				}
				else
				{
					motor[motorR1] = 10;
					motor[motorR2] = 10;
					motor[motorL1] = 0;
					motor[motorL2] = 0;
				}
			}
		}
	}
	motor[motorR2] = 0; //stops motors
	motor[motorR2] = 0;
	motor[motorL1] = 0;
	motor[motorL2] = 0;
	SensorValue(gyro) = 0; //resets gyro sensor
}

task main()
{
	//turn(motor power, "left/right", "point/swing")
}
