/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "assignment.h"
#include <stdint.h>

typedef enum _EDGE_TYPE { NONE = 0, RISING, FALLING} EDGE_TYPE;



EDGE_TYPE edge_detect(uint8_t, uint8_t);

int main(void)
{
	/*
	 * DO NOT WRITE TO THE WHOLE REGISTER!!!
	 *
	 * Write to bits, that are meant for change.
	 */

	/*PIN A3 config */
	*((volatile uint32_t *) (uint32_t)(0x40021000 + 0x00000014U)) |= (uint32_t)(1 << 17);	//clock for port A
	*((volatile uint32_t *)((uint32_t)0x48000000)) &= ~(uint32_t)(0b11 << 6);	// reset PIN A MODER3 - input
	// MODER A3  - 00
	*((volatile uint32_t *)((uint32_t)(0x48000000 + 0x0CU))) |= (0b1 << 6);		//pin A3 pullup
	*((volatile uint32_t *)((uint32_t)(0x48000000 + 0x0CU))) &= ~(0b1 << 7);    //bits [7,6] = 01


	/*Enables clock for GPIO port B*/
	*((volatile uint32_t *) (uint32_t)(0x40021000 + 0x00000014U)) |= (uint32_t)(1 << 18);	//enable clock for port B
	/*GPIOB pin 3 and 6 setup*/
	/*GPIO MODER register*/
	//Set mode for pin 3
	*((volatile uint32_t *)((uint32_t)0x48000400)) &= ~(uint32_t)(0x3 << 6);	//PORT B MODER - reset bits 6+7
	*((volatile uint32_t *)((uint32_t)0x48000400)) |= (uint32_t)(1 << 6);		// set bit 6  - output mode 01
	// MODER B6  - 01


	/*GPIO OTYPER register*/
	*((volatile uint32_t *)((uint32_t)(0x48000400 + 0x04U))) &= ~(1 << 3);	// pin B3 push pull mode
	/*GPIO OSPEEDR register*/
	//Set Low speed for GPIOB pin 3
	*((volatile uint32_t *)((uint32_t)(0x48000400 + 0x08U))) &= ~(0x3 << 6);	//pin B3 low speed mode 00
	//Set no pull for GPIOB pin 3
	*((volatile uint32_t *)((uint32_t)(0x48000400 + 0x0CU))) &= ~(0x3 << 6);	//pin B3 none

	EDGE_TYPE state = 0;
	uint8_t ledState = 0;

	while (1)
	{
		//GPIO IDR, read input from pin 6
		state = edge_detect((*((volatile uint32_t *)((uint32_t)(0x48000000 + 0x10U))) & (1 << 3)), 30);

		if(state == RISING) {
			ledState = !ledState;
		}
		if(ledState)
			LED_ON;
		else
			LED_OFF;

	}

}
/* USER CODE BEGIN */


EDGE_TYPE edge_detect(uint8_t state, uint8_t samples) {
	static int16_t counter = 0;
	if (!state && counter > 0)
		counter = 0;	//low and was high
	if (state && counter < 0)
		counter = 0;	//high and was low

	if (counter == samples - 1) {
		++counter;
		return RISING;
	}
	else if (counter == -samples + 1) {
		--counter;
		return FALLING;
	}
	else if (counter >= samples || counter <= -samples)
		return NONE;

	if (state)
		++counter;
	else
		--counter;
	return NONE;
}


/* USER CODE END */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
