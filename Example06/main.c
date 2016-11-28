/*
 /* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "Sensor.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_ssp.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_timer.h"
#include "oled.h"
#include "oledClass.h"


/* Demo includes. */
#include "basic_io.h"

/* The task functions. */
void vLeitura( void *pvParameters );
void vImprime( void *pvParameters );
/*-----------------------------------------------------------*/
/* Declare a variable of type xQueueHandle.  This is used to store the queue
that is accessed by all two tasks. */
xQueueHandle xQueue;

int main( void )
{
	Sensor_new();
	oledClass();
	xQueue = xQueueCreate(5,sizeof(long));

	if(xQueue != NULL){
		/* A função vLeitura, lê os dados do sensor e adiciona na fila com menor prioridade. */
		xTaskCreate( vLeitura, "Leitura Sensor", 240, NULL, 1, NULL );
		/* A função vImprime, imprime os dados do sensor no oled com maior prioridade. */
		xTaskCreate( vImprime, "Impressao", 240, NULL, 2, NULL );

		/* Start the scheduler so our tasks start executing. */
		vTaskStartScheduler();
	}


	for( ;; );
	return 0;
}
/*-----------------------------------------------------------*/
static void intToString(int value, uint8_t* pBuf, uint32_t len, uint32_t base)
{
    static const char* pAscii = "0123456789abcdefghijklmnopqrstuvwxyz";
    int pos = 0;
    int tmpValue = value;

    // the buffer must not be null and at least have a length of 2 to handle one
    // digit and null-terminator
    if (pBuf == NULL || len < 2)
    {
        return;
    }

    // a valid base cannot be less than 2 or larger than 36
    // a base value of 2 means binary representation. A value of 1 would mean only zeros
    // a base larger than 36 can only be used if a larger alphabet were used.
    if (base < 2 || base > 36)
    {
        return;
    }

    // negative value
    if (value < 0)
    {
        tmpValue = -tmpValue;
        value    = -value;
        pBuf[pos++] = '-';
    }

    // calculate the required length of the buffer
    do {
        pos++;
        tmpValue /= base;
    } while(tmpValue > 0);


    if (pos > len)
    {
        // the len parameter is invalid.
        return;
    }

    pBuf[pos] = '\0';

    do {
        pBuf[--pos] = pAscii[value % base];
        value /= base;
    } while(value > 0);

    return;
}
/*-----------------------------------------------------------*/

void vLeitura( void *pvParameters )
{
	char *pcTaskName;
	long luz=0;
	portBASE_TYPE xStatus;
	portTickType xLastWakeTime = xTaskGetTickCount();
	volatile unsigned long ul;


	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{

		luz=Sensor_read();// lê o sensor

		xStatus = xQueueSendToBack(xQueue,&luz,0);// adiciona na fila o dado lido

		if( xStatus != pdPASS )
		/* Print out the name of this task.  This task just does this repeatedly
		without ever blocking or delaying. */
		vPrintString( pcTaskName );
		vPrintString("Lendo o sensor!!!\n");


		for( ul = 0; ul < 0x1fff; ul++ )
		{
			asm volatile( "NOP" );
		}
	}
}
/*-----------------------------------------------------------*/

void vImprime( void *pvParameters )
{
	portTickType xLastWakeTime;
	/* The xLastWakeTime variable needs to be initialized with the current tick
	count.  Note that this is the only time we access this variable.  From this
	point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
	API function. */
	xLastWakeTime = xTaskGetTickCount();
	long luz = 0;
	uint8_t buf[10];
	portBASE_TYPE xStatus;
	const portTickType xTicksToWait = 500 / portTICK_RATE_MS;

	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		xStatus = xQueueReceive( xQueue, &luz, xTicksToWait);
		if( xStatus == pdPASS ){

			intToString(luz, buf, 10, 10);
			oledPrint(buf);
		}
		/* Print out the name of this task. */
		vPrintString( "Periodic task is running..........\n" );

		/* We want this task to execute exactly every 10 milliseconds. */
		vTaskDelayUntil( &xLastWakeTime, ( 10 / portTICK_RATE_MS ) );
	}
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing. */
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing. */
}


