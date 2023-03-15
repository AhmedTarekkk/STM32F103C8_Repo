/******************************************************************************
*  File name:		NVIC_interface.h
*  Date:			Mar 15, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

/*******************************************************************************
*                        		NVIC GROUPING                                  *
*******************************************************************************/
#define NVIC_u8_16GROUPS_0SUB	0b011
#define NVIC_u8_8GROUPS_2SUBS	0b100
#define NVIC_u8_4GROUPS_4SUBS	0b101
#define NVIC_u8_2GROUPS_8SUBS	0b110
#define NVIC_u8_0GROUP_16SUBS	0b111

/*******************************************************************************
*                        	NVIC INTERTUPT NUMBER                              *
*******************************************************************************/
#define NVIC_u8_WWDG							0
#define NVIC_u8_PVD								1
#define NVIC_u8_TAMPER							2
#define NVIC_u8_RTC								3
#define NVIC_u8_FLASH							4
#define NVIC_u8_RCC								5
#define NVIC_u8_EXTI0							6
#define NVIC_u8_EXTI1							7
#define NVIC_u8_EXTI2							8
#define NVIC_u8_EXTI3							9
#define NVIC_u8_EXTI4							10
#define NVIC_u8_DMA1_CHANNEL1					11
#define NVIC_u8_DMA1_CHANNEL2					12
#define NVIC_u8_DMA1_CHANNEL3					13
#define NVIC_u8_DMA1_CHANNEL4					14
#define NVIC_u8_DMA1_CHANNEL5					15
#define NVIC_u8_DMA1_CHANNEL6					16
#define NVIC_u8_DMA1_CHANNEL7					17
#define NVIC_u8_ADC1_2							18
#define NVIC_u8_CAN_TX							19
#define NVIC_u8_CAN_RX0							20
#define NVIC_u8_CAN_RX1							21
#define NVIC_u8_CAN_SCE							22
#define NVIC_u8_EXTI9_5							23
#define NVIC_u8_TIM1_BRK						24
#define NVIC_u8_TIM1_UP							25
#define NVIC_u8_TIM1_TRG_COM					26
#define NVIC_u8_TIM1_CC							27
#define NVIC_u8_TIM2							28
#define NVIC_u8_TIM3							29
#define NVIC_u8_TIM4							30
#define NVIC_u8_I2C1_EV							31
#define NVIC_u8_I2C1_ER							32
#define NVIC_u8_I2C2_EV							33
#define NVIC_u8_I2C2_ER							34
#define NVIC_u8_SPI1							35
#define NVIC_u8_SPI2							36
#define NVIC_u8_USART1							37
#define NVIC_u8_USART2							38
#define NVIC_u8_USART3							39
#define NVIC_u8_EXTI15_10						40
#define NVIC_u8_RTCALARM						41
#define NVIC_u8_USBWAKEUP						42

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		NVIC_u8EnableInterrupt
* Description:			Function to enable the required interrupt
* Parameters (in):    	void
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 NVIC_u8EnableInterrupt(u8 Copy_u8InterruptNumber);

/*******************************************************************************
* Function Name:		NVIC_u8DisableInterrupt
* Description:			Function to disable the required interrupt
* Parameters (in):    	The Required Interrupt
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 NVIC_u8DisableInterrupt(u8 Copy_u8InterruptNumber);

/*******************************************************************************
* Function Name:		NVIC_u8SetInterruptPending
* Description:			Function to pend the required interrupt
* Parameters (in):    	The Required Interrupt
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 NVIC_u8SetInterruptPending(u8 Copy_u8InterruptNumber);

/*******************************************************************************
* Function Name:		NVIC_u8SClearInterruptPending
* Description:			Function to clear the required interrupt pending
* Parameters (in):    	The Required Interrupt
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 NVIC_u8SClearInterruptPending(u8 Copy_u8InterruptNumber);

/*******************************************************************************
* Function Name:		NVIC_u8InterruptIsActive
* Description:			Function to init the system clock source
* Parameters (in):    	The Required Interrupt
* 						Pointer to function to save it the interrupt status active or not
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 NVIC_u8InterruptIsActive(u8 Copy_u8InterruptNumber, u8* Copy_pu8InterruptStatus);

/*******************************************************************************
* Function Name:		NVIC_u8SetGroupPriority
* Description:			Function to set the group priority for the required interrupt
* Parameters (in):    	void
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 NVIC_u8SetGroupPriority(u8 Copy_u8InterruptNumber,u8 Copy_u8GroupPriority);

/*******************************************************************************
* Function Name:		NVIC_u8GenerateSWInerrupt
* Description:			Function to generate interrupt with specific number with SW
* Parameters (in):    	void
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 NVIC_u8GenerateSWInerrupt(u8 Copy_u8InterruptNumber);

#endif
