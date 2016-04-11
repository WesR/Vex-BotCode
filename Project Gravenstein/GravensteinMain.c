#pragma config(Sensor, in1,    launcherDegree, sensorPotentiometer)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  RightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, openLoop, driveLeft)
#pragma config(Motor,  port2,           launcherLeft,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           launcherRight, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           launcherTilt,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           hozBelt,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           vertBelt,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393_HBridge, openLoop, driveRight)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
* Project Gravenstein
* By Wes Ring�
* Riley Schoppa�
*/

int launcherSpeed = 0;
int launcherSpeed_new = 0;
bool hozBelt_on = false;

void setLauncherSpeed(int _speed){ //Sets the launcher speed
	setMotor(launcherLeft, -_speed);
	setMotor(launcherRight, _speed);
}
void stopLauncher(void){ //Kills the launcher
	stopMotor(launcherLeft);
	stopMotor(launcherRight);
	launcherSpeed = 0;
	launcherSpeed_new = 0;
}
void updateLauncherSpeed(void){ //Updates the launcher speed changes
	if (launcherSpeed < launcherSpeed_new){launcherSpeed++;wait(.1);}
	if (launcherSpeed > launcherSpeed_new){launcherSpeed--;wait(.1);}
	setLauncherSpeed(launcherSpeed);
}
void goForwardFor(int time){ //Goes forward for a set ammount of time
	setMotor(leftMotor,120);
	setMotor(rightMotor,120);
	wait(time);
	stopMotor(leftMotor);
	stopMotor(rightMotor);
}
void roboControl(void){ //For autonomous control	//This is test code
	//We spin in a circle for 5 seconds
	setMotor(leftMotor,100);
	setMotor(rightMotor,100);
	wait(5);
	stopMotor(leftMotor);
	stopMotor(rightMotor);
}

void manualControl(void){ //For manual control

	if (abs(vexRT(Ch2)) > 15 || abs(vexRT(Ch3)) > 15){ //Only move if we pop over 15 units on the controls
		//Run the motors at the joystick input
		setMotor(leftMotor,vexRT(Ch3));
		setMotor(rightMotor,vexRT(Ch2));
	}	else {
		//Kill the motors
		stopMotor(leftMotor);
		stopMotor(rightMotor);
	}

	//if (vexRT(Btn8U)){ roboControl();} //If 8L is pressed, we go into auto test mode

	if (vexRT(Btn8L)){ // Starts and stops the horizontal belt
		if(!hozBelt_on){hozBelt_on = true; setMotor(hozBelt,65);}else{hozBelt_on = false;stopMotor(hozBelt);}
	}

	if (vexRT(Btn5D)||vexRT(Btn6D)){ // Starts and stops verticle belt
		if (vexRT(Btn5D)){setMotor(vertBelt,-127);} else {setMotor(vertBelt,127);}
	} else {
		stopMotor(vertBelt);
	}

	if (vexRT(Btn5U)||vexRT(Btn6U)){// Starts and stops the launcher tilt motors
		if (vexRT(Btn5U)){setMotor(launcherTilt,-30);} else {setMotor(launcherTilt,30);}
	} else {
		stopMotor(launcherTilt);
	}

	/*			Launcher speeds			*/
	if (vexRT(Btn7D)){ stopLauncher();} //Stops Launcher
	if (vexRT(Btn7L)){ launcherSpeed_new = 65;} //Sets launcher speed to 65
	if (vexRT(Btn7U)){ launcherSpeed_new = 100;} //Sets launcher speed to 100
	if (vexRT(Btn7R)){ launcherSpeed_new = 127;} //Sets launcher speed to 127 (max)
	updateLauncherSpeed();
}

task main(){
	//enableCompetitionMode(); //This makes it so the Vex Competition machine can take control
	bool _CompetitionMode = false; //Allowing us to refrence if we are in Competition Mode

	repeat(forever){
		if ( _CompetitionMode == true){
			if (getCompetitionDriverControl() == true) {manualControl();} //Competition driver Controls
			if (getCompetitionAutonomous() == true) {roboControl();} //Competition robo Controls
			} else {
			manualControl(); //For driver controls
		}
	}
}
