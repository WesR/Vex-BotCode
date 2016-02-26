#pragma config(Sensor, in1,    lineTracker1,   sensorLineFollower)
#pragma config(Sensor, in2,    lineTracker2,   sensorLineFollower)
#pragma config(Sensor, in3,    lineTracker3,   sensorLineFollower)
#pragma config(Sensor, dgtl1,  lifter,         sensorQuadEncoder)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           treadLift,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           clawMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393_HBridge, openLoop, reversed)
//Wes Ring Robit™ autonomous Programming
task main()
{
	//Global varibles
	int threshold = 1800; //Black -> white | High -> low
	int runNumber = 1;
	repeat (forever) {
		//Lets make Roboit think!

		//Forward
		if (SensorValue(lineTracker1) > threshold && SensorValue(lineTracker2) > threshold && SensorValue(lineTracker3) < threshold) //Lean left | Power Right
		{
			setMotor(leftMotor, 60);
			setMotor(rightMotor, 120);
		}
		else if (SensorValue(lineTracker1) < threshold && SensorValue(lineTracker2) > threshold && SensorValue(lineTracker3) > threshold) //Lean Right | Power Left
		{
			setMotor(leftMotor, 120);
			setMotor(rightMotor, 60);
		}
		else//Go forward
		{
			setMotor(leftMotor, 60);
			setMotor(rightMotor, 60);
		}

		//Turn Left
		/*
		if (SensorValue(lineTracker1) < threshold && SensorValue(lineTracker2) < threshold && SensorValue(lineTracker3) > threshold)// Doubble white on the left
		{
			setMotor(leftMotor, 0);
			setMotor(rightMotor, 65);
		}

		//Turn Right
		if (SensorValue(lineTracker1) > threshold && SensorValue(lineTracker2) < threshold && SensorValue(lineTracker3) < threshold)// Doubble white on the left
		{
			setMotor(leftMotor, 0);
			setMotor(rightMotor, 65);
		}
		*/
	}
}
