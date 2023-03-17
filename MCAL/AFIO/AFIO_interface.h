/******************************************************************************
*  File name:		AFIO_interface.h
*  Date:			Mar 17, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef AFIO_INTERFACE_H
#define AFIO_INTERFACE_H

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

/*******************************************************************************
*                       	   		AFIO PORTS                 	               *
*******************************************************************************/
#define AFIO_u8_PORTA							0
#define AFIO_u8_PORTB							1
#define AFIO_u8_PORTC							2
#define AFIO_u8_PORTD							3
#define AFIO_u8_PORTE							4

/*******************************************************************************
*                       	   		AFIO EXTI LINE                 	               *
*******************************************************************************/
#define AFIO_u8_EXTI_LINE0						0
#define AFIO_u8_EXTI_LINE1						1
#define AFIO_u8_EXTI_LINE2						2
#define AFIO_u8_EXTI_LINE3						3
#define AFIO_u8_EXTI_LINE4						4
#define AFIO_u8_EXTI_LINE5						5
#define AFIO_u8_EXTI_LINE6						6
#define AFIO_u8_EXTI_LINE7						7
#define AFIO_u8_EXTI_LINE8						8
#define AFIO_u8_EXTI_LINE9						9
#define AFIO_u8_EXTI_LINE10						10
#define AFIO_u8_EXTI_LINE11						11
#define AFIO_u8_EXTI_LINE12						12
#define AFIO_u8_EXTI_LINE13						13
#define AFIO_u8_EXTI_LINE14						14
#define AFIO_u8_EXTI_LINE15						15

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		EXTI_u8SetInterruptStatus
* Description:			Function to enable or disable the required EXTI mask
* Parameters (in):    	The EXTI number
* 						EXTI state : Masked or Not Masked
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 AFIO_u8SetEXTIPortSource(u8 Copy_u8EXTINumber , u8 Copy_u8PortNumber);

#endif
