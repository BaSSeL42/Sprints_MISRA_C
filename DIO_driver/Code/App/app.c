/*
 *		File		: app.c
 *  	Created on	: Jun 5, 2023
 *      Author		: Bassel Yasser
 *      Description	: APP functions Implementation
 */
/***********************************************************************************************
*											Includes
***********************************************************************************************/
#include <util/delay.h>
#include "../Common/std_types.h"
#include "../HAL/Button/button.h"
#include "../HAL/LED/led.h"

/***********************************************************************************************
*										Global Variables
***********************************************************************************************/
enu_buttonError_t 	gl_enu_button_state;
enu_ledError_t 	 	gl_enu_led_state;
Uint8_t 			gl_u8_pressed;
Uint8_t 			gl_u8_press_counting = 0;

/***********************************************************************************************
*									Functions Implementation
***********************************************************************************************/
void APP_Init(void)
{
	gl_enu_led_state  = HLed_Init(DIO_PINC_0);
	gl_enu_led_state &= HLed_Init(DIO_PINC_1);
	gl_enu_led_state &= HLed_Init(DIO_PINC_2);
	gl_enu_led_state &= HLed_Init(DIO_PINC_3);

	if (gl_enu_led_state == LED_OK)
	{
		gl_enu_led_state  =  HLed_off(DIO_PINC_0);
		gl_enu_led_state &=  HLed_off(DIO_PINC_1);
		gl_enu_led_state &=  HLed_off(DIO_PINC_2);
		gl_enu_led_state &=  HLed_off(DIO_PINC_3);

		if (gl_enu_led_state == LED_OK)
		{
			gl_enu_button_state = HButton_Init(DIO_PINA_6);
		}
	}
}



void APP_start(void)
{
	gl_enu_button_state = HButton_getPinVal(DIO_PINA_6, &gl_u8_pressed);

	if (gl_enu_button_state == BUTTON_OK)
	{
		if (!gl_u8_pressed)
		{
			_delay_ms(300);
			if ( !gl_u8_pressed)
			{
				if (gl_u8_press_counting == 0)
				{
					gl_enu_led_state  = HLed_on(DIO_PINC_0);
					gl_enu_led_state &= HLed_off(DIO_PINC_1);
					gl_enu_led_state &= HLed_off(DIO_PINC_2);
					gl_enu_led_state &= HLed_off(DIO_PINC_3);

					if (gl_enu_led_state == LED_OK)
						gl_u8_press_counting++;
				}
				else if (gl_u8_press_counting == 1)
				{
					gl_enu_led_state  = HLed_on(DIO_PINC_0);
					gl_enu_led_state &= HLed_on(DIO_PINC_1);
					gl_enu_led_state &= HLed_off(DIO_PINC_2);
					gl_enu_led_state &= HLed_off(DIO_PINC_3);

					if (gl_enu_led_state == LED_OK)
						gl_u8_press_counting++;
				}
				else if (gl_u8_press_counting == 2)
				{
					gl_enu_led_state  = HLed_on(DIO_PINC_0);
					gl_enu_led_state &= HLed_on(DIO_PINC_1);
					gl_enu_led_state &= HLed_on(DIO_PINC_2);
					gl_enu_led_state &= HLed_off(DIO_PINC_3);

					if (gl_enu_led_state == LED_OK)
						gl_u8_press_counting++;
				}
				else if (gl_u8_press_counting == 3)
				{
					gl_enu_led_state  = HLed_on(DIO_PINC_0);
					gl_enu_led_state &= HLed_on(DIO_PINC_1);
					gl_enu_led_state &= HLed_on(DIO_PINC_2);
					gl_enu_led_state &= HLed_on(DIO_PINC_3);

					if (gl_enu_led_state == LED_OK)
						gl_u8_press_counting++;
				}
				else if (gl_u8_press_counting == 4)
				{
					gl_enu_led_state  = HLed_off(DIO_PINC_0);
					gl_enu_led_state &= HLed_on(DIO_PINC_1);
					gl_enu_led_state &= HLed_on(DIO_PINC_2);
					gl_enu_led_state &= HLed_on(DIO_PINC_3);

					if (gl_enu_led_state == LED_OK)
						gl_u8_press_counting++;
				}
				else if (gl_u8_press_counting == 5)
				{
					gl_enu_led_state  = HLed_off(DIO_PINC_0);
					gl_enu_led_state &= HLed_off(DIO_PINC_1);
					gl_enu_led_state &= HLed_on(DIO_PINC_2);
					gl_enu_led_state &= HLed_on(DIO_PINC_3);

					if (gl_enu_led_state == LED_OK)
						gl_u8_press_counting++;
				}
				else if (gl_u8_press_counting == 6)
				{
					gl_enu_led_state  = HLed_off(DIO_PINC_0);
					gl_enu_led_state &= HLed_off(DIO_PINC_1);
					gl_enu_led_state &= HLed_off(DIO_PINC_2);
					gl_enu_led_state &= HLed_on(DIO_PINC_3);

					if (gl_enu_led_state == LED_OK)
						gl_u8_press_counting++;
				}
				else if (gl_u8_press_counting == 7)
				{
					gl_enu_led_state  = HLed_off(DIO_PINC_0);
					gl_enu_led_state &= HLed_off(DIO_PINC_1);
					gl_enu_led_state &= HLed_off(DIO_PINC_2);
					gl_enu_led_state &= HLed_off(DIO_PINC_3);

					if (gl_enu_led_state == LED_OK)
						gl_u8_press_counting = 0;
				}
				else
				{
					/* do nothing */
				}
			}
		}
	}
}

/***********************************************************************************************
*										END
***********************************************************************************************/



