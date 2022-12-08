 /******************************************************************************
 *
 * Module:Ultrasonic sensor HC-SR04
 *
 * File Name: ultrasonic.h
 *
 * Description: Source file for the Ultrasonic sensor HC-SR04 driver
 *
 * Author: Shimaa Gamal
 *
 *******************************************************************************/

#include "ultrasonic.h"
#include"icu.h"
#include "gpio.h"
#include "common_macros.h"
#include <util/delay.h>



uint8 g_edgeCount=0;
uint16 g_timeHighEcoPulse=0;


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


void Ultrasonic_init(void){

	Icu_ConfigType Icu_Config = {F_CPU_8,RISING};    /*The ICU configured with frequency F_CPU/8
	and to detect the raising edge as the first edge */

	Icu_init(&Icu_Config);                           /*Initialize the ICU*/

	Icu_setCallBack(Ultrasonic_edgeProcessing);      /* Setup the ICU call back function. */

	GPIO_setupPinDirection(TR_PORT_ID,TR_PIN_ID,PIN_OUTPUT);    /*configure the trigger pin as output pin*/

}



void Ultrasonic_Trigger (void){
	GPIO_writePin(TR_PORT_ID,TR_PIN_ID,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TR_PORT_ID,TR_PIN_ID,LOGIC_LOW);
}


uint16 Ultrasonic_readDistance(void){
	uint16 distance;
	Ultrasonic_Trigger();
	distance = g_timeHighEcoPulse/ 58.8 ;
    return distance ;
}

void Ultrasonic_edgeProcessing (void){

	g_edgeCount++;
		if(g_edgeCount == 1)
		{
			/* clear the timer value to begin counting when detecting the first rising edge */

			Icu_clearTimerValue();

			Icu_setEdgeDetectionType(FALLING);
		}
		else if(g_edgeCount == 2)
		{
			/*save the time of the eco pulse*/

			g_timeHighEcoPulse = Icu_getInputCaptureValue();

			Icu_clearTimerValue();

			Icu_setEdgeDetectionType(RISING);

			g_edgeCount = 0;
		}
}

