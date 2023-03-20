/******************************************************************************
*  File name:		UART_interface.h
*  Date:			Mar 19, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/

/*******************************************************************************
* Name: UART_configStruct_t
* Type: Structure
* Description: Data type to initialize the DMA channel
********************************************************************************/

typedef struct
{
	u32 UART_u32_BAUD_RATE;
	u8 UART_u8_END_STRING;
	u8 UART_u8_STOP_BIT;
	u8 UART_u8_DATA_SIZE;
	u8 UART_u8_PARTIY;
	u8 UART_u8_RECEIVE_METHOD;
}UART_configStruct_t;

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

/*******************************************************************************
*                       	   	UART		                	        	   *
*******************************************************************************/
#define UART_u8_1								0
#define UART_u8_2								1
#define UART_u8_3								2

/*******************************************************************************
*                       	   	INTERRUPT		                	           *
*******************************************************************************/
#define UART_u8_POLLING							0
#define UART_u8_INTERRUP						1

/*******************************************************************************
*                       	   	DATA SIZE		                	           *
*******************************************************************************/
#define UART_u8_8_BITS							0
#define UART_u8_9_BITS							1

/*******************************************************************************
*                       	   	PARTIY		   		             	           *
*******************************************************************************/
#define UART_u8_PARITY_DISABLED					0b00
#define UART_u8_PARITY_EVEN						0b10
#define UART_u8_PARITY_ODD						0b11

/*******************************************************************************
*                       	   	STOP BITS		   		                       *
*******************************************************************************/
#define UART_u8_STOP_1_BIT						0b00
#define UART_u8_STOP_0_5_BIT					0b01
#define UART_u8_STOP_2_BITS						0b10
#define UART_u8_STOP_1_5_BITS					0b11

/*******************************************************************************
*                       Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		UART_u8Init
* Description:			Function to initialize the UART
* Parameters (in):    	Pointer to structure of type UART_RegDef_t
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 UART_u8Init(u8 Copy_u8UartNumber, UART_configStruct_t * Copy_PstrUARTConfig);

/*******************************************************************************
* Function Name:		UART_u8SendByte
* Description:			Function to send one byte using the UART
* Parameters (in):    	Data Byte
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 UART_u8SendByte(u8 Copy_u8UartNumber, u8 Copy_u8DataByte);

/*******************************************************************************
* Function Name:		UART_u8SendString
* Description:			Function to send string using the UART
* Parameters (in):    	Data Byte
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 UART_u8SendString(u8 Copy_u8UartNumber, u8* Copy_Pu8DataString);

/*******************************************************************************
* Function Name:		UART_u8SendStream
* Description:			Function to send stream of data using UART
* Parameters (in):    	Pointer to variable to receive the stream on it and the data size
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 UART_u8SendStream(u8 Copy_u8UartNumber, u8* Copy_pu8DataByte, u16 Copy_u8DataSize);

/*******************************************************************************
* Function Name:		UART_u8ReceiveByte
* Description:			Function to receive one byte using UART
* Parameters (in):    	Pointer to variable to save the data on it
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 UART_u8ReceiveByte(u8 Copy_u8UartNumber, u8* Copy_pu8DataByte);

/*******************************************************************************
* Function Name:		UART_u8ReceiveString
* Description:			Function to receive string using UART
* Parameters (in):    	Pointer to variable to receive the string on it
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 UART_u8ReceiveString(u8 Copy_u8UartNumber, u8* Copy_pu8DataByte);

/*******************************************************************************
* Function Name:		UART_u8ReceiveStream
* Description:			Function to receive string using UART
* Parameters (in):    	Pointer to variable to receive the stream on it and the data size
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 UART_u8ReceiveStream(u8 Copy_u8UartNumber, u8* Copy_pu8DataByte, u16 Copy_u8DataSize);

/*******************************************************************************
* Function Name:		UART_u8SetCallBack
* Description:			Function to set the ISR
* Parameters (in):    	Pointer to function to act as the ISR
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 UART_u8SetCallBack(u8 Copy_u8UartNumber, void(*Copy_pfCallback)(void));



#endif /* UART_INTERFACE_H_ */
