/*
 * assignment.h
 *
 *  Created on: 27. 9. 2020
 *      Author: Stancoj
 */

#ifndef ASSIGNMENT_H_
#define ASSIGNMENT_H_

/**
 * 		This header file provides macros to the MCU's registers required for this assignment.
 * 		Your task is to provide their actual implementation so you can use them in application in "main.c"
 * 		and make your "LED blink" application code readable and great again!
 */

/* General purpose input output port A macros */
//GPIOA peripheral base address
#define	GPIOA_BASE_ADDR	0x4800 0000		/* Add GPIO A peripheral base address here. */
//MODER register
#define	GPIOA_MODER_REG			/* Add moder register address here. */
//OTYPER register
#define	GPIOA_OTYPER_REG		/* Add otyper register address here. */
//OSPEEDER register
#define GPIOA_OSPEEDER_REG		/* Add ospeeder register address here. */
//PUPDR register
#define GPIOA_PUPDR_REG			/* Add pupdr register address here. */
//IDR register
#define GPIOA_IDR_REG			/* Add idr register address here. */
//ODR register
#define GPIOA_ODR_REG			/* Add odr register address here. */
//BSRR register
#define GPIOA_BSRR_REG			/* Add bsrr register address here. */
//BRR register
#define GPIOA_BRR_REG			/* Add brr register address here. */

/*Reset clock control register macros */
//RCC base address
#define	RCC_BASE_ADDR			/* Add rcc register address here. */
//AHBEN register
#define	RCC_AHBENR_REG			/* Add ahben register address here. */

/* LED and button macros */
#define LED_ON					*((volatile uint32_t *)((uint32_t)(0x48000000 + 0x18U))) |= (1 << 4)   	//GPIOB pin 3
#define LED_OFF					*((volatile uint32_t *)((uint32_t)0x48000000 + 0x28U)) |= (1 << 4);		//GPIOB pin 3


#define BUTTON_GET_STATE		(*((uint32_t*) (0x48000000 + 0x10U)) & (1 << 3))


#endif /* ASSIGNMENT_H_ */
