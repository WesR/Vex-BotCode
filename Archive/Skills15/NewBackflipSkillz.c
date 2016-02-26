#pragma config(Sensor, in1,		 lineTracker1,	 sensorLineFollower)
#pragma config(Sensor, in2,		 lineTracker2,	 sensorLineFollower)
#pragma config(Sensor, in3,		 lineTracker3,	 sensorLineFollower)
#pragma config(Sensor, dgtl1,	 lifterSholder,	 sensorQuadEncoder)
#pragma config(Sensor, dgtl3,	 lifterElbow,		 sensorQuadEncoder)
#pragma config(Motor,	 port1,						leftMotor,		 tmotorVex393_HBridge, openLoop)
#pragma config(Motor,	 port2,						elbowLift,		 tmotorVex393_MC29, openLoop)
#pragma config(Motor,	 port3,						shoulderLift,	 tmotorVex393_MC29, openLoop)
#pragma config(Motor,	 port9,						clawMotor,		 tmotorVex393_MC29, openLoop)
#pragma config(Motor,	 port10,					rightMotor,		 tmotorVex393_HBridge, openLoop)
//Wes Ring NextGen™ Programming
//Perry Plane III NextGen™ BaseLib

task main() //Start Kernel
{
	//Global varibles
	//enableCompetitionMode(); //Allows for compition mode
	bool isLiftingElbow = true; //checks if it is lifting Elbow
	bool isLiftingSholder = true; //checks if it is lifting Sholder
	int autoLevelPower = 17; //autoballanceing motor speed
	int autoLevelThresh = 20; //autoballanceing motor speed
	int threshold = 700; //Black -> white | High -> low
	int runNumber = 1;
	bool terminator = false;


	repeat (forever) {
		if (terminator == false)
		{
			//if (getCompetitionDriverControl() == true) {}
			//Driver contols
			joystickControl(leftMotor, Ch2, 10); //Left wheel motor
			joystickControl(rightMotor, Ch3, 10); //Right wheel motor
			buttonControl(clawMotor, Btn8D, Btn8R, 70);//Claw Motor
			//buttonControl(elbowLift, Btn5D, Btn6D, 70); //Elbow Motor
			//buttonControl(shoulderLift, Btn6U, Btn5U,70); //Sholder Motor

			if (vexRT[Btn5D] == 1) //Lifting Up Elbow
			{
				setMotor(elbowLift, 70);
				isLiftingElbow = true;
			}
			else if (vexRT[Btn6D] == 1)//Lifting Down Elbow
			{
				setMotor(elbowLift, -70);
				isLiftingElbow = true;
			}
			else//Balance time!
			{
				if (isLiftingElbow == true){isLiftingElbow = false; SensorValue[lifterElbow] = 0;}
				if (SensorValue[lifterElbow] > -autoLevelThresh){ setMotor(elbowLift, -autoLevelPower); }
				else if (SensorValue[lifterElbow] < autoLevelThresh){ setMotor(elbowLift, autoLevelPower); }
				else { setMotor(elbowLift, 0); }
			}

			if (vexRT[Btn6U] == 1) //Lifting Up Sholder
			{
				setMotor(shoulderLift, 70);
				isLiftingSholder = true;
			}
			else if (vexRT[Btn5U] == 1)//Lifting Down Sholder
			{
				setMotor(shoulderLift, -70);
				isLiftingSholder = true;
			}
			else//Balance time!
			{
				if (isLiftingSholder == true){isLiftingSholder = false; SensorValue[lifterSholder] = 0;}
				if (SensorValue[lifterSholder] > -autoLevelThresh){ setMotor(shoulderLift, -autoLevelPower); }
				else if (SensorValue[lifterSholder] < autoLevelThresh){ setMotor(shoulderLift, autoLevelPower); }
				else { setMotor(shoulderLift, 0); }
			}

		}
		if (vexRT(Btn7U) == 1)
		{
			terminator = true;
		}
		if (vexRT(Btn7L) == 1)
		{
			terminator = false;
		}

		if (terminator == true)
		{
			//Lets make Roboit think!

			//Forward

			if (SensorValue(lineTracker1) > threshold && SensorValue(lineTracker2) > threshold && SensorValue(lineTracker3) < threshold) //Lean left | Power Right
			{
				setMotor(leftMotor, 95);
				setMotor(rightMotor, 60);
			}
			else if (SensorValue(lineTracker1) < threshold && SensorValue(lineTracker2) > threshold && SensorValue(lineTracker3) > threshold) //Lean Right | Power Left
			{
				setMotor(leftMotor, 60);
				setMotor(rightMotor, 95);
			}
			else if (SensorValue(lineTracker1) > threshold && SensorValue(lineTracker2) > threshold && SensorValue(lineTracker3) > threshold) //Turn 90 Degrees
			{

				setMotor(leftMotor, 60);
/*				wait1Msec;
				moveMotorTarget(leftMotor, 1800, 50);
				moveMotorTarget(rightMotor, 1800,  50);
				waitUntilMotorStop(leftMotor);
				waitUntilMotorStop(rightMotor); */
			}
			else //Go forward
			{
				setMotor(leftMotor, -80);
				setMotor(rightMotor, -60);
			}
		}
	}

	//Terminator Mode
	//if (getCompetitionAutonomous() == true) {}

}
