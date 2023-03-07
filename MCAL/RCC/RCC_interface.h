/******************************************************************************
*  File name:		RCC_interface.h
*  Author:			Mar 5, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

/*******************************************************************************
*                        		AHB Peripherals                                *
*******************************************************************************/
#define	DMA1_RCC				0
#define	DMA2_RCC				1
#define	SRAM_RCC				2
#define	FLITF_RCC				4
#define	CRC_RCC					6
#define	FSMC_RCC				8

/*******************************************************************************
*                        		APB2 Peripherals                               *
*******************************************************************************/
#define	AFIO_RCC				(0  +32)
#define	GPIOA_RCC				(2  +32)
#define	GPIOB_RCC				(3  +32)
#define	GPIOC_RCC				(4  +32)
#define	GPIOD_RCC				(5  +32)
#define	GPIOE_RCC				(6  +32)
#define	GPIOF_RCC				(7  +32)
#define	GPIOG_RCC				(8  +32)
#define	ADC1_RCC				(9  +32)
#define	ADC2_RCC				(10 +32)
#define	TIM1_RCC				(11 +32)
#define	SPI1_RCC				(12 +32)
#define	TIM8_RCC				(13 +32)
#define	USART1_RCC				(14 +32)
#define	ADC3_RCC				(15 +32)
#define	TIM9_RCC				(19 +32)
#define	TIM10_RCC				(20 +32)
#define	TIM11_RCC				(21 +32)

/*******************************************************************************
*                        		APB1 Peripherals                               *
*******************************************************************************/
#define	TIM2_RCC				(0  +64)
#define	TIM3_RCC				(1  +64)
#define	TIM4_RCC				(2  +64)
#define	TIM5_RCC				(3  +64)
#define	TIM6_RCC				(4  +64)
#define	TIM7_RCC				(5  +64)
#define	TIM12_RCC				(6  +64)
#define	TIM13_RCC				(7  +64)
#define	TIM14_RCC				(8  +64)
#define	WWD_RCC					(11 +64)
#define	SPI2_RCC				(14 +64)
#define	SPI3_RCC				(15 +64)
#define	USART2_RCC				(17 +64)
#define	USART3_RCC				(18 +64)
#define	USART4_RCC				(19 +64)
#define	USART5_RCC				(20 +64)
#define	I2C1_RCC				(21 +64)
#define	I2C2_RCC				(22 +64)
#define	USB_RCC					(23 +64)
#define	CAN_RCC					(25 +64)
#define	BKP_RCC					(27 +64)
#define	PWR_RCC					(28 +64)
#define	DAC_RCC					(29 +64)

/*******************************************************************************
*                        		Peripherals State                              *
*******************************************************************************/
#define Disable		0
#define Enable		1

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		RCC_u8InitSysClk
* Description:			Function to init the system clock source
* Parameters (in):    	void
* Parameters (out):   	OK or Error
* Return value:      	DHT11_response
********************************************************************************/
u8 RCC_u8InitSysClk	(void);

/*******************************************************************************
* Function Name:		RCC_u8EnablePeripheralClk
* Description:			Function to enable or disable clock for specific periphral
* Parameters (in):    	The required peripheral and its bus
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 RCC_u8EnableDisablPeripheralClk	(u8 Copy_u8PeripheralId ,u8 Copy_u8State);

#endif
