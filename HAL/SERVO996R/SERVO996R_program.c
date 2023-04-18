/******************************************************************************
*  File name:		SERVO996R_program.c
*  Date:			Apr 14, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"

#include "SERVO996R_interface.h"
#include "SERVO996R_private.h"
#include "SERVO996R_config.h"
#include "GPIO_interface.h"
#include "TIMER1_interface.h"

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		SERVO996R_u8init
********************************************************************************/
u8 SERVO996R_u8init(SERVO996R_initStruct_t * Copy_PstrServoInit)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	GPIO_u8SetPinMode(Copy_PstrServoInit->SERVO996R_u8_PORT, Copy_PstrServoInit->SERVO996R_u8_PIN \
			, GPIO_u8_OUTPUT_AF_PP_50MHZ);
	switch(Copy_PstrServoInit->SERVO996R_u8_TIMER)
	{
	case TIMER_u8_1:
		TIMER1_u8InitPwmChannel(Copy_PstrServoInit->SERVO996R_u8_PWM_CHANNEL);
		break;

	default:
		Local_u8ErrorState = STD_TYPES_NOK;
		break;
	}

	return Local_u8ErrorState;
}

/*******************************************************************************
* Function Name:		SERVO996R_u8rotate
********************************************************************************/
u8 SERVO996R_u8rotate(SERVO996R_initStruct_t * Copy_PstrServoInit , u8 Copy_u8Angle)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(Copy_u8Angle >= SERVO996R_MIN_DEGREE && Copy_u8Angle <= SERVO996R_MAX_DEGREE && Copy_PstrServoInit != NULL)
	{
		f32 Local_u8DutyCycle = SERVO996R_MIN_DUTY + Copy_u8Angle * (((float)SERVO996R_MAX_DUTY-SERVO996R_MIN_DUTY) \
				/(SERVO996R_MAX_DEGREE - SERVO996R_MIN_DEGREE)) ;
		switch(Copy_PstrServoInit->SERVO996R_u8_TIMER)
		{
		case TIMER_u8_1:
			TIMER1_u8SetPWM(Copy_PstrServoInit->SERVO996R_u8_PWM_CHANNEL, SERVO996R_FREQUENCY, Local_u8DutyCycle);
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
