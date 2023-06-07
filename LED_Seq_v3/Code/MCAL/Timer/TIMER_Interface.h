/*
 * TIMER_Interface.h
 *
 *  Created on: Apr 3, 2023
 *      Author: Bassel Yasser
 */

#ifndef MCAL_TIMER_TIMER_INTERFACE_H_
#define MCAL_TIMER_TIMER_INTERFACE_H_


/************************************************************************************************/
/*									MACROS														*/
/************************************************************************************************/



/************************************************************************************************/
/*									USER_DEFINED TYPES											*/
/************************************************************************************************/
typedef enum
{
	TIMER_NOK = 0,
	TIMER_OK,

}enu_timerStatus_t;


/********************************/
/*	 TIMER 0 					*/
/********************************/
typedef enum
{
	OVF_MODE,
	PHASE_CORRECT_PWM_MODE,
	CTC_MODE,
	FAST_PWM_MODE,

	TIMER_MODE_INVALID,

}enu_timerMode_t;



typedef enum
{
	TIMER_NO_CLK_SRC,
	TIMER_PRE_1,
	TIMER_PRE_8,
	TIMER_PRE_64,
	TIMER_PRE_256,
	TIMER_PRE_1024,
	TIMER_EXT_CLK_FALLING,
	TIMER_EXT_CLK_RISING,

	TIMER_PRESCALR_INVALID,


}enu_timerPrescalar_t;



typedef enum
{
	CTC_NORMAL=0,
	CTC_TOGGLE_ON_CMP,
	CTC_CLR_ON_CMP,
	CTC_SET_ON_CMP,
	CTC_INVALID,

}enu_ctcMode_t;

typedef enum
{
	PWM_NORMAL=0,
	PWM_CLR_ON_CMP,
	PWM_SET_ON_CMP,
	PWM_INVALID,

}enu_pwmMode_t;






typedef void (*ptrFunc_t)(void);



/************************************************************************************************/
/*									FUNCTIONS PROTOTYPE											*/
/************************************************************************************************/
enu_timerStatus_t enuTimer0_init (enu_timerMode_t);
enu_timerStatus_t u8Timer0_setPrescallar(enu_timerPrescalar_t);
enu_timerStatus_t vidTimer0_OvfIrqEnable(void);
enu_timerStatus_t vidTimer0_OvfIrqDisable(void);
enu_timerStatus_t vidTimer0_start(void);
enu_timerStatus_t vidTimer0_stop(void);

enu_timerStatus_t u8Timer0_setTime_ms(Uint32_t u32_time_ms);

enu_timerStatus_t vidTimer0_setcbf_OVF(ptrFunc_t ptrFunc);

/***********************************************************************/



#endif /* MCAL_TIMER_TIMER_INTERFACE_H_ */
