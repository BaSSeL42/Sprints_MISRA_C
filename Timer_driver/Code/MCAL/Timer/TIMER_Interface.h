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
/* TCCRO REG */
#define CS00		0
#define CS01		1
#define CS02		2
#define WGM01		3
#define COM00		4
#define COM01		5
#define WGM00		6
#define FOC0		7

/* TIMSK REG */
#define TOIE0		0
#define OCIE0		1
#define TOIE1		2
#define OCIE1A		3
#define OCIE1B		4
#define TICIE1		5
#define TOIE2		6
#define OCIE2		7

/* TIFR REG */
#define TOV0		0
#define OCF0		1
#define TOV1		2
#define OCF1A		3
#define OCF1B		4
#define ICF1		5
#define TOV2		6
#define OCF2		7


/* SREG REG */
#define timer_I		7

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


enu_timerStatus_t enuFastPWM0_init(enu_pwmMode_t ,enu_timerPrescalar_t );
enu_timerStatus_t vidPWM0_Generate(Uint8_t);

enu_timerStatus_t vidTimer0_setcbf_OVF(ptrFunc_t ptrFunc);

/***********************************************************************/



#endif /* MCAL_TIMER_TIMER_INTERFACE_H_ */
