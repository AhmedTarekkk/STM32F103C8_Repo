/******************************************************************************
*  File name:		ESP_private.h
*  Date:			Mar 24, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef ESP_PRIVATE_H_
#define ESP_PRIVATE_H_

/*******************************************************************************
*                           Private Variables                                  *
*******************************************************************************/

static u8 temp[UART_RX_BUFFER_SIZE] = { 0 }; /* buffer to store messages from ESP */
static u8 counter = 0 ; /* counter to indicate the received chat location */
static char (*P_Orders)[BUFFER_SIZE] = NULL ; /* global variable to store the pointer to the receiver buffer of the main */
static u8 PushPointer = 0;

/*******************************************************************************
*                      Private Functions Prototypes                            *
*******************************************************************************/

/*******************************************************************************
* Function Name:		ESP8266_ISRreceive
* Description:			Function to act as ISR for Uart so we can receive msgs from ESP
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

static void ESP8266_ISRreceive(void);

/*******************************************************************************
* Function Name:		ESP8266_sendATCommand
* Description:			Functional to send AT commands to the ESP
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

static ESP_Response ESP8266_sendATCommand(char* AT_Command); /* can be used in this file only */

/*******************************************************************************
* Function Name:		ESP8266_responseToServer
* Description:			Function used to so the ESP can communicate with the server in both directions
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

static void ESP8266_responseToServer(void);

#endif /* ESP_PRIVATE_H_ */
