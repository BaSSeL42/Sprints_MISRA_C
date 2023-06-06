/*
 *		File		: hextInt.c
 *  	Created on	: Apr 4, 2023
 *      Author		: Bassel Yasser
 *      Description	: HAL external Interrupt functions Implementation
 */
/***********************************************************************************************
*											Includes
***********************************************************************************************/
#include "../../Common/std_types.h"
#include "../../Common/Bit_Math.h"
#include "HExtInt.h"


/***********************************************************************************************
*										Functions Implementation
***********************************************************************************************/
enu_HExtIntError_t HExtInt_enInit(void)
{
	enu_HExtIntError_t errorStatus = HEXTINT_OK;

	errorStatus &= vidExtInt_init(INT_0 , FALL_EDGE );
	errorStatus &= vidExtInt_init(INT_1 , FALL_EDGE );

	return errorStatus;
}

enu_HExtIntError_t HExtInt_en_INT0_CBF(ptr_func_t ptr_func)
{
	enu_HExtIntError_t errorStatus = HEXTINT_OK;

	if (ptr_func != NULL)
	{
		errorStatus &= EXTINT_INT0_CallBackFunc(ptr_func);
	}
	else
	{
		errorStatus = HEXTINT_NOK;
	}
	return errorStatus;
}

enu_HExtIntError_t HExtInt_en_INT1_CBF(ptr_func_t ptr_func)
{
	enu_HExtIntError_t errorStatus = HEXTINT_OK;

	if (ptr_func != NULL)
	{
		errorStatus &= EXTINT_INT1_CallBackFunc(ptr_func);
	}
	else
	{
		errorStatus = HEXTINT_NOK;
	}
	return errorStatus;
}
/***********************************************************************************************
*										File END
***********************************************************************************************/
