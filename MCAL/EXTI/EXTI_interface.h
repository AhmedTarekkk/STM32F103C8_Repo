/******************************************************************************
*  File name:		EXTI_interface.h
*  Date:			Mar 17, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

/*******************************************************************************
*                       	   		EXTI STATE                 	               *
*******************************************************************************/
#define EXTI_u8_DISABLE						0
#define EXTI_u8_ENABLE						1

/*******************************************************************************
*                       	   		EXTI EDGE                 	               *
*******************************************************************************/
#define EXTI_u8_RISING							0
#define EXTI_u8_FALLING							1
#define EXTI_u8_RISING_FALLING					2

/*******************************************************************************
*                       	   		EXTI NUMBER                 	               *
*******************************************************************************/
#define EXTI_u8_0								0
#define EXTI_u8_1								1
#define EXTI_u8_2								2
#define EXTI_u8_3								3
#define EXTI_u8_4								4
#define EXTI_u8_5								5
#define EXTI_u8_6								6
#define EXTI_u8_7								7
#define EXTI_u8_8								8
#define EXTI_u8_9								9
#define EXTI_u8_10								10
#define EXTI_u8_11								11
#define EXTI_u8_12								12
#define EXTI_u8_13								13
#define EXTI_u8_14								14
#define EXTI_u8_15								15

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		EXTI_u8SetInterruptStatus
* Description:			Function to enable or disable the required EXTI mask
* Parameters (in):    	The EXTI number
* 						EXTI state : Masked or Not Masked
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 EXTI_u8SetInterruptStatus(u8 Copy_u8EXTINumber ,u8 Copy_u8EXTIStatus );

/*******************************************************************************
* Function Name:		EXTI_u8SetEventtStatus
* Description:			Function to enable or disable the required EXTI mask
* Parameters (in):    	The EXTI number
* 						EXTI state : Masked or Not Masked
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 EXTI_u8SetEventtStatus(u8 Copy_u8EXTINumber ,u8 Copy_u8EXTIStatus );

/*******************************************************************************
* Function Name:		EXTI_u8SetInterruptEdge
* Description:			Function to enable the required interrupt
* Parameters (in):    	The EXTI number
* 						EXTI edge : Falling, Rising, or Rising and falling
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 EXTI_u8SetInterruptEdge(u8 Copy_u8EXTINumber ,u8 Copy_u8EXTIEdge );

/*******************************************************************************
* Function Name:		EXTI_u8ClearInterruptPending
* Description:			Function to enable the required interrupt
* Parameters (in):    	The EXTI number
* 						EXTI edge : Falling, Rising, or Rising and falling
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 EXTI_u8ClearInterruptPending(u8 Copy_u8EXTINumber);

/*******************************************************************************
* Function Name:		EXTI_u8IsInterruptِActive
* Description:			Function to check if the interrupt is active or not
* Parameters (in):    	The EXTI number
* 						Pointer to variable to store the interrupt status in it
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 EXTI_u8IsInterruptِActive(u8 Copy_u8EXTINumber ,u8* Copy_pu8EXTIStatus );

/*******************************************************************************
* Function Name:		EXTI_u8GenerateSWInerrupt
* Description:			Function to generate interrupt with specific number with SW
* Parameters (in):    	void
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 EXTI_u8GenerateSWInerrupt(u8 Copy_u8EXTINumber);

/*******************************************************************************
* Function Name:		EXTI_u8SetCallBack
* Description:			Function to Set the ISR for the EXTIx
* Parameters (in):    	EXTI number
* 						Pointer to function to act as ISR
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 EXTI_u8SetCallBack(u8 Copy_u8EXTINumber , void(*Copy_pfCallback)(void));

#endif
