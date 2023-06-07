
/*************************************************************************************************************
 * 								Includes
 ************************************************************************************************************/
#include "avr/interrupt.h"
#include "../../Common/std_types.h"
#include "../../Common/Bit_Math.h"
#include "TIMER_Private.h"
#include "TIMER_Interface.h"

/*************************************************************************************************************
 * 								Macros
 ************************************************************************************************************/
#define PRESCALLER_CLR_MSK		(0b11111000)
#define PRESCALLER_OFFSET		CS00
#define F_CPU					8000000UL

#define STOPPED					0
#define RUNNING					1

#define OVF_TICKS				256UL
#define MAX_TIM_MS				5000UL
/*************************************************************************************************************
 * 								Global/Static Variables
 ************************************************************************************************************/
static enu_timerPrescalar_t gl_enu_prescaller;
static Uint8_t 				gl_u8_timer_status;
static Uint8_t	 			gl_u8_ovf;
static Uint16_t 			gl_u16_preload;
static ptrFunc_t  			gl_ptr_func_call_back = NULL;


static Uint16_t prescaller_map[6] = {
		0,
		1,
		8,
		64,
		256,
		1024
};

/*************************************************************************************************************
 * 							Function Implementation
 ************************************************************************************************************/
enu_timerStatus_t enuTimer0_init (enu_timerMode_t enTimerMode)
{
	enu_timerStatus_t errorStatus = TIMER_OK;

	if(enTimerMode < TIMER_MODE_INVALID)
	{
		switch (enTimerMode)
		{
		case OVF_MODE 				: ClrBit(TCCR0_REG, WGM01);ClrBit(TCCR0_REG, WGM00); break;
		case PHASE_CORRECT_PWM_MODE : ClrBit(TCCR0_REG, WGM01);SetBit(TCCR0_REG, WGM00); break;
		case CTC_MODE 				: SetBit(TCCR0_REG, WGM01);ClrBit(TCCR0_REG, WGM00); break;
		case FAST_PWM_MODE 			: SetBit(TCCR0_REG, WGM01);SetBit(TCCR0_REG, WGM00); break;
		default 					: /* do nothing */ 									 break;
		}
	}
	else
	{
		errorStatus = TIMER_NOK;
	}
	return errorStatus;
}


/*************************************************************************************************************/
enu_timerStatus_t u8Timer0_setPrescallar(enu_timerPrescalar_t Copy_enPrescal)
{
	enu_timerStatus_t errorStatus = TIMER_OK;
	Uint8_t temp_reg;
	if(Copy_enPrescal < TIMER_PRESCALR_INVALID)
	{
		gl_enu_prescaller = Copy_enPrescal;
		if (gl_u8_timer_status == RUNNING)
		{
			temp_reg = TCCR0_REG;		 // read
			temp_reg &= PRESCALLER_CLR_MSK;  // mod
			temp_reg |=  gl_enu_prescaller << PRESCALLER_OFFSET; // mod
			TCCR0_REG |= temp_reg;		// write
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		errorStatus = TIMER_NOK;
	}
	return errorStatus;
}

/*************************************************************************************************************/
enu_timerStatus_t vidTimer0_OvfIrqEnable(void)
{
	enu_timerStatus_t errorStatus = TIMER_OK;

	SetBit(TIMSK_REG, TOIE0);

	return errorStatus;

}

/*************************************************************************************************************/
enu_timerStatus_t vidTimer0_OvfIrqDisable(void)
{
	enu_timerStatus_t errorStatus = TIMER_OK;

	ClrBit(TIMSK_REG, TOIE0);

	return errorStatus;
}

/*************************************************************************************************************/
enu_timerStatus_t vidTimer0_start(void)
{
	enu_timerStatus_t errorStatus = TIMER_OK;

	if (gl_enu_prescaller != TIMER_NO_CLK_SRC)
	{
		TCCR0_REG |=  gl_enu_prescaller << PRESCALLER_OFFSET;
		gl_u8_timer_status  = RUNNING;
	}
	else
	{
		errorStatus = TIMER_NOK;
	}
	return errorStatus;
}

/*************************************************************************************************************/
enu_timerStatus_t vidTimer0_stop(void)
{
	enu_timerStatus_t errorStatus = TIMER_OK;

	TCCR0_REG &=  PRESCALLER_CLR_MSK;
	gl_u8_timer_status = STOPPED;

	return errorStatus;
}
/*************************************************************************************************************/
enu_timerStatus_t u8Timer0_setTime_ms(Uint32_t u32_time_ms)
{
	enu_timerStatus_t errorStatus = TIMER_OK;
	Uint32_t desired_ticks;
	Float32_t tick_time_ms;
	if( u32_time_ms < MAX_TIM_MS )
	{
		tick_time_ms = (Float32_t)prescaller_map[gl_enu_prescaller] / ((Uint32_t)F_CPU / 1000U)  ;
		desired_ticks = u32_time_ms / tick_time_ms;

		/* Compare ticks with OVF_ticks */
		if(desired_ticks == OVF_TICKS)
		{
			gl_u8_ovf = 1;
		}
		else if(desired_ticks < OVF_TICKS)
		{
			gl_u16_preload = OVF_TICKS - desired_ticks;
			TCNT0_REG = gl_u16_preload;
			gl_u8_ovf = 1;
		}
		else if(desired_ticks > OVF_TICKS)
		{
			gl_u8_ovf = (Uint8_t)(desired_ticks / OVF_TICKS);
			gl_u16_preload = (uint16_t)(OVF_TICKS - (desired_ticks % OVF_TICKS ));
			TCNT0_REG = gl_u16_preload;
			if (gl_u16_preload > 0U)
			{
				gl_u8_ovf++;
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
		errorStatus = TIMER_NOK;
	}
	return errorStatus;
}

/*************************************************************************************************************/
enu_timerStatus_t vidTimer0_setcbf_OVF(ptrFunc_t ptrFunc)
{
	enu_timerStatus_t errorStatus = TIMER_OK;
	if (ptrFunc != NULL)
	{
		gl_ptr_func_call_back = ptrFunc;
	}
	else
	{
		errorStatus = TIMER_NOK;
	}
	return errorStatus;
}


/*************************************************************************************************************
 * 							ISR Interrupt Handling
 ************************************************************************************************************/
ISR(TIMER0_OVF_vect)
{
	static Uint8_t counter = 0;
	counter++;
	if(counter == gl_u8_ovf)
	{
		if (gl_ptr_func_call_back != NULL)
		{
			counter = 0;
			TCNT0_REG = gl_u16_preload;
			gl_ptr_func_call_back();
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
