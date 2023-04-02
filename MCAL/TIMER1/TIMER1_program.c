/******************************************************************************
*  File name:		TIMER1_program.c
*  Date:			Apr 1, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"

#include <TIMER1_interface.h>
#include <TIMER1_private.h>
#include <TIMER1_config.h>

/*******************************************************************************
*                           Global Variables                                  *
*******************************************************************************/

/* to store the address of the function to be the ISR */
static void (*TIMER1_Pf)(void) = NULL;

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		TIMER1_u8SetBusyWait
********************************************************************************/
u8 TIMER1_u8Init(u8 Copy_u8Direction , u16 Copy_u16Prescaler)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	TIMER1->CR1 = 0;
	SET_BIT(TIMER1->CR1,7); /* Auto reload pre-load enable */
	TIMER1->CR1 |= ((Copy_u8Direction & 0b1) << 4); /* Set the direction up or down */
	TIMER1->PSC = ( Copy_u16Prescaler - 1 ) ;

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		TIMER1_u8SetBusyWait
********************************************************************************/
u8 TIMER1_u8SetBusyWait(u16 Copy_u32NumOfTicks , u8 Copy_u8RepetitionNumebr)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	CLR_BIT(TIMER1->DIER,0); /* Disable the interrupt */
	TIMER1->ARR = (Copy_u32NumOfTicks & 0xFFFF);
	TIMER1->RCR = ((Copy_u8RepetitionNumebr - 1) & 0xFF);
	SET_BIT(TIMER1->CR1,0); /* Enable The timer */
	while(GET_BIT(TIMER1->SR,0) == 0); /* Wait until update occurs */
	CLR_BIT(TIMER1->SR,0); /* Clear the update flag */
	CLR_BIT(TIMER1->CR1,0); /* Disable The timer */

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		TIMER1_u8SetIntervalPeriodic
********************************************************************************/
u8 TIMER1_u8SetIntervalPeriodic(u16 Copy_u32NumOfTicks , u8 Copy_u8RepetitionNumebr , void(*Copy_pf)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_pf != NULL)
	{
		TIMER1_Pf = Copy_pf;
		TIMER1->ARR = (Copy_u32NumOfTicks & 0xFFFF);
		TIMER1->RCR = ((Copy_u8RepetitionNumebr - 1) & 0xFF);
		SET_BIT(TIMER1->DIER,0); /* Enable the interrupt */
		SET_BIT(TIMER1->CR1,0); /* Enable The timer */
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		TIMER1_u8Stop
********************************************************************************/
u8 TIMER1_u8Stop(void)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	TIMER1->CR1 = 0;
	TIMER1->ARR = 0;
	TIMER1->RCR = 0;
	TIMER1->PSC = 0;
	CLR_BIT(TIMER1->DIER,0); /* Disable the interrupt */
	SET_BIT(TIMER1->EGR,0);

	return Local_u8ErrorState;
}


/*******************************************************************************
*                       Interrupt Service Routines                            *
*******************************************************************************/
void TIM1_UP_IRQHandler(void)
{
	if(TIMER1_Pf != NULL)
	{
		TIMER1_Pf();
	}
	CLR_BIT(TIMER1->SR,0); /* Clear the update flag */
}
