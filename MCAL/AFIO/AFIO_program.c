/******************************************************************************
*  File name:		AFIO_program.c
*  Date:			Mar 17, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"

#include "AFIO_interface.h"
#include "AFIO_private.h"
#include "AFIO_config.h"

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		AFIO_u8SetEXTIPortSource
********************************************************************************/

u8 AFIO_u8SetEXTIPortSource(u8 Copy_u8EXTINumber , u8 Copy_u8PortNumber)
{
	u8 LocalErrorState = STD_TYPES_NOK;

	if(Copy_u8EXTINumber <= 15)
	{
		LocalErrorState = STD_TYPES_OK;
		u8 Local_RegisterNumber = Copy_u8EXTINumber/4;
		u8 Local_ByteNumber = Copy_u8EXTINumber%4;

		AFIO->EXTICR[Local_RegisterNumber] &= ~(0b1111 << (4*Local_ByteNumber));
		AFIO->EXTICR[Local_RegisterNumber] |= (Copy_u8PortNumber << (4*Local_ByteNumber));
	}

	return LocalErrorState;
}

/*******************************************************************************
* Function Name:		AFIO_u8DisableJTAG
********************************************************************************/
u8 AFIO_u8DisableJTAG(void)
{
	u8 LocalErrorState = STD_TYPES_OK;

	CLR_BIT(AFIO->MAPR,26);
	SET_BIT(AFIO->MAPR,25);
	CLR_BIT(AFIO->MAPR,24);

	return LocalErrorState;
}

/*******************************************************************************
* Function Name:		AFIO_u8SetUARTConfiguration
********************************************************************************/
u8 AFIO_u8SetUARTConfiguration(u8 Copy_u8UARTNumber , u8 Copy_u8RemapValue)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	switch(Copy_u8UARTNumber)
	{
	case AFIO_u8_UART1:
		AFIO->MAPR &= ~(0b1 << 2);
		AFIO->MAPR |= ((Copy_u8RemapValue & 0b1) << 2) ;
		break;

	case AFIO_u8_UART2:
		AFIO->MAPR &= ~(0b1 << 3);
		AFIO->MAPR |= ((Copy_u8RemapValue & 0b1) << 3) ;
		break;

	case AFIO_u8_UART3:
		AFIO->MAPR &= ~(0b11 << 4);
		AFIO->MAPR |= ((Copy_u8RemapValue & 0b11) << 4) ;
		break;

	default:
		Local_u8ErrorState = STD_TYPES_NOK;
		break;
	}

	return Local_u8ErrorState;
}
