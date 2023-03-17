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
