/******************************************************************************
*  File name:		DMA_program.c
*  Date:			Mar 18, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"

#include "DMA_interface.h"
#include "DMA_private.h"
#include "DMA_config.h"

/*******************************************************************************
*                      Private Variables	                                   *
*******************************************************************************/
typedef void(*fptr_t)(void);
static fptr_t Global_pfArr[7] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		DMA_u8ChannelInit
********************************************************************************/
u8 DMA_u8ChannelInit	(DMA_configStruct_t * Copy_PstrDMAChannelConfig)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	switch(Copy_PstrDMAChannelConfig->ChannelNumber)
	{
	case DMA_u8_CHANNEL1:
		DMA->CCR1 = 0; /* Reset the whole register  */
		DMA->CCR1 |= ((Copy_PstrDMAChannelConfig->ChannelPriority & 0b11) << 12 );
		DMA->CCR1 |= ((Copy_PstrDMAChannelConfig->DataSize & 0b11) << 10 );
		DMA->CCR1 |= ((Copy_PstrDMAChannelConfig->DataSize & 0b11) << 8  );
		DMA->CCR1 |= ((Copy_PstrDMAChannelConfig->IncrementMode & 0b11) << 6 );
		DMA->CCR1 |= ((Copy_PstrDMAChannelConfig->EnableTCInt & 0b1) << 1);
		if(Copy_PstrDMAChannelConfig->DataTransferType == DMA_u8_MEM_TO_MEM)
		{
			SET_BIT(DMA->CCR1,14);
			SET_BIT(DMA->CCR1,4); /* Memory is the source Peripheral is the destination */
		}
		else
		{
			DMA->CCR1 |= ((Copy_PstrDMAChannelConfig->DataTransferType & 0b1) << 4 );
		}
		break;

	case DMA_u8_CHANNEL2:
		DMA->CCR2 = 0; /* Reset the whole register  */
		DMA->CCR2 |= ((Copy_PstrDMAChannelConfig->ChannelPriority & 0b11) << 12 );
		DMA->CCR2 |= ((Copy_PstrDMAChannelConfig->DataSize & 0b11) << 10 );
		DMA->CCR2 |= ((Copy_PstrDMAChannelConfig->DataSize & 0b11) << 8  );
		DMA->CCR2 |= ((Copy_PstrDMAChannelConfig->IncrementMode & 0b11) << 6 );
		DMA->CCR2 |= ((Copy_PstrDMAChannelConfig->EnableTCInt & 0b1) << 1);
		if(Copy_PstrDMAChannelConfig->DataTransferType == DMA_u8_MEM_TO_MEM)
		{
			SET_BIT(DMA->CCR2,14);
			SET_BIT(DMA->CCR2,4); /* Memory is the source Peripheral is the destination */
		}
		else
		{
			DMA->CCR2 |= ((Copy_PstrDMAChannelConfig->DataTransferType & 0b1) << 4 );
		}
		break;

	case DMA_u8_CHANNEL3:
		DMA->CCR3 = 0; /* Reset the whole register  */
		DMA->CCR3 |= ((Copy_PstrDMAChannelConfig->ChannelPriority & 0b11) << 12 );
		DMA->CCR3 |= ((Copy_PstrDMAChannelConfig->DataSize & 0b11) << 10 );
		DMA->CCR3 |= ((Copy_PstrDMAChannelConfig->DataSize & 0b11) << 8  );
		DMA->CCR3 |= ((Copy_PstrDMAChannelConfig->IncrementMode & 0b11) << 6 );
		DMA->CCR3 |= ((Copy_PstrDMAChannelConfig->EnableTCInt & 0b1) << 1);
		if(Copy_PstrDMAChannelConfig->DataTransferType == DMA_u8_MEM_TO_MEM)
		{
			SET_BIT(DMA->CCR3,14);
			SET_BIT(DMA->CCR3,4); /* Memory is the source Peripheral is the destination */
		}
		else
		{
			DMA->CCR3 |= ((Copy_PstrDMAChannelConfig->DataTransferType & 0b1) << 4 );
		}
		break;

	case DMA_u8_CHANNEL4:
		DMA->CCR4 = 0; /* Reset the whole register  */
		DMA->CCR4 |= ((Copy_PstrDMAChannelConfig->ChannelPriority & 0b11) << 12 );
		DMA->CCR4 |= ((Copy_PstrDMAChannelConfig->DataSize & 0b11) << 10 );
		DMA->CCR4 |= ((Copy_PstrDMAChannelConfig->DataSize & 0b11) << 8  );
		DMA->CCR4 |= ((Copy_PstrDMAChannelConfig->IncrementMode & 0b11) << 6 );
		DMA->CCR4 |= ((Copy_PstrDMAChannelConfig->EnableTCInt & 0b1) << 1);
		if(Copy_PstrDMAChannelConfig->DataTransferType == DMA_u8_MEM_TO_MEM)
		{
			SET_BIT(DMA->CCR4,14);
			SET_BIT(DMA->CCR4,4); /* Memory is the source Peripheral is the destination */
		}
		else
		{
			DMA->CCR4 |= ((Copy_PstrDMAChannelConfig->DataTransferType & 0b1) << 4 );
		}
		break;

	case DMA_u8_CHANNEL5:
		DMA->CCR5 = 0; /* Reset the whole register  */
		DMA->CCR5 |= ((Copy_PstrDMAChannelConfig->ChannelPriority & 0b11) << 12 );
		DMA->CCR5 |= ((Copy_PstrDMAChannelConfig->DataSize & 0b11) << 10 );
		DMA->CCR5 |= ((Copy_PstrDMAChannelConfig->DataSize & 0b11) << 8  );
		DMA->CCR5 |= ((Copy_PstrDMAChannelConfig->IncrementMode & 0b11) << 6 );
		DMA->CCR5 |= ((Copy_PstrDMAChannelConfig->EnableTCInt & 0b1) << 1);
		if(Copy_PstrDMAChannelConfig->DataTransferType == DMA_u8_MEM_TO_MEM)
		{
			SET_BIT(DMA->CCR5,14);
			SET_BIT(DMA->CCR5,4); /* Memory is the source Peripheral is the destination */
		}
		else
		{
			DMA->CCR5 |= ((Copy_PstrDMAChannelConfig->DataTransferType & 0b1) << 4 );
		}
		break;

	case DMA_u8_CHANNEL6:
		DMA->CCR6 = 0; /* Reset the whole register  */
		DMA->CCR6 |= ((Copy_PstrDMAChannelConfig->ChannelPriority & 0b11) << 12 );
		DMA->CCR6 |= ((Copy_PstrDMAChannelConfig->DataSize & 0b11) << 10 );
		DMA->CCR6 |= ((Copy_PstrDMAChannelConfig->DataSize & 0b11) << 8  );
		DMA->CCR6 |= ((Copy_PstrDMAChannelConfig->IncrementMode & 0b11) << 6 );
		DMA->CCR6 |= ((Copy_PstrDMAChannelConfig->EnableTCInt & 0b1) << 1);
		if(Copy_PstrDMAChannelConfig->DataTransferType == DMA_u8_MEM_TO_MEM)
		{
			SET_BIT(DMA->CCR6,14);
			SET_BIT(DMA->CCR6,4); /* Memory is the source Peripheral is the destination */
		}
		else
		{
			DMA->CCR6 |= ((Copy_PstrDMAChannelConfig->DataTransferType & 0b1) << 4 );
		}
		break;

	case DMA_u8_CHANNEL7:
		DMA->CCR7 = 0; /* Reset the whole register  */
		DMA->CCR7 |= ((Copy_PstrDMAChannelConfig->ChannelPriority & 0b11) << 12 );
		DMA->CCR7 |= ((Copy_PstrDMAChannelConfig->DataSize & 0b11) << 10 );
		DMA->CCR7 |= ((Copy_PstrDMAChannelConfig->DataSize & 0b11) << 8  );
		DMA->CCR7 |= ((Copy_PstrDMAChannelConfig->IncrementMode & 0b11) << 6 );
		DMA->CCR7 |= ((Copy_PstrDMAChannelConfig->EnableTCInt & 0b1) << 1);
		if(Copy_PstrDMAChannelConfig->DataTransferType == DMA_u8_MEM_TO_MEM)
		{
			SET_BIT(DMA->CCR7,14);
			SET_BIT(DMA->CCR7,4); /* Memory is the source Peripheral is the destination */
		}
		else
		{
			DMA->CCR7 |= ((Copy_PstrDMAChannelConfig->DataTransferType & 0b1) << 4 );
		}
		break;

	default:
		Local_u8ErrorState = STD_TYPES_NOK;
		break;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		DMA_u8ChannelTransfer
********************************************************************************/
u8 DMA_u8ChannelTransfer	(u8 Copy_u8ChannelNumber, u32 Copy_u32MemAddress,u32 Copy_u32PerAddress,u32 Copy_u32NumberOfTransfers)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	switch(Copy_u8ChannelNumber)
	{
	case DMA_u8_CHANNEL1:
		DMA->CNDTR1 = (Copy_u32NumberOfTransfers & 0xFFFF);
		DMA->CMAR1 = Copy_u32MemAddress;
		DMA->CPAR1 = Copy_u32PerAddress;
		SET_BIT(DMA->CCR1,0); /* Enable The Channel */
		break;

	case DMA_u8_CHANNEL2:
		DMA->CNDTR2 = (Copy_u32NumberOfTransfers & 0xFFFF);
		DMA->CMAR2 = Copy_u32MemAddress;
		DMA->CPAR2 = Copy_u32PerAddress;
		SET_BIT(DMA->CCR2,0); /* Enable The Channel */
		break;

	case DMA_u8_CHANNEL3:
		DMA->CNDTR3 = (Copy_u32NumberOfTransfers & 0xFFFF);
		DMA->CMAR3 = Copy_u32MemAddress;
		DMA->CPAR3 = Copy_u32PerAddress;
		SET_BIT(DMA->CCR3,0); /* Enable The Channel */
		break;

	case DMA_u8_CHANNEL4:
		DMA->CNDTR4 = (Copy_u32NumberOfTransfers & 0xFFFF);
		DMA->CMAR4 = Copy_u32MemAddress;
		DMA->CPAR4 = Copy_u32PerAddress;
		SET_BIT(DMA->CCR4,0); /* Enable The Channel */
		break;

	case DMA_u8_CHANNEL5:
		DMA->CNDTR5 = (Copy_u32NumberOfTransfers & 0xFFFF);
		DMA->CMAR5 = Copy_u32MemAddress;
		DMA->CPAR5 = Copy_u32PerAddress;
		SET_BIT(DMA->CCR5,0); /* Enable The Channel */
		break;

	case DMA_u8_CHANNEL6:
		DMA->CNDTR6 = (Copy_u32NumberOfTransfers & 0xFFFF);
		DMA->CMAR6 = Copy_u32MemAddress;
		DMA->CPAR6 = Copy_u32PerAddress;
		SET_BIT(DMA->CCR6,0); /* Enable The Channel */
		break;

	case DMA_u8_CHANNEL7:
		DMA->CNDTR7 = (Copy_u32NumberOfTransfers & 0xFFFF);
		DMA->CMAR7 = Copy_u32MemAddress;
		DMA->CPAR7 = Copy_u32PerAddress;
		SET_BIT(DMA->CCR7,0); /* Enable The Channel */
		break;

	default:
		Local_u8ErrorState = STD_TYPES_NOK;
		break;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		DMA_u8ChannelTransfer_BusyWait
********************************************************************************/
u8 DMA_u8ChannelTransfer_BusyWait	(u8 Copy_u8ChannelNumber, u32 Copy_u32MemAddress,u32 Copy_u32PerAddress,u32 Copy_u32NumberOfTransfers)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	switch(Copy_u8ChannelNumber)
	{
	case DMA_u8_CHANNEL1:
		DMA->CNDTR1 = (Copy_u32NumberOfTransfers & 0xFFFF);
		DMA->CMAR1 = Copy_u32MemAddress;
		DMA->CPAR1 = Copy_u32PerAddress;
		SET_BIT(DMA->CCR1,0); /* Enable The Channel */
		while(GET_BIT(DMA->ISR,1) == 0); /* Wait until Transmission Complete Flag = 1 */
		SET_BIT(DMA->IFCR,1); /* Clear The interrupt flag */
		break;

	case DMA_u8_CHANNEL2:
		DMA->CNDTR2 = (Copy_u32NumberOfTransfers & 0xFFFF);
		DMA->CMAR2 = Copy_u32MemAddress;
		DMA->CPAR2 = Copy_u32PerAddress;
		SET_BIT(DMA->CCR2,0); /* Enable The Channel */
		while(GET_BIT(DMA->ISR,5) == 0); /* Wait until Transmission Complete Flag = 1 */
		SET_BIT(DMA->IFCR,5); /* Clear The interrupt flag */
		break;

	case DMA_u8_CHANNEL3:
		DMA->CNDTR3 = (Copy_u32NumberOfTransfers & 0xFFFF);
		DMA->CMAR3 = Copy_u32MemAddress;
		DMA->CPAR3 = Copy_u32PerAddress;
		SET_BIT(DMA->CCR3,0); /* Enable The Channel */
		while(GET_BIT(DMA->ISR,9) == 0); /* Wait until Transmission Complete Flag = 1 */
		SET_BIT(DMA->IFCR,9); /* Clear The interrupt flag */
		break;

	case DMA_u8_CHANNEL4:
		DMA->CNDTR4 = (Copy_u32NumberOfTransfers & 0xFFFF);
		DMA->CMAR4 = Copy_u32MemAddress;
		DMA->CPAR4 = Copy_u32PerAddress;
		SET_BIT(DMA->CCR4,0); /* Enable The Channel */
		while(GET_BIT(DMA->ISR,13) == 0); /* Wait until Transmission Complete Flag = 1 */
		SET_BIT(DMA->IFCR,13); /* Clear The interrupt flag */
		break;

	case DMA_u8_CHANNEL5:
		DMA->CNDTR5 = (Copy_u32NumberOfTransfers & 0xFFFF);
		DMA->CMAR5 = Copy_u32MemAddress;
		DMA->CPAR5 = Copy_u32PerAddress;
		SET_BIT(DMA->CCR5,0); /* Enable The Channel */
		while(GET_BIT(DMA->ISR,17) == 0); /* Wait until Transmission Complete Flag = 1 */
		SET_BIT(DMA->IFCR,17); /* Clear The interrupt flag */
		break;

	case DMA_u8_CHANNEL6:
		DMA->CNDTR6 = (Copy_u32NumberOfTransfers & 0xFFFF);
		DMA->CMAR6 = Copy_u32MemAddress;
		DMA->CPAR6 = Copy_u32PerAddress;
		SET_BIT(DMA->CCR6,0); /* Enable The Channel */
		while(GET_BIT(DMA->ISR,21) == 0); /* Wait until Transmission Complete Flag = 1 */
		SET_BIT(DMA->IFCR,21); /* Clear The interrupt flag */
		break;

	case DMA_u8_CHANNEL7:
		DMA->CNDTR7 = (Copy_u32NumberOfTransfers & 0xFFFF);
		DMA->CMAR7 = Copy_u32MemAddress;
		DMA->CPAR7 = Copy_u32PerAddress;
		SET_BIT(DMA->CCR7,0); /* Enable The Channel */
		while(GET_BIT(DMA->ISR,25) == 0); /* Wait until Transmission Complete Flag = 1 */
		SET_BIT(DMA->IFCR,25); /* Clear The interrupt flag */
		break;

	default:
		Local_u8ErrorState = STD_TYPES_NOK;
		break;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		DMA_u8CheckIfErrorOccurred
********************************************************************************/
u8 DMA_u8CheckIfErrorOccurred	(u8 Copy_u8ChannelNumber, u8 * Copy_Pu8ErrorState)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_Pu8ErrorState != NULL)
	{
		switch(Copy_u8ChannelNumber)
		{
		case DMA_u8_CHANNEL1:
			*Copy_Pu8ErrorState = GET_BIT(DMA->ISR,3); /* If error occurred Write 1 in the variable */
			SET_BIT(DMA->IFCR,3); /* Clear the flag so we can check it again later */
			break;

		case DMA_u8_CHANNEL2:
			*Copy_Pu8ErrorState = GET_BIT(DMA->ISR,7); /* If error occurred Write 1 in the variable */
			SET_BIT(DMA->IFCR,7); /* Clear the flag so we can check it again later */
			break;

		case DMA_u8_CHANNEL3:
			*Copy_Pu8ErrorState = GET_BIT(DMA->ISR,11); /* If error occurred Write 1 in the variable */
			SET_BIT(DMA->IFCR,11); /* Clear the flag so we can check it again later */
			break;

		case DMA_u8_CHANNEL4:
			*Copy_Pu8ErrorState = GET_BIT(DMA->ISR,15); /* If error occurred Write 1 in the variable */
			SET_BIT(DMA->IFCR,15); /* Clear the flag so we can check it again later */
			break;

		case DMA_u8_CHANNEL5:
			*Copy_Pu8ErrorState = GET_BIT(DMA->ISR,19); /* If error occurred Write 1 in the variable */
			SET_BIT(DMA->ISR,19); /* Clear the flag so we can check it again later */
			break;

		case DMA_u8_CHANNEL6:
			*Copy_Pu8ErrorState = GET_BIT(DMA->ISR,23); /* If error occurred Write 1 in the variable */
			SET_BIT(DMA->ISR,23); /* Clear the flag so we can check it again later */
			break;

		case DMA_u8_CHANNEL7:
			*Copy_Pu8ErrorState = GET_BIT(DMA->ISR,27); /* If error occurred Write 1 in the variable */
			SET_BIT(DMA->ISR,27); /* Clear the flag so we can check it again later */
			break;

		default:
			Local_u8ErrorState = STD_TYPES_NOK;
			break;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		DMA_u8SetCallBack
********************************************************************************/
u8 DMA_u8SetCallBack(u8 Copy_u8ChannelNumber, void(*Copy_pfCallback)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_pfCallback != NULL && Copy_u8ChannelNumber <= DMA_u8_CHANNEL7)
	{
		Global_pfArr[Copy_u8ChannelNumber-1] = Copy_pfCallback;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
*                       Interrupt Service Routines                            *
*******************************************************************************/
void DMA1_Channel1_IRQHandler(void)
{
	SET_BIT(DMA->IFCR,1); /* Clear The TC Flag */
	if(Global_pfArr[0] != NULL)
	{
		Global_pfArr[0]();
	}
	else
	{
		/* Do Nothing */
	}
}

void DMA1_Channel2_IRQHandler(void)
{
	SET_BIT(DMA->IFCR,5); /* Clear The TC Flag */
	if(Global_pfArr[1] != NULL)
	{
		Global_pfArr[1]();
	}
	else
	{
		/* Do Nothing */
	}
}

void DMA1_Channel3_IRQHandler(void)
{
	SET_BIT(DMA->IFCR,9); /* Clear The TC Flag */
	if(Global_pfArr[2] != NULL)
	{
		Global_pfArr[2]();
	}
	else
	{
		/* Do Nothing */
	}
}

void DMA1_Channel4_IRQHandler(void)
{
	SET_BIT(DMA->IFCR,13); /* Clear The TC Flag */
	if(Global_pfArr[3] != NULL)
	{
		Global_pfArr[3]();
	}
	else
	{
		/* Do Nothing */
	}
}

void DMA1_Channel5_IRQHandler(void)
{
	SET_BIT(DMA->IFCR,17); /* Clear The TC Flag */
	if(Global_pfArr[4] != NULL)
	{
		Global_pfArr[4]();
	}
	else
	{
		/* Do Nothing */
	}
}

void DMA1_Channel6_IRQHandler(void)
{
	SET_BIT(DMA->IFCR,21); /* Clear The TC Flag */
	if(Global_pfArr[5] != NULL)
	{
		Global_pfArr[5]();
	}
	else
	{
		/* Do Nothing */
	}
}

void DMA1_Channel7_IRQHandler(void)
{
	SET_BIT(DMA->IFCR,25); /* Clear The TC Flag */
	if(Global_pfArr[6] != NULL)
	{
		Global_pfArr[6]();
	}
	else
	{
		/* Do Nothing */
	}
}
