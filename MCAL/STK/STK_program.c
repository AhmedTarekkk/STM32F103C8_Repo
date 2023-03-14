/******************************************************************************
*  File name:		STK_program.c
*  Date:			Mar 13, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"

#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"

/*******************************************************************************
*                           Global Variables                                  *
*******************************************************************************/

/* to store the address of the function to be the ISR */
static volatile void (*STK_Pf)(void) = NULL;
static u8 STK_u8ModeOfInterval; /* Variable to save the current mode of the STK */

/*******************************************************************************
*                       Interrupt Service Routines                            *
*******************************************************************************/
void SysTick_Handler(void)
{
	if(STK_u8ModeOfInterval == STK_u8_SINGLE_INTERVAL)
	{
		/* Disable and Stop The Timer */
		CLR_BIT(STK->CTRL,0);
		CLR_BIT(STK->CTRL,1);
		STK->LOAD = 0;
		STK->VAL  = 0;
	}
	if(STK_Pf != NULL)
	{
		STK_Pf();
	}
	/* Clear The Interrupt Flag */
	CLR_BIT(STK->CTRL,16);
}

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		STK_voidInit
********************************************************************************/
u8 STK_voidInit(void)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	/* Choose the Clock Source */
	#if (STK_u8_CLK_SRC == STK_u8_AHB)
		SET_BIT(STK->CTRL,2);
	#elif (STK_u8_CLK_SRC == STK_u8_AHB_8)
		CLR_BIT(STK->CTRL,2);
	#else
		#error"Wrong Systick Clock Source"
	#endif
	/* Disable the timer */
	CLR_BIT(STK->CTRL,0);

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		STK_u8SetBusyWait
********************************************************************************/
u8 STK_u8SetBusyWait(u32 Copy_u32NumOfTicks)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_u32NumOfTicks <= 0x00FFFFFFFF)
	{
		/* Close the exception request */
		CLR_BIT(STK->CTRL,1);
		/* Load the required delay */
		STK->LOAD = Copy_u32NumOfTicks ;
		/* Enable the timer */
		SET_BIT(STK->CTRL,0);
		/* Start the change immediately by writing any value to VAL register */
		STK->VAL = 0;
		/* Wait until timer reach zero */
		while(GET_BIT(STK->CTRL,16) == 0);
		/* Disable Timer */
		CLR_BIT(STK->CTRL,0);
		STK->LOAD = 0;
		STK->VAL  = 0;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		STK_u8SetIntervalSingle
********************************************************************************/
u8 STK_u8SetIntervalSingle(u32 Copy_u32NumOfTicks, void(*Copy_pf)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if((Copy_u32NumOfTicks <= 0x00FFFFFF) && (Copy_pf != NULL))
	{
		/* Set Callback Function */
		STK_Pf = Copy_pf;
		/* Load the required delay */
		STK->LOAD = Copy_u32NumOfTicks ;
		/* Enable the timer */
		SET_BIT(STK->CTRL,0);
		/* Set the mode = interval */
		STK_u8ModeOfInterval = STK_u8_SINGLE_INTERVAL;
		/* Enable the exception request */
		SET_BIT(STK->CTRL,1);
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		STK_u8SetIntervalPeriodic
********************************************************************************/
u8 STK_u8SetIntervalPeriodic(u32 Copy_u32NumOfTicks, void(*Copy_pf)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;

	if((Copy_u32NumOfTicks <= 0x00FFFFFF) && (Copy_pf != NULL))
	{
		/* Set Callback Function */
		STK_Pf = Copy_pf;
		/* Load the required delay */
		STK->LOAD = Copy_u32NumOfTicks-1 ;
		/* Enable the timer */
		SET_BIT(STK->CTRL,0);
		/* Set the mode = interval */
		STK_u8ModeOfInterval = STK_u8_PERIODIC_INTERVAL;
		/* Enable the exception request */
		SET_BIT(STK->CTRL,1);
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		STK_voidStop
********************************************************************************/
u8 STK_voidStop(void)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	CLR_BIT(STK->CTRL,0);
	STK->LOAD = 0;
	STK->VAL  = 0;

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		STK_u8GetElapsedTime
********************************************************************************/
u8 STK_u8GetElapsedTime      (u32 * Copy_pu32ElapsedTime)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_pu32ElapsedTime != NULL)
	{
		*Copy_pu32ElapsedTime = (STK->LOAD - STK->VAL) ;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		STK_u8GetRemainingTime
********************************************************************************/
u8 STK_u8GetRemainingTime    (u32 * Copy_pu32RemainingTime)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_pu32RemainingTime != NULL)
	{
		*Copy_pu32RemainingTime = STK->VAL ;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}
