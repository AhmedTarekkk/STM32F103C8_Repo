/******************************************************************************
*  File name:		stm32f103xx.h
*  Date:			Mar 5, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef STM32F103xx_H
#define STM32F103xx_H

/*******************************************************************************
*                      				RCC                     		           *
*******************************************************************************/

#define RCC_u32_BASE_ADDRESS						0x40021000

typedef struct
{	
	volatile u32 CR;
	volatile u32 CFGR;
	volatile u32 CIR;
	volatile u32 APB2RSTR;
	volatile u32 APB1RSTR;
	volatile u32 AHBENR;
	volatile u32 APB2ENR;
	volatile u32 APB1ENR;
	volatile u32 BDCR;		
	volatile u32 CSR;				
}RCC_RegDef_t;

#define RCC			((RCC_RegDef_t *)RCC_u32_BASE_ADDRESS)

#endif
