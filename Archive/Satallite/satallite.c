#pragma config(Sensor, dgtl1,  trackend,            sensorTouch)
#pragma config(Sensor, dgtl2,  sonar,               sensorSONAR_inch)
#pragma config(Sensor, dgtl4,  quad,                sensorQuadEncoder)
#pragma config(Motor,  port2,           drive,         tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while(true){
		wait1Msec(2000);						// Robot waits for 2000 milliseconds before executing program
		SensorValue[quad]=0;        // Set optical shaft encoder quadrature count to zero
		int targetCount = 1;

		while(vexRT[Btn6U] == 0)  //Satellite waits until the button is pressed before moving on
		{
		}
		writeDebugStreamLine("New scan started");

		setMotor(drive, -30);  //Turn on the motor in reverse at 64

		while(SensorValue[trackend] == 0) //While the final button isn't pressed...
		{

			while(abs(SensorValue[quad]) < targetCount && SensorValue[trackend] == 0)//Wait for the encoder count to reach the target polling point (125 counts or 3 inches of travel) and satellite has not reached end of the path
			{
			}
			writeDebugStreamLine("%d \t %d", SensorValue(quad), SensorValue(sonar));  //...and then write optical shaft encoder and sonar values to the debug stream
			targetCount = targetCount + 41; // Sensor data is written every 125 counts or 3 inches of travel
		}

		stopMotor(drive); //Stop the motor
		writeDebugStreamLine("Scan ended");

		//returing to starting position
		int oldCount = SensorValue(quad)-25;//-25 to account for inertia when stopping
		SensorValue[quad]=0;        // Set optical shaft encoder quadrature count to zero
		setMotor(drive, 60);
		while(abs(SensorValue[quad]) < oldCount )
		{
		}
		stopMotor(drive);

	}
}   // End task main
