/*
 *		File		: button.c
 *  	Created on	: Apr 4, 2023
 *      Author		: Bassel Yasser
 *      Description	: Button functions Implementation
 */
/***********************************************************************************************
*											Includes
***********************************************************************************************/
#include "../../Common/std_types.h"
#include "../../Common/Bit_Math.h"
//#include "../../MCAL/DIO/DIO_Interface.h"

#include "button.h"


/***********************************************************************************************
*										Functions Implementation
***********************************************************************************************/
enu_buttonError_t HButton_Init(enu_pin en_pinx)
{
	enu_buttonError_t errorStatus = BUTTON_OK;

	if ( en_pinx < PIN_INVALID )
	{
		errorStatus &= DIO_s8SETPinDir(en_pinx, INPUT);
		errorStatus &= DIO_s8SETPinVal(en_pinx, HIGH);
	}
	else
	{
		errorStatus = BUTTON_NOK;
	}

	return errorStatus;
}


enu_buttonError_t HButton_getPinVal(enu_pin en_pinx,  Uint8_t* pu8_refVal )
{
	enu_buttonError_t errorStatus = BUTTON_OK;

	if ( en_pinx < PIN_INVALID && pu8_refVal != NULL )
	{
		errorStatus &= DIO_s8GETPinVal(en_pinx, pu8_refVal);
	}
	else
	{
		errorStatus = BUTTON_NOK;
	}

	return errorStatus;

}

/***********************************************************************************************
*										END
***********************************************************************************************/
