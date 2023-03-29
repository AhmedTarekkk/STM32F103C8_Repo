/******************************************************************************
*  File name:		EXTI_program.c
*  Date:			Mar 17, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

/*******************************************************************************
*                           Global Variables                                  *
*******************************************************************************/
typedef void(*fptr)(void);

static fptr Global_pfArray[16] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
								  NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		EXTI_u8SetInterruptStatus
********************************************************************************/
u8 EXTI_u8SetInterruptStatus(u8 Copy_u8EXTINumber ,u8 Copy_u8EXTIStatus )
{
	u8 LocalErrorState = STD_TYPES_NOK;

	if(Copy_u8EXTINumber <= 15)
	{
		switch(Copy_u8EXTIStatus)
		{
		case EXTI_u8_ENABLE:
			LocalErrorState = STD_TYPES_OK;
			SET_BIT(EXTI->IMR,Copy_u8EXTINumber);
			break;

		case EXTI_u8_DISABLE:
			LocalErrorState = STD_TYPES_OK;
			CLR_BIT(EXTI->IMR,Copy_u8EXTINumber);
			break;
		}
	}
	else
	{
		/* Do Nothing */
	}

	return LocalErrorState;
}

/*******************************************************************************
* Function Name:		EXTI_u8SetEventtStatus
********************************************************************************/
u8 EXTI_u8SetEventtStatus(u8 Copy_u8EXTINumber ,u8 Copy_u8EXTIStatus )
{
	u8 LocalErrorState = STD_TYPES_NOK;

	if(Copy_u8EXTINumber <= 15)
	{
		switch(Copy_u8EXTIStatus)
		{
		case EXTI_u8_ENABLE:
			LocalErrorState = STD_TYPES_OK;
			SET_BIT(EXTI->EMR,Copy_u8EXTINumber);
			break;

		case EXTI_u8_DISABLE:
			LocalErrorState = STD_TYPES_OK;
			CLR_BIT(EXTI->EMR,Copy_u8EXTINumber);
			break;
		}
	}
	else
	{
		/* Do Nothing */
	}

	return LocalErrorState;
}

/*******************************************************************************
* Function Name:		EXTI_u8SetInterruptEdge
********************************************************************************/
u8 EXTI_u8SetInterruptEdge(u8 Copy_u8EXTINumber ,u8 Copy_u8EXTIEdge )
{
	u8 LocalErrorState = STD_TYPES_NOK;

	if(Copy_u8EXTINumber <= 15)
	{
		switch(Copy_u8EXTIEdge)
		{
		case EXTI_u8_RISING:
			LocalErrorState = STD_TYPES_OK;
			SET_BIT(EXTI->RTSR,Copy_u8EXTINumber);
			CLR_BIT(EXTI->FTSR,Copy_u8EXTINumber);
			break;

		case EXTI_u8_FALLING:
			LocalErrorState = STD_TYPES_OK;
			SET_BIT(EXTI->FTSR,Copy_u8EXTINumber);
			CLR_BIT(EXTI->RTSR,Copy_u8EXTINumber);
			break;

		case EXTI_u8_RISING_FALLING:
			LocalErrorState = STD_TYPES_OK;
			SET_BIT(EXTI->RTSR,Copy_u8EXTINumber);
			SET_BIT(EXTI->FTSR,Copy_u8EXTINumber);
			break;
		}

	}

	return LocalErrorState;
}

/*******************************************************************************
* Function Name:		EXTI_u8ClearInterruptPending
********************************************************************************/
u8 EXTI_u8ClearInterruptPending(u8 Copy_u8EXTINumber)
{
	u8 LocalErrorState = STD_TYPES_NOK;

	if(Copy_u8EXTINumber <= 15)
	{
		LocalErrorState = STD_TYPES_OK;
		SET_BIT(EXTI->PR,Copy_u8EXTINumber);
	}
	else
	{
		/* Do Nothing */
	}

	return LocalErrorState;
}

/*******************************************************************************
* Function Name:		EXTI_u8IsInterruptِActive
********************************************************************************/
u8 EXTI_u8IsInterruptِActive(u8 Copy_u8EXTINumber ,u8* Copy_pu8EXTIStatus )
{
	u8 LocalErrorState = STD_TYPES_NOK;

	if(Copy_u8EXTINumber <= 15)
	{
		LocalErrorState = STD_TYPES_OK;
		*Copy_pu8EXTIStatus = GET_BIT(EXTI->PR,Copy_u8EXTINumber);
	}
	else
	{
		/* Do Nothing */
	}

	return LocalErrorState;
}

/*******************************************************************************
* Function Name:		EXTI_u8GenerateSWInerrupt
* Description:			Function to generate interrupt with specific number with SW
* Parameters (in):    	void
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 EXTI_u8GenerateSWInerrupt(u8 Copy_u8EXTINumber)
{
	u8 LocalErrorState = STD_TYPES_NOK;

	if(Copy_u8EXTINumber <= 15)
	{
		LocalErrorState = STD_TYPES_OK;
		SET_BIT(EXTI->SWIER,Copy_u8EXTINumber);
	}
	else
	{
		/* Do Nothing */
	}

	return LocalErrorState;
}

/*******************************************************************************
* Function Name:		EXTI_u8SetCallBack
********************************************************************************/
u8 EXTI_u8SetCallBack(u8 Copy_u8EXTINumber , void(*Copy_pfCallback)(void))
{
	u8 LocalErrorState = STD_TYPES_NOK;

	if(Copy_u8EXTINumber <=  15)
	{
		LocalErrorState = STD_TYPES_OK;
		Global_pfArray[Copy_u8EXTINumber] = Copy_pfCallback;
	}
	else
	{
		/* Do Nothing */
	}

	return LocalErrorState;
}

/*******************************************************************************
*                       Interrupt Service Routines                            *
*******************************************************************************/
void EXTI0_IRQHandler(void)
{
	SET_BIT(EXTI->PR,0);
	if(Global_pfArray[0] != NULL )
	{
		Global_pfArray[0]();
	}
}

void EXTI1_IRQHandler(void)
{
	SET_BIT(EXTI->PR,1);
	if(Global_pfArray[1] != NULL )
	{
		Global_pfArray[1]();
	}
}

void EXTI2_IRQHandler(void)
{
	SET_BIT(EXTI->PR,2);
	if(Global_pfArray[2] != NULL )
	{
		Global_pfArray[2]();
	}
}

void EXTI3_IRQHandler(void)
{
	SET_BIT(EXTI->PR,3);
	if(Global_pfArray[3] != NULL )
	{
		Global_pfArray[3]();
	}
}

void EXTI4_IRQHandler(void)
{
	SET_BIT(EXTI->PR,4);
	if(Global_pfArray[4] != NULL )
	{
		Global_pfArray[4]();
	}
}

void EXTI9_5_IRQHandler(void)
{
	for (u8 i = 5 ; i <= 9 ; i++)
	{
		if(GET_BIT(EXTI->PR,i) == 1 && GET_BIT(EXTI->IMR,i) == 1)
		{
			SET_BIT(EXTI->PR,i);
			if(Global_pfArray[i] != NULL )
			{
				Global_pfArray[i]();
				return;
			}
		}
	}
}

void EXTI15_10_IRQHandler(void)
{
	for (u8 i = 10 ; i <= 15 ; i++)
	{
		if(GET_BIT(EXTI->PR,i) == 1)
		{
			SET_BIT(EXTI->PR,i);
			if(Global_pfArray[i] != NULL )
			{
				Global_pfArray[i]();
				return;
			}
		}
	}
}
