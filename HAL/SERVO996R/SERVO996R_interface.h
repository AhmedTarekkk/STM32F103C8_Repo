/******************************************************************************
*  File name:		SERVO996R_interface.h
*  Date:			Apr 17, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef SERVO996R_INTERFACE_H_
#define SERVO996R_INTERFACE_H_

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/

/*******************************************************************************
* Name: SERVO996R
* Type: Structure
* Description: Data type to get the response of the ESP
********************************************************************************/
typedef struct
{
	u8 SERVO996R_u8_PORT;
	u8 SERVO996R_u8_PIN;
	u8 SERVO996R_u8_TIMER;
	u8 SERVO996R_u8_PWM_CHANNEL;
}SERVO996R_initStruct_t;

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		SERVO996R_u8init
* Description:			Function to initialize the servo
* Parameters (in):    	pointer to the servo init structure
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 SERVO996R_u8init(SERVO996R_initStruct_t * Copy_PstrServoInit);

/*******************************************************************************
* Function Name:		SERVO996R_u8rotate
* Description:			Function to rotate the servo with required angle
* Parameters (in):    	pointer the servo structure and the required angle
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 SERVO996R_u8rotate(SERVO996R_initStruct_t * Copy_PstrServoInit , u8 Copy_u8Angle);

#endif /* SERVO996R_INTERFACE_H_ */
