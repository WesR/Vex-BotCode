#pragma config(Sensor, dgtl1,  DeathSonarIn,   sensorSONAR_inch)
#pragma config(Sensor, dgtl3,  Autonomous,     sensorDigitalIn)
#pragma config(Motor,  port2,           Shoulder,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           Hand,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           Claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           Left,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           Right,         tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


task main()
{
	enableCompetitionMode();
	repeat (forever) {
		if (getCompetitionDriverControl() == true) {
			buttonControl(port5, Btn6U, Btn5U, 75);
			buttonControl(port2, Btn6D, Btn5D, 40);
			joystickControl(port7, Ch3, 10);
			joystickControl(port8, Ch2, 10);
			buttonControl(port4, Btn8L, Btn8U, 30);
		}
		if (getCompetitionAutonomous() == true) {
			setMotor(port4, -50);
			setMotor(port7, 50);
			setMotor(port8, 50);
			wait(2, seconds);
			stopAllMotors();
			setMotor(port4, 50);
			wait(1, seconds);
			setMotor(port8, -50);
			setMotor(port7, -50);
			wait(2, seconds);
		}
	}
}
