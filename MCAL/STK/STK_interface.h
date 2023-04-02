/******************************************************************************
*  File name:		STK_interface.h
*  Date:			Mar 13, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

/*******************************************************************************
*                        		Clock Source	                               *
*******************************************************************************/
#define STK_u8_AHB						0
#define STK_u8_AHB_8					1

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		STK_u8Init
* Description:			Function to init the systick clock source and disable it
* Parameters (in):    	void
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 STK_u8Init(u8 Copy_u8ClockSource);

/*******************************************************************************
* Function Name:		STK_u8SetBusyWait
* Description:			Function to create delay with the systick timer
* Parameters (in):    	The number of ticks required to delay
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 STK_u8SetBusyWait(u32 Copy_u32NumOfTicks);

/*******************************************************************************
* Function Name:		STK_u8SetIntervalSingle
* Description:			Function to create single shot interrupt
* Parameters (in):    	The number of ticks required to fire the interrupt
* 						Pointer to fuction to be the systick handler
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 STK_u8SetIntervalSingle(u32 Copy_u32NumOfTicks, void(*Copy_pf)(void));

/*******************************************************************************
* Function Name:		STK_u8SetIntervalPeriodic
* Description:			Function to create periodic interrupt
* Parameters (in):    	The number of ticks required to fire the interrupt
* 						Pointer to fuction to be the systick handler
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 STK_u8SetIntervalPeriodic(u32 Copy_u32NumOfTicks, void(*Copy_pf)(void));

/*******************************************************************************
* Function Name:		STK_u8Stop
* Description:			Function to stop and disable the systick timer
* Parameters (in):    	void
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 STK_u8Stop(void);

/*******************************************************************************
* Function Name:		STK_u8GetElapsedTime
* Description:			Function to calculate the elapsed time
* Parameters (in):    	Pointer to variable to save the elapsed time in it
* Parameters (out):   	void
* Return value:      	None
********************************************************************************/
u8 STK_u8GetElapsedTime      (u32 * Copy_pu32ElapsedTime);

/*******************************************************************************
* Function Name:		STK_u8GetRemainingTime
* Description:			Function to calculate the remaining time
* Parameters (in):    	Pointer to variable to save the remaining time in it
* Parameters (out):   	void
* Return value:      	None
********************************************************************************/
u8 STK_u8GetRemainingTime    (u32 * Copy_pu32RemainingTime);

#endif
