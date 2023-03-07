/******************************************************************************
*  File name:		RCC_config.h
*  Date:			Mar 5, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/*******************************************************************************
*                      Configure the system clock
*                      1- RCC_u8_HSI
*                      2- RCC_u8_HSE
*                      3- RCC_u8_PLL
*******************************************************************************/
#define RCC_u8_CLK_SYS			RCC_u8_HSI

/*******************************************************************************
*                      Configure the PLL clock source
*                       1- RCC_u8_PLL_HSI_DIVIDED_BY_2
*                       2- RCC_u8_PLL_HSE
*                       3- RCC_u8_PLL_HSE_DIVIDED_BY_2
*
*                      Configure the HSE clock source
*                       1-  RCC_u8_PLL_MULTIPLY_BY_2
*                       2-  RCC_u8_PLL_MULTIPLY_BY_3
*                       3-  RCC_u8_PLL_MULTIPLY_BY_4
*						4-  RCC_u8_PLL_MULTIPLY_BY_5
*						5-  RCC_u8_PLL_MULTIPLY_BY_6
*						6-  RCC_u8_PLL_MULTIPLY_BY_7
*						7-  RCC_u8_PLL_MULTIPLY_BY_8
*						8-  RCC_u8_PLL_MULTIPLY_BY_9
*						9-  RCC_u8_PLL_MULTIPLY_BY_10
*						10- RCC_u8_PLL_MULTIPLY_BY_11
*						11- RCC_u8_PLL_MULTIPLY_BY_12
*						12- RCC_u8_PLL_MULTIPLY_BY_13
*						13- RCC_u8_PLL_MULTIPLY_BY_14
*						14- RCC_u8_PLL_MULTIPLY_BY_15
*						15- RCC_u8_PLL_MULTIPLY_BY_16
*******************************************************************************/
#if (RCC_u8_CLK_SYS == RCC_u8_PLL)
	#define RCC_u8_PLL_SOURCE			RCC_u8_PLL_HSI_DIVIDED_BY_2
	#define RCC_u8_PLL_MULTIPLIER		RCC_u8_PLL_MULTIPLY_BY_2
#endif

/*******************************************************************************
*                      Configure the HSE clock source
*                       1- RCC_u8_HSE_NOT_BYPASS
*                       2- RCC_u8_HSE_BYPASS
*******************************************************************************/
#if (RCC_u8_CLK_SYS == RCC_u8_HSE)

	#define RCC_u8_HSE_TYPE			RCC_u8_HSE_NOT_BYPASS

#endif

#endif
