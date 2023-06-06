/*
 * HTimer.c
 *
 *  Created on: Apr 5, 2023
 *      Author: Bassel Yasser
 */
/*************************************************************************************************************
 * 								Includes
 ************************************************************************************************************/
#include "../../Common/std_types.h"
#include "../../Common/Bit_Math.h"
#include "../../MCAL/Timer/TIMER_Interface.h"
#include "HTimer.h"

/*************************************************************************************************************
 * 							Function Implementation
 ************************************************************************************************************/
enu_HTimerError_t HTimer_enInit(void)
{
	enu_HTimerError_t errorStatus = HTIMER_OK;

	errorStatus &= enuTimer0_init (OVF_MODE);
	errorStatus &= u8Timer0_setPrescallar(TIMER_PRE_64);
	errorStatus &= vidTimer0_OvfIrqEnable();

	return errorStatus;

}
/*************************************************************************************************************/
enu_HTimerError_t HTimer_vidDelayMs( Uint32_t u32_delay )
{
	enu_HTimerError_t errorStatus = HTIMER_OK;

	errorStatus &=  u8Timer0_setTime_ms(u32_delay);
	errorStatus &=  vidTimer0_start();

	return errorStatus;
}
/*************************************************************************************************************/
enu_HTimerError_t HTimer_enCBF(ptr_funcc pFunc)
{
	enu_HTimerError_t errorStatus = HTIMER_OK;

	if(pFunc != NULL)
	{
		errorStatus &= vidTimer0_setcbf_OVF(pFunc);

	}else{
		errorStatus = HTIMER_NOK;
	}

	return errorStatus;

}
/*************************************************************************************************************/
/*							End Of Implementation
*************************************************************************************************************/

