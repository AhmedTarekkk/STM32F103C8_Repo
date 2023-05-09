/******************************************************************************
*  File name:		SPI_program.c
*  Date:			May 8, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"

#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"

/*******************************************************************************
*                      Private Variables	                                   *
*******************************************************************************/
typedef void(*fptr_t)(void);
static fptr_t Global_pfArr[2] = {NULL,NULL};

SPI_RegDef_t * SPI_Astr[2] = {SPI1,SPI2};

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		SPI_u8Init
********************************************************************************/
u8 SPI_u8Init(u8 Copy_u8SPINumber, SPI_configStruct_t * Copy_PstrSPIConfig)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_u8SPINumber <= 1 && Copy_PstrSPIConfig != NULL)
	{
		/* Clear the control register and set the type at the same time */
		SPI_Astr[Copy_u8SPINumber]->CR1 = ((Copy_PstrSPIConfig->SPI_u8_MCU_TYPE & 0b1) << 2);
		if(Copy_PstrSPIConfig->SPI_u8_NSS_SETUP == SPI_u8_NSS_SW)
		{
			SET_BIT(SPI_Astr[Copy_u8SPINumber]->CR1,9); /* Software slave management enabled */
			SET_BIT(SPI_Astr[Copy_u8SPINumber]->CR1,8); /* NSS High */
		}
		else
		{
			CLR_BIT(SPI_Astr[Copy_u8SPINumber]->CR1,9); /* Software slave management disabled */
			CLR_BIT(SPI_Astr[Copy_u8SPINumber]->CR2,2);
			SPI_Astr[Copy_u8SPINumber]->CR2 |= ((Copy_PstrSPIConfig->SPI_u8_NSS_SETUP & 0b1) << 2);
		}
		SPI_Astr[Copy_u8SPINumber]->CR1 |= (Copy_PstrSPIConfig->SPI_u8_CLOCK_SETUP & 0b11);
		SPI_Astr[Copy_u8SPINumber]->CR1 |= ((Copy_PstrSPIConfig->SPI_u8_BAUD_RATE & 0b111) << 3);
		SPI_Astr[Copy_u8SPINumber]->CR1 |= ((Copy_PstrSPIConfig->SPI_u8_FRAME_FORMAT & 0b1) << 7);
		SPI_Astr[Copy_u8SPINumber]->CR1 |= ((Copy_PstrSPIConfig->SPI_u8_DATA_SIZE & 0b1) << 11);
		/* First bit indicates the receive is interrupt or polling */
		SPI_Astr[Copy_u8SPINumber]->CR2 |= ((Copy_PstrSPIConfig->SPI_u8_RECEIVE_METHOD & 0b1) << 6);
		/* Second and third bit indicates the DMA Configuration */
		SPI_Astr[Copy_u8SPINumber]->CR2 |= ((Copy_PstrSPIConfig->SPI_u8_RECEIVE_METHOD >> 1) & 0b11);
		SET_BIT(SPI_Astr[Copy_u8SPINumber]->CR1,6); /* Enable the peripheral */
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		SPI_u8SWSlaveSelect
********************************************************************************/
u8 SPI_u8SWSlaveSelect(u8 Copy_u8SPINumber, u8 Copy_SlaveState)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	/* It has to be slave or it will make unexpected behavior */
	if(Copy_u8SPINumber <= 1 && (GET_BIT(SPI_Astr[Copy_u8SPINumber]->CR1,2) == SPI_u8_SLAVE))
	{
		CLR_BIT(SPI_Astr[Copy_u8SPINumber]->CR1,8);
		SPI_Astr[Copy_u8SPINumber]->CR1 |= ((Copy_SlaveState & 0b1) << 8);
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		SPI_u8SendReceiveByte
********************************************************************************/
u8 SPI_u8SendReceiveByte(u8 Copy_u8SPINumber, u8 Copy_u8DataByte , u8 * Copy_pu8DataByte)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_u8SPINumber <= 1)
	{
		SPI_Astr[Copy_u8SPINumber]->DR = Copy_u8DataByte ;
		/* Wait until the SPI to complete the transmission and become not busy */
		while(GET_BIT(SPI_Astr[Copy_u8SPINumber]->SR,7) == 1);
		if(Copy_pu8DataByte != NULL)
		{
			* Copy_pu8DataByte = SPI_Astr[Copy_u8SPINumber]->DR ;
		}

	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		SPI_u8SendReceiveByte
********************************************************************************/
u8 SPI_u8SendReceive2Bytes(u8 Copy_u8SPINumber, u16 Copy_u16DataByte , u16 * Copy_pu16DataByte)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_u8SPINumber <= 1)
	{
		SPI_Astr[Copy_u8SPINumber]->DR = Copy_u16DataByte ;
		/* Wait until the SPI to complete the transmission and become not busy */
		while(GET_BIT(SPI_Astr[Copy_u8SPINumber]->SR,7) == 1);
		if(Copy_pu16DataByte != NULL)
		{
			* Copy_pu16DataByte = SPI_Astr[Copy_u8SPINumber]->DR ;
		}

	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		SPI_u8SendString
********************************************************************************/
u8 SPI_u8SendString(u8 Copy_u8SPINumber, u8* Copy_Pu8DataString)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_u8SPINumber <= 1)
	{
		u8 i;
		for(i = 0 ; Copy_Pu8DataString[i] != '\0' ; i++)
		{
			SPI_u8SendReceiveByte(Copy_u8SPINumber, Copy_Pu8DataString[i], NULL);
		}
		SPI_u8SendReceiveByte(Copy_u8SPINumber, Copy_Pu8DataString[i], NULL); /* To send the \0 */
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		SPI_u8ReceiveString
********************************************************************************/
u8 SPI_u8ReceiveString(u8 Copy_u8SPINumber, u8* Copy_Pu8DataString)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_u8SPINumber <= 1)
	{
		u8 i;
		do
		{
			/* Send Dummy data so we can receive the string */
			SPI_u8SendReceiveByte(Copy_u8SPINumber, SPI_u8_DUMMY , (Copy_Pu8DataString+i));
			i++;
		}while(Copy_Pu8DataString[i-1] != '\0');
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		SPI_u8SendString
********************************************************************************/
u8 SPI_u8SendStream(u8 Copy_u8SPINumber, u8* Copy_Pu8DataStream , u8 Copy_StreamSize)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_u8SPINumber <= 1)
	{
		for(u8 i = 0 ; i < Copy_StreamSize ; i++)
		{
			SPI_u8SendReceiveByte(Copy_u8SPINumber, Copy_Pu8DataStream[i], NULL);
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		SPI_u8ReceiveString
********************************************************************************/
u8 SPI_u8ReceiveStream(u8 Copy_u8SPINumber, u8* Copy_Pu8DataStream , u8 Copy_StreamSize)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_u8SPINumber <= 1)
	{
		for(u8 i = 0 ; i < Copy_StreamSize ; i++)
		{
			SPI_u8SendReceiveByte(Copy_u8SPINumber, SPI_u8_DUMMY, (Copy_Pu8DataStream+i));
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		SPI_u8DeInit
********************************************************************************/
u8 SPI_u8DeInit(u8 Copy_u8SPINumber)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_u8SPINumber <= 1)
	{
		while(GET_BIT(SPI_Astr[Copy_u8SPINumber]->SR,7) == 1);
		SPI_Astr[Copy_u8SPINumber]->CR2 = 0;
		SPI_Astr[Copy_u8SPINumber]->CR1 = 0;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		SPI_u8SetCallBack
********************************************************************************/
u8 SPI_u8SetCallBack(u8 Copy_u8SPINumber, void(*Copy_pfCallback)(void))
{
	u8 Local_ErrorState = STD_TYPES_OK;

	if(Copy_u8SPINumber <= 1 && Copy_pfCallback != NULL)
	{
		Global_pfArr[Copy_u8SPINumber] = Copy_pfCallback;
	}
	else
	{
		Local_ErrorState = STD_TYPES_NOK;
	}

	return Local_ErrorState;
}

/*******************************************************************************
*                       Interrupt Service Routines                            *
*******************************************************************************/
void SPI1_IRQHandler(void)
{
	if(Global_pfArr[0] != NULL)
	{
		Global_pfArr[0]();
	}
}

void SPI2_IRQHandler(void)
{
	if(Global_pfArr[1] != NULL)
	{
		Global_pfArr[1]();
	}
}
