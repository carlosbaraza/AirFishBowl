#include "taskSensors.h"

#define	FRONT_DIST_MEAS	2001
#define	LS_DIST_MEAS	2002
#define	RS_DIST_MEAS	2003
#define HEIGHT_MEAS		2004
#define	CURR_MEAS		2005
#define VOLT_MEAS		2006

double ReadDist(int ADCPin);
double ReadPower(int choice);

/*
	Applied Electronics, Applied Operating Systems
	David Kirwan, Glenn Gall, Kieran Barrett
*/

void SensorsTask()
{
	Fishmsg front, left, right, height, current, voltage;
	double measVal;
	
	while(1){
		// get front distance measurement
		measVal = 12.34;	// dummy value
		front.message_type = FRONT_DIST_MEAS;
		front.message_data = measVal;
		xQueueSendToBack(xFlyportQueue, ( void * ) &front, ( portTickType ) 1);
		
		// get left side distance measurement
		measVal = 12.34;	// dummy value
		left.message_type = LS_DIST_MEAS;
		left.message_data = measVal;
		xQueueSendToBack(xFlyportQueue, ( void * ) &left, ( portTickType ) 1);
		
		// get right side distance measurement
		measVal = 12.34;	// dummy value
		right.message_type = RS_DIST_MEAS;
		right.message_data = measVal;
		xQueueSendToBack(xFlyportQueue, ( void * ) &right, ( portTickType ) 1);
		
		// get height measurement
		measVal = ReadDist(3);	// height sensor connected to ADC3 input (pin 20)
		height.message_type = HEIGHT_MEAS;
		height.message_data = measVal;
		xQueueSendToBack(xFlyportQueue, ( void * ) &height, ( portTickType ) 1);
		
		// get current measurement
		measVal = ReadPower(1);	// case 1 is current
		current.message_type = CURR_MEAS;
		current.message_data = measVal;
		xQueueSendToBack(xFlyportQueue, ( void * ) &current, ( portTickType ) 1);
		
		// get voltage measurement
		measVal = ReadPower(2);	// case 2 is current
		voltage.message_type = VOLT_MEAS;
		voltage.message_data = measVal;
		xQueueSendToBack(xFlyportQueue, ( void * ) &voltage, ( portTickType ) 1);
		
		vTaskDelay(10);
	}
}

double ReadDist(int ADCPin)
{
	int DistVal = ADCVal(ADCPin);
    
    double cm = (DistVal * 0.002) / ( (3.3 / 512) / 2.54 );
    
    return cm;
}

double ReadPower(int choice)
{
	int total = 0;
	int count;
	double meas, average;
		
	switch(choice)
	{
		case 1:		// current measurement
			for(count = 0; count < 100; count++)		// take 100 readings
			{
			  total += ADCVal(1);	// current output of board connected to ADC1 input			  
			}

			average = total / (count + 1);
			
			meas = (average - 186) * 2;
		break;
		case 2:		// voltage measurement
			meas = ADCVal(2) * 4;	// voltage output connected to ADC2 input
		break;	
	}
	
	return meas;
}
