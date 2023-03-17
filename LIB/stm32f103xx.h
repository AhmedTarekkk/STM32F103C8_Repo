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

#define RCC						((RCC_RegDef_t *)RCC_u32_BASE_ADDRESS)

/*******************************************************************************
*                      				GPIO                     		           *
*******************************************************************************/

#define GPIOA_u32_BASE_ADDRESS						0x40010800U
#define GPIOB_u32_BASE_ADDRESS						0x40010C00U
#define GPIOC_u32_BASE_ADDRESS						0x40011000U
#define GPIOD_u32_BASE_ADDRESS						0x40011400U
#define GPIOE_u32_BASE_ADDRESS						0x40011800U

typedef struct
{
	volatile u32 CRL;
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCKR;
}GPIO_RegDef_t;

#define GPIOA					((GPIO_RegDef_t *)GPIOA_u32_BASE_ADDRESS)
#define GPIOB					((GPIO_RegDef_t *)GPIOB_u32_BASE_ADDRESS)
#define GPIOC					((GPIO_RegDef_t *)GPIOC_u32_BASE_ADDRESS)
#define GPIOD					((GPIO_RegDef_t *)GPIOD_u32_BASE_ADDRESS)
#define GPIOE					((GPIO_RegDef_t *)GPIOE_u32_BASE_ADDRESS)

/*******************************************************************************
*                      				SYSTICK                    		           *
*******************************************************************************/

#define STK_u32_BASE_ADDRESS						0xE000E010U

typedef struct
{
	volatile u32 CTRL;
	volatile u32 LOAD;
	volatile u32 VAL;
	volatile u32 CALIB;
}STK_RegDef_t;

#define STK						((STK_RegDef_t *)STK_u32_BASE_ADDRESS)

/*******************************************************************************
*                      				NVIC                    		           *
*******************************************************************************/

#define NVIC_u32_BASE_ADDRESS						0xE000E100U

typedef struct
{
	volatile u32 ISER[2];
	volatile u32 RESERVED1[30];
	volatile u32 ICER[2];
	volatile u32 RESERVED2[30];
	volatile u32 ISPR[2];
	volatile u32 RESERVED3[30];
	volatile u32 ICPR[2];
	volatile u32 RESERVED4[30];
	volatile u32 IABR[2];
	volatile u32 RESERVED5[62];
	volatile u32 IPR[11]; /* Can handle up to 43 interrupt So IPR10 -> 10*4+3 = 43 */
	volatile u32 RESERVED6[693];
	volatile u32 STIR;
}NVIC_RegDef_t;

#define NVIC					((NVIC_RegDef_t *)NVIC_u32_BASE_ADDRESS)
#define SCB_AIRCR				(*(volatile u32*)(0xE000ED0CU))

/*******************************************************************************
*                      				EXTI                    		           *
*******************************************************************************/

#define EXTI_u32_BASE_ADDRESS						0x40010400U

typedef struct
{
	volatile u32 IMR;
	volatile u32 EMR;
	volatile u32 RTSR;
	volatile u32 FTSR;
	volatile u32 SWIER;
	volatile u32 PR;
}EXTI_RegDef_t;

#define EXTI						((EXTI_RegDef_t*)EXTI_u32_BASE_ADDRESS)

#endif
