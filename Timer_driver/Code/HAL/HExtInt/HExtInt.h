/*
 *		File		: hextInt.h
 *  	Created on	: Apr 4, 2023
 *      Author		: Bassel Yasser
 *      Description	: HAL external Interrupt functions prototypes
 */
/***********************************************************************************************
*										File Guard
***********************************************************************************************/
#ifndef HAL_HEXTINT_HEXTINT_H_
#define HAL_HEXTINT_HEXTINT_H_
/***********************************************************************************************
*											Includes
***********************************************************************************************/
#include "../../MCAL/ExtInt/EXTINT_Interface.h"
/***********************************************************************************************
*										User defined data types
***********************************************************************************************/
typedef enum
{
	HEXTINT_NOK = 0,
	HEXTINT_OK

}enu_HExtIntError_t;



//typedef void(*ptr_func)(void);

/***********************************************************************************************
*									 Functions prototypes
***********************************************************************************************/
enu_HExtIntError_t HExtInt_enInit(void);

enu_HExtIntError_t HExtInt_en_INT0_CBF(ptr_func_t ptr_func);

enu_HExtIntError_t HExtInt_en_INT1_CBF(ptr_func_t ptr_func);




#endif /* HAL_HEXTINT_HEXTINT_H_ */
/***********************************************************************************************
*									File End
***********************************************************************************************/
