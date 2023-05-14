/******************************************************************************
*  File name:		GPT_interface.h
*  Date:			Apr 21, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef GPT_INTERFACE_H_
#define GPT_INTERFACE_H_

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

/*******************************************************************************
*                 	     	General Purpose Timers                             *
*******************************************************************************/
#define TIMER_u8_2								2
#define TIMER_u8_3								3
#define TIMER_u8_4								4

/*******************************************************************************
*                 	     		Counting Direction	                           *
*******************************************************************************/
#define GPT_u8_COUNT_UP					0
#define GPT_u8_COUNT_DOWN				1

/*******************************************************************************
*                 	     		Pwm Channels		                           *
*******************************************************************************/
#define GPT_u8_PWM_CHANNEL1					0
#define GPT_u8_PWM_CHANNEL2					1
#define GPT_u8_PWM_CHANNEL3					2
#define GPT_u8_PWM_CHANNEL4					3

/*******************************************************************************
*                    		  Functions Prototypes                             *
*******************************************************************************/

/*******************************************************************************
* Function Name:		GPT_u8Init
* Description:			Function to initialize GPT
* Parameters (in):    	Timer number, Timer direction (up or down) and the prescaler
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 GPT_u8Init(u8 Copy_u8TimerNumber , u8 Copy_u8Direction , u16 Copy_u16Prescaler);

/*******************************************************************************
* Function Name:		GPT_u8SetBusyWait
* Description:			Function to create delay with the timer 1
* Parameters (in):    	Timer number and number of ticks
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 GPT_u8SetBusyWait(u8 Copy_u8TimerNumber , u16 Copy_u32NumOfTicks);

/*******************************************************************************
* Function Name:		GPT_u8SetIntervalPeriodic
* Description:			Timer number , Number of ticks and pointer to function to act as ISR
* Parameters (in):    	void
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 GPT_u8SetIntervalPeriodic(u8 Copy_u8TimerNumber , u16 Copy_u32NumOfTicks , void(*Copy_pf)(void));

/*******************************************************************************
* Function Name:		GPT_u8InitPwmChannel
* Description:			Function to initialize PWM channel
* Parameters (in):    	Channel Number
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 GPT_u8InitPwmChannel(u8 Copy_u8TimerNumber , u8 Copy_u8PwmChannel);

/*******************************************************************************
* Function Name:		GPT_u8SetPWM
* Description:			Function to create PWM with the timer 1
* Parameters (in):    	Frequency , duty cycle and channel number
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 GPT_u8SetPWM(u8 Copy_u8TimerNumber , u8 Copy_u8PwmChannel , u8 Copy_u8PwmFrequency , f32 Copy_u8PwmDutyCycle);

/*******************************************************************************
* Function Name:		GPT_u8Stop
* Description:			Function to stop and disable the timer
* Parameters (in):    	void
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 GPT_u8Stop(u8 Copy_u8TimerNumber);

#endif /* GPT_INTERFACE_H_ */
