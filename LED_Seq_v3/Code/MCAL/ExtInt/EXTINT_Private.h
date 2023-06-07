/*
 * EXTINT_Private.h
 *
 *  Created on: Apr 3, 2023
 *      Author: hp
 */

#ifndef MCAL_EXTINT_EXTINT_PRIVATE_H_
#define MCAL_EXTINT_EXTINT_PRIVATE_H_

#define MCUCR_REG	(*(volatile Uint8_t*)(0x55))
#define MCUCSR_REG	(*(volatile Uint8_t*)(0x54))
#define GICR_REG	(*(volatile Uint8_t*)(0x5B))
#define GIFR_REG	(*(volatile Uint8_t*)(0x5A))

#define SREG_REG 	(*(volatile Uint8_t*)(0x5F)) // for global interrupt



#endif /* 04_MCAL_EXTINT_EXTINT_PRIVATE_H_ */
