/******************************************************************************
*  File name:		GPIO_program.c
*  Date:			Mar 8, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"

/*******************************************************************************
*                      Private Variables	                                   *
*******************************************************************************/
static GPIO_RegDef_t * GPIO_Astr[7] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG};

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		GPIO_u8SetPinMode
********************************************************************************/
u8 GPIO_u8SetPinMode	(const GPIO_PinConfig_t * Copy_PstrPinConfig)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_PstrPinConfig != NULL)
	{
		if(Copy_PstrPinConfig->PortId <= GPIO_u8_GPIOG)
		{
			u8 Local_u8PinMode = Copy_PstrPinConfig->PinMode;
			if(Local_u8PinMode == GPIO_u8_INPUT_PULL_UP)
			{
				/* Turn on the internal pull up resistor */
				SET_BIT(GPIO_Astr[Copy_PstrPinConfig->PortId]->ODR,Copy_PstrPinConfig->PinId);
				CLR_BIT(Local_u8PinMode,4); /*Get the Mode back to its value */
			}
			else if(Local_u8PinMode == GPIO_u8_INPUT_PULL_DOWN)
			{
				/* Turn off the internal pull up resistor */
				CLR_BIT(GPIO_Astr[Copy_PstrPinConfig->PortId]->ODR,Copy_PstrPinConfig->PinId);
			}
			if(Copy_PstrPinConfig->PinId <= GPIO_u8_PIN7)
			{
				GPIO_Astr[Copy_PstrPinConfig->PortId]->CRL &= ((~(0b1111)) << (Copy_PstrPinConfig->PinId * 4));
				GPIO_Astr[Copy_PstrPinConfig->PortId]->CRL |= (Local_u8PinMode << (Copy_PstrPinConfig->PinId * 4));
			}
			else if(Copy_PstrPinConfig->PinId <= GPIO_u8_PIN15)
			{
				u8 Local_u8PinId = Copy_PstrPinConfig->PinId - 8; /* As the structure is constant */
				GPIO_Astr[Copy_PstrPinConfig->PortId]->CRH &= ((~(0b1111)) << (Local_u8PinId * 4));
				GPIO_Astr[Copy_PstrPinConfig->PortId]->CRH |= (Local_u8PinMode << (Local_u8PinId * 4));
			}
			else
			{
				Local_u8ErrorState = STD_TYPES_NOK;
			}
		}
		else
		{
			Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		GPIO_u8SetPinMode
********************************************************************************/
u8 GPIO_u8SetPinValue	(const GPIO_PinConfig_t * Copy_PstrPinConfig , u8 Copy_u8PinValue)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_PstrPinConfig != NULL)
	{
		if(Copy_PstrPinConfig->PortId <= GPIO_u8_GPIOG && Copy_PstrPinConfig->PinId <= GPIO_u8_PIN15)
		{
			switch(Copy_u8PinValue)
			{
			case GPIO_u8_HIGH:
				SET_BIT(GPIO_Astr[Copy_PstrPinConfig->PortId]->BSRR,Copy_PstrPinConfig->PinId);
				break;
			case GPIO_u8_LOW:
				SET_BIT(GPIO_Astr[Copy_PstrPinConfig->PortId]->BRR,Copy_PstrPinConfig->PinId);
				break;
			default:
				Local_u8ErrorState = STD_TYPES_NOK;
			}
		}
		else
		{
			Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		GPIO_u8SetPinMode
********************************************************************************/
u8 GPIO_u8GetPinValue	(const GPIO_PinConfig_t * Copy_PstrPinConfig , u8 * Copy_Pu8RetunredPinValue)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_PstrPinConfig != NULL)
	{
		if(Copy_PstrPinConfig->PortId <= GPIO_u8_GPIOG && Copy_PstrPinConfig->PinId <= GPIO_u8_PIN15)
		{
			*Copy_Pu8RetunredPinValue = GET_BIT(GPIO_Astr[Copy_PstrPinConfig->PortId]->IDR,Copy_PstrPinConfig->PinId);
		}
		else
		{
			Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		GPIO_u8TogPinValue
********************************************************************************/
u8 GPIO_u8TogPinValue	(const GPIO_PinConfig_t * Copy_PstrPinConfig)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_PstrPinConfig != NULL)
	{
		if(Copy_PstrPinConfig->PortId <= GPIO_u8_GPIOG && Copy_PstrPinConfig->PinId <= GPIO_u8_PIN15)
		{
			TOG_BIT(GPIO_Astr[Copy_PstrPinConfig->PortId]->ODR,Copy_PstrPinConfig->PinId);
		}
		else
		{
			Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
