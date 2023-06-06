/*
 * EXTINT_Interface.h
 *
 *  Created on: Apr 3, 2023
 *      Author: hp
 */

#ifndef MCAL_EXTINT_EXTINT_INTERFACE_H_
#define MCAL_EXTINT_EXTINT_INTERFACE_H_


/************************************************************************************************/
/*									MACROS														*/
/************************************************************************************************/

#define E_INT_OK		1
#define E_INT_NOK		0

/* MCUCR register bits*/
#define ISC00		0
#define ISC01		1
#define ISC10		2
#define ISC11		3
/* MCUCSR register bits*/
#define ISC2		6
/* GICR register bits*/
#define INT0		6
#define INT1		7
#define INT2		5
/* GIFR register bits*/
#define INTF0		6
#define INTF1		7
#define INTF2		5
/* SREG register bits*/
#define I			7

/************************************************************************************************/
/*									USER_DEFINED TYPES											*/
/************************************************************************************************/
typedef enum
{
	INT_0 = 0,
	INT_1,
	INT_2,
	INT_TYPE_INVALID,

}enu_int_type_t;

typedef enum
{
	LOW_LEVEL = 0,
	ANY_LOGICAL,
	FALL_EDGE,
	RISE_EDGE,
	SENS_CONTROL_INVALID,
}enu_sns_ctrl_t;


typedef void(*ptr_func_t)(void);

/************************************************************************************************/
/*									FUNCTION_PROTOTYPE											*/
/************************************************************************************************/
Uint8_t vidExtInt_init(enu_int_type_t, enu_sns_ctrl_t);

Uint8_t EXTINT_INT0_CallBackFunc(ptr_func_t ptr_func);

Uint8_t EXTINT_INT1_CallBackFunc(ptr_func_t ptr_func);



#endif /* 04_MCAL_EXTINT_EXTINT_INTERFACE_H_ */
