/*
 * main.c
 *
 *  Created on: Apr 3, 2023
 *      Author: Bassel Yasser
 */
/*******************************************************************************
 * 								Includes
 ******************************************************************************/
#include "../Common/Bit_Math.h"
#include "../Common/std_types.h"
#include "../HAL/Button/button.h"
#include "../HAL/LED/led.h"
#include "../HAL/HExtInt/HExtInt.h"
#include "../HAL/HTimer/HTimer.h"

/*******************************************************************************
 * 								Macros
 ******************************************************************************/
#define LED_SEQ0		0
#define LED_SEQ1		1
#define LED_SEQ2		2
#define LED_SEQ3		3
#define LED_SEQ4		4
#define LED_SEQ5		5
#define LED_SEQ6		6
#define LED_SEQ7		7
#define LED_SEQ8		8
#define LED_SEQ9		9

/*******************************************************************************
 * 							Global Variables
 ******************************************************************************/
static Uint32_t 	gl_u32_time_1 = 90;
static Uint32_t 	gl_u32_time_2 = 100;
static Uint8_t 		gl_u8_led_sequence = LED_SEQ1;
static Uint32_t 	gl_u32_timer_counter = 0;

enu_buttonError_t 	gl_enu_button_state 	= BUTTON_OK;
enu_ledError_t 	 	gl_enu_led_state		= LED_OK;
enu_HExtIntError_t	gl_enu_ext_int_state	= HEXTINT_OK;
enu_HTimerError_t	gl_enu_hal_timer_state	= HTIMER_OK;
/*******************************************************************************
 * 						Static Functions prototype
 ******************************************************************************/
static void ledDisplay(void);
static void blink(void);
static void changeBlinkTime(void);

/*******************************************************************************
 * 							main function Implementation
 ******************************************************************************/


void APP_Init(void)
{
	gl_enu_led_state &= HLed_Init(DIO_PINC_0);
	gl_enu_led_state &= HLed_Init(DIO_PINC_1);
	gl_enu_led_state &= HLed_Init(DIO_PINC_2);
	gl_enu_led_state &= HLed_Init(DIO_PINC_3);

	if (gl_enu_led_state == LED_OK)
	{
		gl_enu_button_state &= HButton_Init(DIO_PIND_2);
		gl_enu_button_state &= HButton_Init(DIO_PIND_3);

		if (gl_enu_button_state == BUTTON_OK)
		{
			gl_enu_ext_int_state &= HExtInt_enInit();

			if (gl_enu_ext_int_state == HEXTINT_OK)
			{
				gl_enu_hal_timer_state &= HTimer_enInit();
				gl_enu_ext_int_state &= HExtInt_en_INT0_CBF(ledDisplay);
				gl_enu_ext_int_state &= HExtInt_en_INT1_CBF(changeBlinkTime);

				if(gl_enu_hal_timer_state == HTIMER_OK && gl_enu_ext_int_state == HEXTINT_OK)
				{
					gl_enu_hal_timer_state &= HTimer_enCBF(blink);
					GLI();
				}
				else
				{
					/* do nothing */
				}
			}
			else
			{
				/* do nothing */
			}
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		/* do nothing */
	}


	if (gl_enu_led_state == LED_OK 			 &&
			gl_enu_ext_int_state == HEXTINT_OK	 &&
			gl_enu_hal_timer_state == HTIMER_OK  &&
			gl_enu_button_state == BUTTON_OK)
	{
		gl_enu_led_state &= HLed_off(DIO_PINC_0);
		gl_enu_led_state &= HLed_off(DIO_PINC_1);
		gl_enu_led_state &= HLed_off(DIO_PINC_2);
		gl_enu_led_state &= HLed_off(DIO_PINC_3);

		gl_enu_hal_timer_state &=  HTimer_vidDelayMs(10);
	}
	else
	{
		/* do nothing */
	}

}



void APP_Start(void)
{
	while(1)
	{
		if(gl_u32_timer_counter == gl_u32_time_1 )
		{
			if (gl_u8_led_sequence == LED_SEQ1 && gl_enu_led_state == LED_OK)
			{
				gl_enu_led_state &= HLed_on(DIO_PINC_0);
				gl_enu_led_state &= HLed_off(DIO_PINC_1);
				gl_enu_led_state &= HLed_off(DIO_PINC_2);
				gl_enu_led_state &= HLed_off(DIO_PINC_3);
			}
			else if (gl_u8_led_sequence == LED_SEQ2 && gl_enu_led_state == LED_OK)
			{
				gl_enu_led_state &= HLed_on(DIO_PINC_0);
				gl_enu_led_state &= HLed_on(DIO_PINC_1);
				gl_enu_led_state &= HLed_off(DIO_PINC_2);
				gl_enu_led_state &= HLed_off(DIO_PINC_3);
			}
			else if (gl_u8_led_sequence == LED_SEQ3 && gl_enu_led_state == LED_OK)
			{
				gl_enu_led_state &= HLed_on(DIO_PINC_0);
				gl_enu_led_state &= HLed_on(DIO_PINC_1);
				gl_enu_led_state &= HLed_on(DIO_PINC_2);
				gl_enu_led_state &= HLed_off(DIO_PINC_3);
			}
			else if (gl_u8_led_sequence == LED_SEQ4 && gl_enu_led_state == LED_OK)
			{
				gl_enu_led_state &= HLed_on(DIO_PINC_0);
				gl_enu_led_state &= HLed_on(DIO_PINC_1);
				gl_enu_led_state &= HLed_on(DIO_PINC_2);
				gl_enu_led_state &= HLed_on(DIO_PINC_3);
			}
			else if (gl_u8_led_sequence == LED_SEQ5 && gl_enu_led_state == LED_OK)
			{
				gl_enu_led_state &= HLed_off(DIO_PINC_0);
				gl_enu_led_state &= HLed_on(DIO_PINC_1);
				gl_enu_led_state &= HLed_on(DIO_PINC_2);
				gl_enu_led_state &= HLed_on(DIO_PINC_3);
			}
			else if (gl_u8_led_sequence == LED_SEQ6 && gl_enu_led_state == LED_OK)
			{
				gl_enu_led_state &= HLed_off(DIO_PINC_0);
				gl_enu_led_state &= HLed_off(DIO_PINC_1);
				gl_enu_led_state &= HLed_on(DIO_PINC_2);
				gl_enu_led_state &= HLed_on(DIO_PINC_3);
			}
			else if (gl_u8_led_sequence == LED_SEQ7 && gl_enu_led_state == LED_OK)
			{
				gl_enu_led_state &= HLed_off(DIO_PINC_0);
				gl_enu_led_state &= HLed_off(DIO_PINC_1);
				gl_enu_led_state &= HLed_off(DIO_PINC_2);
				gl_enu_led_state &= HLed_on(DIO_PINC_3);
			}
			else if (gl_u8_led_sequence == LED_SEQ8 && gl_enu_led_state == LED_OK)
			{
				gl_enu_led_state &= HLed_off(DIO_PINC_0);
				gl_enu_led_state &= HLed_off(DIO_PINC_1);
				gl_enu_led_state &= HLed_off(DIO_PINC_2);
				gl_enu_led_state &= HLed_off(DIO_PINC_3);
			}
			else
			{
				/* do nothing */
			}
		}
		else if(gl_u32_timer_counter == gl_u32_time_2 )
		{
			gl_enu_led_state &= HLed_off(DIO_PINC_0);
			gl_enu_led_state &= HLed_off(DIO_PINC_1);
			gl_enu_led_state &= HLed_off(DIO_PINC_2);
			gl_enu_led_state &= HLed_off(DIO_PINC_3);
			gl_u32_timer_counter = 0;
		}
		else
		{
			/*do nothing*/
		}
	}
}




/*******************************************************************************
 * 							Function Implementation
 ******************************************************************************/
/*
 * to choose led sequence
 */
static void ledDisplay(void)
{
	static Uint8_t l_st_u8_seq_version = 1;
	l_st_u8_seq_version++;

	gl_enu_led_state &= HLed_off(DIO_PINC_0);
	gl_enu_led_state &= HLed_off(DIO_PINC_1);
	gl_enu_led_state &= HLed_off(DIO_PINC_2);
	gl_enu_led_state &= HLed_off(DIO_PINC_3);

	if(l_st_u8_seq_version == LED_SEQ1 && gl_enu_led_state == LED_OK)
	{
		gl_u8_led_sequence = LED_SEQ1;
	}
	else if(l_st_u8_seq_version == LED_SEQ2 && gl_enu_led_state == LED_OK)
	{
		gl_u8_led_sequence = LED_SEQ2;
	}
	else if(l_st_u8_seq_version == LED_SEQ3 && gl_enu_led_state == LED_OK)
	{
		gl_u8_led_sequence = LED_SEQ3;
	}
	else if(l_st_u8_seq_version == LED_SEQ4 && gl_enu_led_state == LED_OK)
	{
		gl_u8_led_sequence = LED_SEQ4;
	}
	else if(l_st_u8_seq_version == LED_SEQ5 && gl_enu_led_state == LED_OK)
	{
		gl_u8_led_sequence = LED_SEQ5;
	}
	else if(l_st_u8_seq_version == LED_SEQ6 && gl_enu_led_state == LED_OK)
	{
		gl_u8_led_sequence = LED_SEQ6;
	}
	else if(l_st_u8_seq_version == LED_SEQ7 && gl_enu_led_state == LED_OK)
	{
		gl_u8_led_sequence = LED_SEQ7;
	}
	else if(l_st_u8_seq_version == LED_SEQ8 && gl_enu_led_state == LED_OK)
	{
		gl_u8_led_sequence = LED_SEQ8;
		l_st_u8_seq_version = 0;
	}
	else
	{
		/* do nothing */
	}
}
/*************************************************************************************/
/*
 * simulate LED on duration and LED off duration
 */
static void blink(void)
{
	gl_u32_timer_counter++;
}

/********************************************************************************/
/*
 * change duration of LED on and LED off
 */
static void changeBlinkTime(void)
{
	gl_u32_timer_counter = 0;

	gl_u32_time_1 -= 10;
	gl_u32_time_2 += 10;

	if(gl_u32_time_1 <= 20)
	{
		gl_u32_time_1 = 90;
		gl_u32_time_2 = 100;
	}
	else
	{
		/* do nothing */
	}
}
