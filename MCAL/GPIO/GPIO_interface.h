/******************************************************************************
*  File name:		GPIO_interface.h
*  Date:			Mar 8, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

/*******************************************************************************
*                        			PORT 	  	                               *
*******************************************************************************/
#define GPIO_u8_GPIOA						0
#define GPIO_u8_GPIOB						1
#define GPIO_u8_GPIOC						2
#define GPIO_u8_GPIOD						3
#define GPIO_u8_GPIOE						4
#define GPIO_u8_GPIOF						5
#define GPIO_u8_GPIOG						6

/*******************************************************************************
*                        			PIN 	  	                               *
*******************************************************************************/
#define GPIO_u8_PIN0						0
#define GPIO_u8_PIN1						1
#define GPIO_u8_PIN2						2
#define GPIO_u8_PIN3						3
#define GPIO_u8_PIN4						4
#define GPIO_u8_PIN5						5
#define GPIO_u8_PIN6						6
#define GPIO_u8_PIN7						7
#define GPIO_u8_PIN8						8
#define GPIO_u8_PIN9						9
#define GPIO_u8_PIN10						10
#define GPIO_u8_PIN11						11
#define GPIO_u8_PIN12						12
#define GPIO_u8_PIN13						13
#define GPIO_u8_PIN14						14
#define GPIO_u8_PIN15						15

/*******************************************************************************
*                        			INPUT MODES 	  	                       *
*******************************************************************************/
#define GPIO_u8_INPUT_ANALOG					0b0000
#define GPIO_u8_INPUT_FLOATING					0b0100
#define GPIO_u8_INPUT_PULL_DOWN					0b1000
#define GPIO_u8_INPUT_PULL_UP					0b11000 /* To know if it is pull up or down */

/*******************************************************************************
*                        			OUTPUT MODES 	  	                       *
*******************************************************************************/
#define GPIO_u8_OUTPUT_GP_PP_10MHZ				0b0001
#define GPIO_u8_OUTPUT_GP_OD_10MHZ				0b0101
#define GPIO_u8_OUTPUT_AF_PP_10MHZ				0b1001
#define GPIO_u8_OUTPUT_AF_OD_10MHZ				0b1101

#define GPIO_u8_OUTPUT_GP_PP_2MHZ				0b0010
#define GPIO_u8_OUTPUT_GP_OD_2MHZ				0b0110
#define GPIO_u8_OUTPUT_AF_PP_2MHZ				0b1010
#define GPIO_u8_OUTPUT_AF_OD_2MHZ				0b1110

#define GPIO_u8_OUTPUT_GP_PP_50MHZ				0b0011
#define GPIO_u8_OUTPUT_GP_OD_50MHZ				0b0111
#define GPIO_u8_OUTPUT_AF_PP_50MHZ				0b1011
#define GPIO_u8_OUTPUT_AF_OD_50MHZ				0b1111

/*******************************************************************************
*                        			OUTPUT VALUES 	  	                       *
*******************************************************************************/
#define GPIO_u8_HIGH                       1
#define GPIO_u8_LOW                        0

/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/

/*******************************************************************************
* Name: GPIO_PinConfig_t
* Type: Structure
* Description: Data type to define the required pin
********************************************************************************/
typedef struct
{
	u8 PortId;
	u8 PinId;
	u8 PinMode;
}GPIO_PinConfig_t;

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		GPIO_u8SetPinMode
* Description:			Function to set the mode for the required pin mode
* Parameters (in):    	Pointer to structure of type GPIO_PinConfig_t
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 GPIO_u8SetPinMode	(const GPIO_PinConfig_t * Copy_PstrPinConfig);

/*******************************************************************************
* Function Name:		GPIO_u8SetPinValue
* Description:			Function to write the required pin value
* Parameters (in):    	Pointer to structure of type GPIO_PinConfig_t
* 						value to write in the required pin
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 GPIO_u8SetPinValue	(const GPIO_PinConfig_t * Copy_PstrPinConfig , u8 Copy_u8PinValue);

/*******************************************************************************
* Function Name:		GPIO_u8GetPinValue
* Description:			Function to get the required pin value
* Parameters (in):    	Pointer to structure of type GPIO_PinConfig_t and
* 						Pointer to variable to get the ping value in it
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 GPIO_u8GetPinValue	(const GPIO_PinConfig_t * Copy_PstrPinConfig , u8 * Copy_Pu8RetunredPinValue);

/*******************************************************************************
* Function Name:		GPIO_u8TogPinValue
* Description:			Function to toggle the required pin value
* Parameters (in):    	Pointer to structure of type GPIO_PinConfig_t
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 GPIO_u8TogPinValue	(const GPIO_PinConfig_t * Copy_PstrPinConfig);

#endif
