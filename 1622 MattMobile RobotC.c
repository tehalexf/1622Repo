#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,	sensorQuadEncoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard			   !!*//

/*

DO NOT TOUCH

*/
#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

#define DEBUGJUMPER in2

//Progeam Variables
int controlscheme = 0; //Controller Scheme
int debug = 0; //Debug Mode
int statusbit = 0; //Controller Type
string mainBattery; //Main Battery Variable
string extensionBattery; //Battery Life Variables
int extensionvalue = 0; //Drive Train Battery Value
int feederOn = 0;
int pauseFeeder = 0;

//Controller Setup
//#define x			vexRT[Ch1] //Right Stick Right/Left
#define RIGHTDRIVE		vexRT[Ch2] //Right Stick Up/Down
#define LEFTDRIVE		vexRT[Ch3]

#define ARMUP			vexRT[Btn5U]
#define ARMDOWN			vexRT[Btn5D]

#define REVERSEFEEDER	vexRT[Btn6U]
#define STOPFEEDER		vexRT[Btn6D]

//--Motor Mappings--
//
//	 Port	   Function					____________________			 _____	 ______
//	   1		Left Arm Down			|					|			|	  |	 |	  |
//	   2		Front Right Wheel 4  	|					|  2	  7 |	  |	 |	  |  	6
//	   3		Rear Right Wheel	 	|		 UP			|			|  UP |	 | UP |
//	   4		Front Left Wheel	 	|					|			|	  |	 |	  |
//	   5		Rear Left Wheel	  		|					|			|	  |	 |	  |		8 ---000000000000---  9
//	   6		Right Arm Up		 	|					|			|	  |	 |	  |
//	   7		Left Arm Up		  		|					|			|	  |	 |	  |
//	   8		feeder			   		|					|			|	  |	 |	  |
//	   9		feeder			   		|					|			|	  |	 |	  |
//	   10	   Right Arm Down	5  		|					|  3	  1 |	  |	 |	  |  	10
//									 	---------------------			 -----	 ------
//											  Base				   Arm (Left)  Arm (Right)

//Pre-Atonomous Functions
void pre_auton()
{
	bStopTasksBetweenModes = true; //Necessary to have brain manage user created tasks
}

task autonomous()
{
	while(SensorValue[leftEncoder] <270)
	{
		if(SensorValue[leftEncoder] > SensorValue[rightEncoder])
		{
			//do stuff
		}
		if(SensorValue[leftEncoder] < SensorValue[rightEncoder])
		{
			//do stuff
		}
		if(SensorValue[leftEncoder] == SensorValue[rightEncoder])
		{
			//Do stuff
		}
	}
}

void waitForPress()
{
	while(nLCDButtons == 0){Sleep 10;} //Wait for Buttonpress
	wait1Msec(5);
}

void waitForRelease()
{
	while(nLCDButtons != 0){Sleep 10;}
	wait1Msec(5);
}

task usercontrol()
{
	debug = 0; //Force No Debug

	//Check if Debug Jumper is inserted
	if(DEBUGJUMPER == 1)
	{
		debug = 1;
	}
	else
	{
		debug = 0;
	}

	//Secret Keypress for Debug Mode Also
	if(vexRT[Btn7U] == 1 && vexRT[Btn7L] == 1 && vexRT[Btn5U] == 1 && vexRT[Btn5D] == 1)
	{
		debug = 1;
	}
	else
	{
		debug = 0;
	}
	statusbit = nVexRCReceiveState; //Get the actual status bit data
	// Possible States Below:
	// No Crystals = 0
	// One Transmitter = 1
	// Two Transmitter = 2
	// One and Two Transmitter = 3
	// One VEXnet = 8
	// Two VEXnet = 10
	//Controller Checks
	controlscheme = 1; //Two Player Activated

	if (vexRT[Btn7DXmtr2] == 1 && vexRT[Btn8DXmtr2] == 1) //Both Buttons on partner controller 8D and 7D are pressed
	{
		controlscheme = 2; //Two Player Activated
	}

	while (true) //Actual Executable
	{
		while(debug == 1) //Enter Debug Mode
		{
			bLCDBacklight = true; //Turn on LCD BackLight
			const short leftButton = 1;
			const short centerButton = 2;
			const short rightButton = 4;
			int count = 0;
			clearLCDLine(0);
			clearLCDLine(1);
			//Switching, not executing menu choices
			while(nLCDButtons != centerButton)
			{
				switch(count)
				{
					case 0: //First Choice
						displayLCDCenteredString(0, "Battery Tester");
						displayLCDCenteredString(1, "Enter");
						displayLCDChar(1, 0, 200);
						displayLCDChar(24, 0, 199);
						waitForPress();
						if(nLCDButtons == leftButton)
						{
							waitForRelease();
							count = 3; //Switch back to n-1
						}
						else if(nLCDButtons == rightButton)
						{
							waitForRelease();
							count++;
						}
						break;
					case 1: //Second Choice
						displayLCDCenteredString(0, "Distance Utility");
						displayLCDCenteredString(1, "		  Enter		 ");
						displayLCDChar(1, 0, 200);
						displayLCDChar(24, 0, 199);
						waitForPress();
						if(nLCDButtons == leftButton)
						{
							waitForRelease();
							count--;
						}
						else if(nLCDButtons == rightButton)
						{
							waitForRelease();
							count++;
						}
						break;
					case 2: //Third Choice
						displayLCDCenteredString(0, "Tilt Utility");
						displayLCDCenteredString(1, "		  Enter		 ");
						displayLCDChar(1, 0, 200);
						displayLCDChar(24, 0, 199);
						waitForPress();
						if(nLCDButtons == leftButton)
						{
							waitForRelease();
							count--;
						}
						else if(nLCDButtons == rightButton)
						{
							waitForRelease();
							count++;
						}
						break;
					case 3: //Final (4th) Choice
						displayLCDCenteredString(0, "Fap Utility");
						displayLCDCenteredString(1, "		  Enter		 ");
						displayLCDChar(1, 0, 200);
						displayLCDChar(24, 0, 199);
						waitForPress();
						if(nLCDButtons == leftButton)
						{
							waitForRelease();
							count--;
						}
						else if(nLCDButtons == rightButton)
						{
							waitForRelease();
							count = 0;
						}
						break;
					default:
						count = 0;
						break;
				} //End of Switch
			} //End of While
			//Continued Code
			clearLCDLine(0);
			clearLCDLine(1);
			//Switch Case that actually runs the user choice
			switch(count)
			{
				case 0: //Battery Tester
					while (nLCDButtons != 2)
					{
						//Battery
						displayLCDString(0, 0, "Primary: ");
						sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
						displayNextLCDString(mainBattery);
						//Second
						displayLCDString(1, 0, "Secondary: ");
						extensionvalue = (int)(SensorValue[in1]);
						sprintf(extensionBattery, "%1.2f%c",extensionvalue, 'V');	//Build the value to be displayed
						displayNextLCDString(extensionBattery);
						wait1Msec(100);
					}
					break;
				case 1: //Distance Utility
					while (nLCDButtons != 2)
					{
						//Distance sensor to be put here
					}
					break;
				case 2: //Tilt Utility
					while (nLCDButtons != 2)
					{
						//Tilt sensor to be put here
					}
					break;
				case 3: //Fap Utility
					while (nLCDButtons != 2)
					{
						//Something Else Here
					}
					break;
				default:
					displayLCDCenteredString(0, "No valid choice");
					displayLCDCenteredString(1, "was made!");
					break;
			} //End Switch
		}//End of Debug
		//Start Non-Debug Code

		SensorValue[rightEncoder] = 0;
		SensorValue[leftEncoder] = 0;

		if(vexRT[Ch3] > 126 && vexRT[Ch2] > 126)
		{
			if(SensorValue[leftEncoder] > SensorValue[rightEncoder])
			{
				motor[port3] = LEFTDRIVE*0.8;	//Front Left3
				motor[port4] = LEFTDRIVE*-0.8; //Back Left2
				motor[port5] = RIGHTDRIVE*-1; //Front Right5
				motor[port2] = RIGHTDRIVE*-1; //Back Right4
			}
			if(SensorValue[leftEncoder] < SensorValue[rightEncoder])
			{
				motor[port3] = LEFTDRIVE;	//Front Left
				motor[port2] = LEFTDRIVE*-1; //Back Left
				motor[port5] = RIGHTDRIVE*-0.8; //Front Right
				motor[port4] = RIGHTDRIVE*-0.8; //Back Right
			}
			if(SensorValue[leftEncoder] == SensorValue[rightEncoder])
			{
				motor[port3] = LEFTDRIVE;	//Front Left
				motor[port2] = LEFTDRIVE*-1; //Back Left
				motor[port5] = RIGHTDRIVE*-1; //Front Right
				motor[port4] = RIGHTDRIVE*-1; //Back Right
			}
		}

		else if(vexRT[Ch3] > 126 && vexRT[Ch2] < -126)
		{
			if(SensorValue[leftEncoder] > SensorValue[rightEncoder])
			{
				motor[port3] = RIGHTDRIVE*-1;	//Front Left3
				motor[port4] = RIGHTDRIVE*-1; //Back Left2
				motor[port5] = LEFTDRIVE*0.8; //Front Righ5t
				motor[port2] = LEFTDRIVE*-0.8; //Back Right4
			}
			if(SensorValue[leftEncoder] < SensorValue[rightEncoder])
			{
				motor[port3] = RIGHTDRIVE*-0.8;	//Front Left3
				motor[port4] = RIGHTDRIVE*-0.8; //Back Left2
				motor[port5] = LEFTDRIVE; //Front Righ5t
				motor[port2] = LEFTDRIVE*-1; //Back Right4
			}
			if(SensorValue[leftEncoder] == SensorValue[rightEncoder])
			{
				motor[port3] = RIGHTDRIVE*-1;	//Front Left3
				motor[port4] = RIGHTDRIVE*-1; //Back Left2
				motor[port5] = LEFTDRIVE; //Front Righ5t
				motor[port2] = LEFTDRIVE*-1; //Back Right4
			}
		}
		else
		{
			//Left Drivetrain
			motor[port3] = RIGHTDRIVE*-1;	//Front Left3
			motor[port4] = RIGHTDRIVE*-1; //Back Left2
			//Right Drivetrain
			motor[port5] = LEFTDRIVE; //Front Righ5t
			motor[port2] = LEFTDRIVE*-1; //Back Right4
		}

		//Left Arm
		//Right Arm
		//feeder Code
		//Feeder States:
		//0: Not Intalized
		//1: Intake
		//2: Paused
		//3. Reversed
		if(feederOn == 0) //Startup Code to start feeder
		{
			feederOn = 1;
		}

		if(feederOn == 1)
		{
			motor[port8] = -127;
			motor[port9] = 127;
		}

		if(feederOn == 2)
		{
			motor[port8] = 0;
			motor[port9] = 0;
		}
		if(feederOn == 3)
		{
			motor[port8] = 127;
			motor[port9] = -127;
		}

		if(REVERSEFEEDER ==1)
		{
			feederOn = 3;
		}

		if(STOPFEEDER == 0 && REVERSEFEEDER == 0&& pauseFeeder == 0)
		{
			feederOn = 1;
		}

		if(STOPFEEDER == 0 && REVERSEFEEDER == 1&& pauseFeeder == 0)
		{
			feederOn = 3;
		}

		if(STOPFEEDER == 0 && REVERSEFEEDER == 1&& pauseFeeder == 1)
		{
			feederOn = 3;
			pauseFeeder =0;
		}

		if(STOPFEEDER ==1 && time1(T1) > 200 )
		{
			if(pauseFeeder == 0)
			{
				feederOn = 2;
				ClearTimer(T1);
				pauseFeeder = 1;
			}
			else
			{
				feederOn = 1;
				ClearTimer(T1);
				pauseFeeder = 0;
			}
		}
	} //End of While
}
