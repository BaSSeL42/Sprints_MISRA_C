/************************************************************************************************/
/*									INCLUDES													*/
/************************************************************************************************/
#include "avr/interrupt.h"
#include "../../Common/std_types.h"
#include "../../Common/Bit_Math.h"
#include "EXTINT_Private.h"
#include "EXTINT_Interface.h"


/************************************************************************************************/
/*									USER_DEFINED TYPES											*/
/************************************************************************************************/
ptr_func_t gl_ptr_func_int0_cbk = NULL;
ptr_func_t gl_ptr_func_int1_cbk = NULL;

/************************************************************************************************/
/*									FUNCTION_IMPLEMENTATION										*/
/************************************************************************************************/
Uint8_t vidExtInt_init(enu_int_type_t enIntType, enu_sns_ctrl_t enSensControl)
{
	Uint8_t l_u8_err_status = E_INT_OK;
	if(enIntType < INT_TYPE_INVALID && enSensControl < SENS_CONTROL_INVALID)
	{
		if (enIntType == INT_0)
		{
//			DIO_s8SETPinVal(DIO_PIND_2, HIGH);
			switch (enSensControl)
			{
				case LOW_LEVEL 	: ClrBit(MCUCR_REG, ISC00); ClrBit(MCUCR_REG, ISC01); break;
				case ANY_LOGICAL: SetBit(MCUCR_REG, ISC00); ClrBit(MCUCR_REG, ISC01); break;
				case FALL_EDGE 	: ClrBit(MCUCR_REG, ISC00); SetBit(MCUCR_REG, ISC01); break;
				case RISE_EDGE 	: SetBit(MCUCR_REG, ISC00); SetBit(MCUCR_REG, ISC01); break;
				default : l_u8_err_status = E_INT_NOK; break;
			}

			SetBit(GICR_REG, INT0);
			SetBit(GIFR_REG, INTF0);	// to clear flag for Interrupt 0
		}
		else if (enIntType == INT_1)
		{
//			DIO_s8SETPinVal(EXT_INT1, HIGH);
			switch (enSensControl)
			{
				case LOW_LEVEL 	: ClrBit(MCUCR_REG, ISC10); ClrBit(MCUCR_REG, ISC11); break;
				case ANY_LOGICAL: SetBit(MCUCR_REG, ISC10); ClrBit(MCUCR_REG, ISC11); break;
				case FALL_EDGE 	: ClrBit(MCUCR_REG, ISC10); SetBit(MCUCR_REG, ISC11); break;
				case RISE_EDGE 	: SetBit(MCUCR_REG, ISC10); SetBit(MCUCR_REG, ISC11); break;
				default : l_u8_err_status = E_INT_NOK; break;
			}
			SetBit(GICR_REG, INT1);
			SetBit(GIFR_REG, INTF1);	// to clear flag for Interrupt 1
		}
		else if (enIntType == INT_2)
		{
//			DIO_s8SETPinVal(EXT_INT2, HIGH);
			switch (enSensControl)
			{
				case FALL_EDGE 	: ClrBit(MCUCSR_REG, ISC2);  break;
				case RISE_EDGE 	: SetBit(MCUCSR_REG, ISC2);  break;
				default : l_u8_err_status = E_INT_NOK; break;
			}
			SetBit(GICR_REG, INT2);
			SetBit(GIFR_REG, INTF2);  // to clear flag for Interrupt 2
		}
	}
	else
	{
		l_u8_err_status = E_INT_NOK;
	}

//	SetBit(SREG_REG, I); // enable global interrupt


	return l_u8_err_status;
}



Uint8_t EXTINT_INT0_CallBackFunc(ptr_func_t ptr_func)
{
	Uint8_t l_u8_err_status = E_INT_OK;
	if (ptr_func != NULL)
	{
		gl_ptr_func_int0_cbk = ptr_func;
	}
	else
	{
		l_u8_err_status = E_INT_NOK;
	}

	return l_u8_err_status;
}


Uint8_t EXTINT_INT1_CallBackFunc(ptr_func_t ptr_func)
{

	Uint8_t l_u8_err_status = E_INT_OK;
	if (ptr_func != NULL)
	{
		gl_ptr_func_int1_cbk = ptr_func;
	}
	else
	{
		l_u8_err_status = E_INT_NOK;
	}

	return l_u8_err_status;
}




ISR(INT0_vect)
{
	gl_ptr_func_int0_cbk();
}

ISR(INT1_vect)
{
	gl_ptr_func_int1_cbk();
}
