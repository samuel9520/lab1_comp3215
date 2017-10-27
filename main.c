/* FreeRTOS Header Files */
#include "FreeRTOS.h"
#include "task.h"

/* Device Header Files */

/* Board Header Files */
#include "Board_LED.h"

/* Macros */
#define xMilliSecondOfTicks (configTICK_RATE_HZ/1000)

/* Task Function Prototype */
void vBlueLEDFunction(void *pvParameters);
void vRedLEDFunction(void *pvParameters);

int main() {
	
	/* Initialize LED 
	 * The vendor's library causes all the LEDs to be initialized. 
	 * We are only using two so this may not be ideal. Maybe the
	 * rest can be used as warning lights.
	 */
	LED_Initialize();
	
	/* Create Tasks 
	 * The priorities of the two tasks doesnt really matter 
	 * a higher (or equal) priority than the idle task though.
	 */
	xTaskCreate(vBlueLEDFunction, (const char *) "Blue",\
			configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
  xTaskCreate(vRedLEDFunction, (const char *) "Red", \
			configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
	
	/* Start the Scheduler */
	vTaskStartScheduler();
	
	/* Should Never Reach Here */
	while(1);
}

/* Task Function Definitions */
void vBlueLEDFunction(void *pvParameters){
	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	
	unsigned int counter = 0;
	while(1){
		vTaskDelayUntil(&xLastWakeTime, xMilliSecondOfTicks*100);
		
		if(counter++%2){
			LED_On(1);
		} else {
			LED_Off(1);
		}
	}
}

void vRedLEDFunction(void *pvParameters){
	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	
	unsigned int counter = 0;
	while(1){
		vTaskDelayUntil(&xLastWakeTime, xMilliSecondOfTicks*500);
		
		if(counter++%2){
			LED_On(3);
		} else {
			LED_Off(3);
		}
	}
}
