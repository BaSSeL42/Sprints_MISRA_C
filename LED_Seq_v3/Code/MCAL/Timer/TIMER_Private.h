/*
 * TIMER_Private.h
 *
 *  Created on: Apr 3, 2023
 *      Author: hp
 */

#ifndef MCAL_TIMER_TIMER_PRIVATE_H_
#define MCAL_TIMER_TIMER_PRIVATE_H_

/********************************* TIMER0 REGISTERS ******************************************/
#define TCCR0_REG 	(*(volatile Uint8_t*)(0x53))
#define TCNT0_REG 	(*(volatile Uint8_t*)(0x52))
#define OCR0_REG 	(*(volatile Uint8_t*)(0x5C))

/********************************* TIMER1 REGISTERS ******************************************/
#define TCCR1A_REG 	(*(volatile Uint8_t*)(0x4F))
#define TCCR1B_REG 	(*(volatile Uint8_t*)(0x4E))
#define TCNT1H_REG 	(*(volatile Uint8_t*)(0x4D))
#define TCNT1L_REG 	(*(volatile Uint8_t*)(0x4C))
#define TCNT1_REG 	(*(volatile Uint16_t*)(0x4C))
#define OCR1AH_REG 	(*(volatile Uint8_t*)(0x4B))
#define OCR1AL_REG 	(*(volatile Uint8_t*)(0x4A))
#define OCR1A_REG 	(*(volatile Uint16_t*)(0x4A))

#define OCR1BH_REG 	(*(volatile Uint8_t*)(0x49))
#define OCR1BL_REG 	(*(volatile Uint8_t*)(0x48))
#define ICR1H_REG 	(*(volatile Uint8_t*)(0x47))
#define ICR1L_REG 	(*(volatile Uint8_t*)(0x46))
#define ICR1_REG 	(*(volatile Uint16_t*)(0x46))


#ifndef SREG_REG
#define SREG_REG 	(*(volatile Uint8_t*)(0x5F)) // for global interrupt
#endif


/********************************* TIMER2 REGISTERS ******************************************/
#define TCCR2_REG 	(*(volatile Uint8_t*)(0x45))
#define TCNT2_REG 	(*(volatile Uint8_t*)(0x44))
#define OCR2_REG 	(*(volatile Uint8_t*)(0x43))

/********************************* TIMER_ALL REGISTERS ******************************************/
#define TIFR_REG 	(*(volatile Uint8_t*)(0x58))
#define TIMSK_REG 	(*(volatile Uint8_t*)(0x59))






/* TCCRO REG */
#ifndef CS00
#define CS00		0
#endif

#ifndef CS01
#define CS01		1
#endif

#ifndef CS02
#define CS02		2
#endif

#ifndef WGM01
#define WGM01		3
#endif

#ifndef COM00
#define COM00		4
#endif

#ifndef COM01
#define COM01		5
#endif

#ifndef WGM00
#define WGM00		6
#endif


#ifndef FOC0
#define FOC0		7
#endif




/* TIMSK REG */

#ifndef TOIE0
#define TOIE0		0
#endif

#ifndef OCIE0
#define OCIE0		1
#endif


#ifndef TOIE1
#define TOIE1		2
#endif


#ifndef OCIE1A
#define OCIE1A		3
#endif


#ifndef OCIE1B
#define OCIE1B		4
#endif

#ifndef TICIE1
#define TICIE1		5
#endif


#ifndef TOIE2
#define TOIE2		6
#endif


#ifndef OCIE2
#define OCIE2		7
#endif


/* TIFR REG */

#ifndef TOV0
#define TOV0		0
#endif

#ifndef OCF0
#define OCF0		1
#endif


#ifndef TOV1
#define TOV1		2
#endif


#ifndef OCF1A
#define OCF1A		3
#endif


#ifndef OCF1B
#define OCF1B		4
#endif

#ifndef ICF1
#define ICF1		5
#endif


#ifndef TOV2
#define TOV2		6
#endif


#ifndef OCF2
#define OCF2		7
#endif


/* SREG REG */
#ifndef timer_I
#define timer_I		7
#endif

#endif /* MCAL_TIMER_TIMER_PRIVATE_H_ */
