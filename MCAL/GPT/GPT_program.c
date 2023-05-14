/******************************************************************************
*  File name:		GPT_program.c
*  Date:			Apr 21, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"

#include "GPT_interface.h"
#include "GPT_private.h"
#include "GPT_config.h"

/*******************************************************************************
*                           Global Variables                                  *
*******************************************************************************/

static fptr_t Global_pfArr[3] = {NULL,NULL,NULL};

static GPT_RegDef_t * GPT_Astr[3] = {TIMER2,TIMER3,TIMER4};

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		GPT_u8Init
********************************************************************************/
u8 GPT_u8Init(u8 Copy_u8TimerNumber , u8 Copy_u8Direction , u16 Copy_u16Prescaler)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;
		GPT_Astr[Copy_u8TimerNumber]->CR1 = 0;
		SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CR1,7); /* Auto reload pre-load enable */
		GPT_Astr[Copy_u8TimerNumber]->CR1 |= ((Copy_u8Direction & 0b1) << 4); /* Set the direction up or down */
		GPT_Astr[Copy_u8TimerNumber]->PSC = ( Copy_u16Prescaler - 1 ) ;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		GPT_u8SetBusyWait
********************************************************************************/
u8 GPT_u8SetBusyWait(u8 Copy_u8TimerNumber , u16 Copy_u32NumOfTicks)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;
		CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->DIER,0); /* Disable the interrupt */
		GPT_Astr[Copy_u8TimerNumber]->ARR = (Copy_u32NumOfTicks & 0xFFFF);
		SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CR1,0); /* Enable The timer */
		while(GET_BIT(GPT_Astr[Copy_u8TimerNumber]->SR,0) == 0); /* Wait until update occurs */
		CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->SR,0); /* Clear the update flag */
		CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CR1,0); /* Disable The timer */
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		GPT_u8SetIntervalPeriodic
********************************************************************************/
u8 GPT_u8SetIntervalPeriodic(u8 Copy_u8TimerNumber , u16 Copy_u32NumOfTicks , void(*Copy_pf)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_pf != NULL && Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;
		Global_pfArr[Copy_u8TimerNumber] = Copy_pf;
		GPT_Astr[Copy_u8TimerNumber]->ARR = (Copy_u32NumOfTicks & 0xFFFF);
		SET_BIT(GPT_Astr[Copy_u8TimerNumber]->DIER,0); /* Enable the interrupt */
		SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CR1,0); /* Enable The timer */
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		GPT_u8InitPwmChannel
********************************************************************************/
u8 GPT_u8InitPwmChannel(u8 Copy_u8TimerNumber , u8 Copy_u8PwmChannel)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;
		switch(Copy_u8PwmChannel)
		{
		case GPT_u8_PWM_CHANNEL1:
			GPT_Astr[Copy_u8TimerNumber]->CCMR1 &= ~(0b11); /* Channel is output compare */
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CCMR1,3); /* Output compare preload enable */
			GPT_Astr[Copy_u8TimerNumber]->CCMR1 |= (0b11 << 5); /* PWM mode 1 */
			CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CCMR1,4); /* PWM mode 1 */
			CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CCER,1); /* high output polarity */
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CCER,0); /* Output enable */
			break;

		case GPT_u8_PWM_CHANNEL2:
			GPT_Astr[Copy_u8TimerNumber]->CCMR1 &= ~(0b11<<8);
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CCMR1,11);
			GPT_Astr[Copy_u8TimerNumber]->CCMR1 |= (0b11 << 13);
			CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CCMR1,12);
			CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CCER,5);
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CCER,4);
			break;

		case GPT_u8_PWM_CHANNEL3:
			GPT_Astr[Copy_u8TimerNumber]->CCMR2 &= ~(0b11);
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CCMR2,3);
			GPT_Astr[Copy_u8TimerNumber]->CCMR2 |= (0b11 << 5);
			CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CCMR2,4);
			CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CCER,9);
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CCER,8);
			break;

		case GPT_u8_PWM_CHANNEL4:
			GPT_Astr[Copy_u8TimerNumber]->CCMR2 &= ~(0b11<<8);
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CCMR2,11);
			GPT_Astr[Copy_u8TimerNumber]->CCMR2 |= (0b11 << 13);
			CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CCMR2,12);
			CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->CCER,13);
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CCER,12);
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
* Function Name:		GPT_u8SetPWM
********************************************************************************/
u8 GPT_u8SetPWM(u8 Copy_u8TimerNumber , u8 Copy_u8PwmChannel , u8 Copy_u8PwmFrequency , f32 Copy_u8PwmDutyCycle)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u16 Local_u16ReloadValue;
	u16 Local_u16CompareValue;

	if(Copy_u8PwmDutyCycle >= 0 && Copy_u8PwmDutyCycle <= 100 && Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;
		switch(Copy_u8PwmChannel)
		{
		case GPT_u8_PWM_CHANNEL1:
			Local_u16ReloadValue = ((F_CPU/(GPT_Astr[Copy_u8TimerNumber]->PSC+1))/Copy_u8PwmFrequency);
			Local_u16CompareValue = ((Copy_u8PwmDutyCycle*Local_u16ReloadValue)/100) ;
			GPT_Astr[Copy_u8TimerNumber]->ARR = Local_u16ReloadValue ; /* Setup Frequency */
			GPT_Astr[Copy_u8TimerNumber]->CCR1 = Local_u16CompareValue; /* Setup Duty Cycle */
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CR1,0); /* Enable the timer */
			break;

		case GPT_u8_PWM_CHANNEL2:
			Local_u16ReloadValue = ((F_CPU/(GPT_Astr[Copy_u8TimerNumber]->PSC+1))/Copy_u8PwmFrequency);
			Local_u16CompareValue = ((Copy_u8PwmDutyCycle*Local_u16ReloadValue)/100) ;
			GPT_Astr[Copy_u8TimerNumber]->ARR = Local_u16ReloadValue ; /* Setup Frequency */
			GPT_Astr[Copy_u8TimerNumber]->CCR2 = Local_u16CompareValue; /* Setup Duty Cycle */
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CR1,0); /* Enable the timer */
			break;

		case GPT_u8_PWM_CHANNEL3:
			Local_u16ReloadValue = ((F_CPU/(GPT_Astr[Copy_u8TimerNumber]->PSC+1))/Copy_u8PwmFrequency);
			Local_u16CompareValue = ((Copy_u8PwmDutyCycle*Local_u16ReloadValue)/100) ;
			GPT_Astr[Copy_u8TimerNumber]->ARR = Local_u16ReloadValue ; /* Setup Frequency */
			GPT_Astr[Copy_u8TimerNumber]->CCR3 = Local_u16CompareValue; /* Setup Duty Cycle */
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CR1,0); /* Enable the timer */
			break;

		case GPT_u8_PWM_CHANNEL4:
			Local_u16ReloadValue = ((F_CPU/(GPT_Astr[Copy_u8TimerNumber]->PSC+1))/Copy_u8PwmFrequency);
			Local_u16CompareValue = ((Copy_u8PwmDutyCycle*Local_u16ReloadValue)/100) ;
			GPT_Astr[Copy_u8TimerNumber]->ARR = Local_u16ReloadValue ; /* Setup Frequency */
			GPT_Astr[Copy_u8TimerNumber]->CCR4 = Local_u16CompareValue; /* Setup Duty Cycle */
			SET_BIT(GPT_Astr[Copy_u8TimerNumber]->CR1,0); /* Enable the timer */
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
* Function Name:		GPT_u8Stop
********************************************************************************/
u8 GPT_u8Stop(u8 Copy_u8TimerNumber)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_u8TimerNumber >= 2 && Copy_u8TimerNumber <= 4)
	{
		Copy_u8TimerNumber -= 2;
		GPT_Astr[Copy_u8TimerNumber]->CR1 = 0;
		GPT_Astr[Copy_u8TimerNumber]->ARR = 0;
		GPT_Astr[Copy_u8TimerNumber]->PSC = 0;
		CLR_BIT(GPT_Astr[Copy_u8TimerNumber]->DIER,0); /* Disable the interrupt */
		SET_BIT(GPT_Astr[Copy_u8TimerNumber]->EGR,0);
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
void TIM2_IRQHandler(void)
{
	if(Global_pfArr[0] != NULL)
	{
		Global_pfArr[0]();
	}
	CLR_BIT(TIMER2->SR,0); /* Clear the update flag */
}

void TIM3_IRQHandler(void)
{
	if(Global_pfArr[1] != NULL)
	{
		Global_pfArr[1]();
	}
	CLR_BIT(TIMER3->SR,0); /* Clear the update flag */
}

void TIM4_IRQHandler(void)
{
	if(Global_pfArr[2] != NULL)
	{
		Global_pfArr[2]();
	}
	CLR_BIT(TIMER4->SR,0); /* Clear the update flag */
}
