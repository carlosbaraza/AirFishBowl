#include "taskElectronicsWIT.h"

/*
	Applied Electronics, Applied Operating Systems
	David Kirwan, Patrick Cody
*/

void ElectronicsWITTask()
{
	while(1){
		vTaskSuspendAll();	
		UARTWrite(1,"vTaskSuspendAll task 1\r\n");
		
		IOPut(p19, toggle);
		IOPut(p21, toggle);
		
		vTaskDelay(100);
		
		UARTWrite(1,"xTaskResumeAll task 1\r\n");
		xTaskResumeAll();
	}
}