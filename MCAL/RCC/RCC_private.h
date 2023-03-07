/******************************************************************************
*  File name:		RCC_private.h
*  Author:			Mar 5, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

/*******************************************************************************
*                        		Clock Source	                               *
*******************************************************************************/
#define RCC_u8_HSI	1
#define RCC_u8_HSE	2
#define RCC_u8_PLL	3

/*******************************************************************************
*                        		PLL Clock Source	                           *
*******************************************************************************/
#define RCC_u8_PLL_HSI_DIVIDED_BY_2			1
#define RCC_u8_PLL_HSE						2
#define RCC_u8_PLL_HSE_DIVIDED_BY_2			3

/*******************************************************************************
*                        		PLL Clock Multiplier	                       *
*******************************************************************************/
#define RCC_u8_PLL_MULTIPLY_BY_2 			0b0000
#define RCC_u8_PLL_MULTIPLY_BY_3 			0b0001
#define RCC_u8_PLL_MULTIPLY_BY_4 			0b0010
#define RCC_u8_PLL_MULTIPLY_BY_5 			0b0011
#define RCC_u8_PLL_MULTIPLY_BY_6 			0b0100
#define RCC_u8_PLL_MULTIPLY_BY_7 			0b0101
#define RCC_u8_PLL_MULTIPLY_BY_8 			0b0110
#define RCC_u8_PLL_MULTIPLY_BY_9 			0b0111
#define RCC_u8_PLL_MULTIPLY_BY_10			0b1000
#define RCC_u8_PLL_MULTIPLY_BY_11			0b1001
#define RCC_u8_PLL_MULTIPLY_BY_12			0b1010
#define RCC_u8_PLL_MULTIPLY_BY_13			0b1011
#define RCC_u8_PLL_MULTIPLY_BY_14			0b1100
#define RCC_u8_PLL_MULTIPLY_BY_15			0b1101
#define RCC_u8_PLL_MULTIPLY_BY_16			0b1110
/*******************************************************************************
*                        		HSE Clock Source	                           *
*******************************************************************************/
#define RCC_u8_HSE_NOT_BYPASS					1
#define RCC_u8_HSE_BYPASS						2

#endif
