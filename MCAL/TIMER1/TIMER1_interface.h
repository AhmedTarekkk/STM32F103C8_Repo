/******************************************************************************
*  File name:		TIMER1_interface.h
*  Date:			Apr 1, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

/*******************************************************************************
*                 	     		Advanced Timers                               *
*******************************************************************************/
#define TIMER1_u8_1							0
#define TIMER1_u8_8							1

/*******************************************************************************
*                 	     		Counting Direction	                           *
*******************************************************************************/
#define TIMER1_u8_COUNT_UP					0
#define TIMER1_u8_COUNT_DOWN				1

/*******************************************************************************
*                    		  Functions Prototypes                             *
*******************************************************************************/

/*******************************************************************************
* Function Name:		TIMER1_u8Init
* Description:			Function to initialize timer1
* Parameters (in):    	Timer direction (up or down) and the prescaler
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 TIMER1_u8Init(u8 Copy_u8Direction , u16 Copy_u16Prescaler);

/*******************************************************************************
* Function Name:		TIMER1_u8SetBusyWait
* Description:			Function to create delay with the timer 1
* Parameters (in):    	Number of ticks and the repetition number
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 TIMER1_u8SetBusyWait(u16 Copy_u32NumOfTicks , u8 Copy_u8RepetitionNumebr);

/*******************************************************************************
* Function Name:		TIMER1_u8SetIntervalPeriodic
* Description:			Number of ticks, repetition number and pointer to function to act as ISR
* Parameters (in):    	void
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 TIMER1_u8SetIntervalPeriodic(u16 Copy_u32NumOfTicks , u8 Copy_u8RepetitionNumebr , void(*Copy_pf)(void));

/*******************************************************************************
* Function Name:		TIMER1_u8Stop
* Description:			Function to stop and disable the timer
* Parameters (in):    	void
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 TIMER1_u8Stop(void);

#endif /* TIMER1_INTERFACE_H_ */
