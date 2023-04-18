/******************************************************************************
*  File name:		ESP_program.c
*  Date:			Mar 24, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"

#include "ESP_interface.h"
#include "ESP_private.h"
#include "ESP_config.h"
#include "UART_interface.h"
#include "STK_interface.h"
#include "LCD_interface.h"
#include <string.h>
#include <stdio.h>


/*******************************************************************************
*                           Global Variables                                  *
*******************************************************************************/

u8 temp[100] = { 0 }; /* buffer to store messages from ESP */
static u8 counter = 0 ; /* counter to indicate the received chat location */
char (*P_Orders)[20] = NULL ; /* global variable to store the pointer to the receiver buffer of the main */
extern u8 OrdersWaiting;
static u8 PushPointer = 0;

/*******************************************************************************
*                           Private Function                                  *
*******************************************************************************/

/*******************************************************************************
* Function Name:		ESP8266_sendATCommand
* Description:			Functional to send AT commands to the ESP
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

static ESP_Response ESP8266_sendATCommand(char* AT_Command); /* can be used in this file only */

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		ESP8266_receive
********************************************************************************/
void ESP8266_ISRreceive(void)
{
	temp[counter] = ESP_UART_DATA;
	CLR_BIT(UART2->SR,5); /* Clear the flag */
	counter++;
	if(counter == 100){
		counter = 0; //pointer = 0;
	}
	if((strncmp((char*)temp,"\r\n+IPD",6) == 0) && temp[counter-1]=='\n')
	{
		ESP8266_responseToServer();
	}
}

/*******************************************************************************
* Function Name:		ESP8266_waitExpectedResponse
********************************************************************************/
ESP_Response ESP8266_waitExpectedResponse(char * Expected_Response,u16 MaxTimeout)
{
	u8 ResponseLength = strlen(Expected_Response);
	u16 time = 0;
	/* Wait until we get the expected response from the ESP or timeout occur*/
	while((strncmp((char*)temp,Expected_Response,ResponseLength) != 0) && (time < MaxTimeout))
	{
		time++;
	STK_u8SetmSBusyWait(1);
	}
	__asm volatile("CPSID I");

	if((strncmp((char*)temp,"ALREADY",7) == 0) || (strncmp((char*)temp,"link",4) == 0) \
			|| (strncmp((char*)temp,"CLOSED",6) == 0) || (strncmp((char*)temp,"AT",2) == 0)) /* check if we sent command that already applied to ESP */
	{
		time = 0;
	}
	ESP8266_resetBuffer();  /* Clear the receive buffer */

	if(time >= MaxTimeout ) 	/* check if timeout occurred */
	{
		return ESP_error;
	}
	return ESP_ok;
}

/*******************************************************************************
* Function Name:		ESP8266_resetBuffer
********************************************************************************/
void ESP8266_resetBuffer()
{
	memset(temp, 0, sizeof temp); /* Clear the whole variable */
	counter = 0; /* reset counter to index 0 */
}

/*******************************************************************************
* Function Name:		ESP8266_sendATCommand
********************************************************************************/
ESP_Response ESP8266_sendATCommand(char* AT_Command)
{
		char Expected_Response[60] = "\r\nOK\r\n";
		u16 timeout = 2000; /* 2 seconds timeout */
		if(strcmp(AT_Command,"ATE0\r\n") == 0) /* printing on the LCD the command purpose */
		{
			LCD_displayString("Disabling Echo");
			strcpy(Expected_Response,"\rATE0\r\r\n\r\nOK\r\n");
		}
		else if(strcmp(AT_Command,"AT+CWMODE=3\r\n") == 0)
		{
			LCD_displayString("ESP Station Mode");
		}
		else if(strcmp(AT_Command,"AT+CIPMUX=0\r\n") == 0)
		{
			LCD_displayString("Single Channel");
		}
		else if(strcmp(AT_Command,"AT+CIPMODE=0\r\n") == 0)
		{
			LCD_displayString("Normal Mode");
		}
		else if(strcmp(AT_Command,"AT\r\n") == 0)
		{
			LCD_displayString("AT");
		}
		else if(strncmp(AT_Command,"AT+CWJAP",8) == 0)
		{
			LCD_displayString("Connect to Wi-Fi");
			timeout = 10000; /* 10 seconds timeout */
			strcpy(Expected_Response,"WIFI DISCONNECT\r\nWIFI CONNECTED\r\nWIFI GOT IP\r\n\r\nOK\r\n");
		}
		else if(strncmp(AT_Command,"AT+CIPSTART",11) == 0)
		{
			LCD_displayString("Connect to Server");
			strcpy(Expected_Response,"CONNECT\r\n\r\nOK\r\n");
		}
		else if(strncmp(AT_Command,"AT+CIPCLOSE",11) == 0)
		{
			LCD_displayString("Complete Sending");
			strcpy(Expected_Response,"CLOSED\r\n\r\nOK\r\n");
		}
		else if(strncmp(AT_Command,"AT+CIPSEND",10) == 0)
		{
			LCD_displayString("Sending Data");
		}
		else if(strncmp(AT_Command,"AT+CIPSTATUS",12) == 0)
		{
			LCD_displayString("Check Connection");
			strcpy(Expected_Response,"STATUS:3");
		}
		else
		{
			LCD_displayString("Unknown Command");
		}
		LCD_moveCursor(1, 0);
		ESP8266_resetBuffer();
		__asm("CPSIE i");
		UART_u8SendString(ESP_u8_UART, (u8*)AT_Command);
		u8 State = ESP8266_waitExpectedResponse(Expected_Response, timeout); /* wait to get the expected response */
		if(State == ESP_ok)
		{
			LCD_displayString("OK");
			STK_u8SetmSBusyWait(1000);
			LCD_clearScreen();
		}
		else
		{
			LCD_displayString("ERROR");
			STK_u8SetmSBusyWait(1000);
			LCD_clearScreen();
			return ESP_error;
		}
		return ESP_ok;
}

/*******************************************************************************
* Function Name:		ESP8266_init
********************************************************************************/
void ESP8266_init(char ordersBuffer[][BUFFER_SIZE])
{
	STK_u8SetmSBusyWait(5000);
	LCD_clearScreen();
	P_Orders = ordersBuffer;

	u8 OldPrimask = 0;
	__asm volatile ("MRS %0, PRIMASK " : "=r"(OldPrimask) : ); /* Save the primask register */
	__asm("CPSID i"); /* close the global interrupt so we don't get interrupted while initializing */

	UART_u8SetCallBack(ESP_u8_UART, ESP8266_ISRreceive);

	char AT_Command[20] = {0};

	UART_u8SendByte(ESP_u8_UART, '\r');

	strcpy(AT_Command,"ATE0\r\n"); /* command to disable the echo */
	ESP8266_sendATCommand(AT_Command);

	strcpy(AT_Command,"AT+CWMODE=3\r\n"); /* command to make the ESP in station mode */
	ESP8266_sendATCommand(AT_Command);

	strcpy(AT_Command,"AT+CIPMUX=0\r\n"); /* Command to make the ESP has single connection */
	ESP8266_sendATCommand(AT_Command);

	strcpy(AT_Command,"AT+CIPMODE=0\r\n"); /* Command to make the ESP has single connection */
	ESP8266_sendATCommand(AT_Command);

	__asm volatile ("MSR PRIMASK,%0" : :"r"(OldPrimask)); /* Return the Primask to it's last value */
	LCD_clearScreen();
}

/*******************************************************************************
* Function Name:		ESP8266_ping
********************************************************************************/
ESP_Response ESP8266_ping(void)
{
	LCD_clearScreen();

	u8 OldPrimask = 0;
	__asm volatile ("MRS %0, PRIMASK " : "=r"(OldPrimask) : ); /* Save the primask register */
	__asm("CPSID i"); /* close the global interrupt so we don't get interrupted while initializing */

	char AT_Command[10] = "AT\r\n";
	ESP8266_sendATCommand(AT_Command);

	__asm volatile ("MSR PRIMASK,%0" : :"r"(OldPrimask)); /* Return the Primask to it's last value */

	return 	ESP_ok;
}

/*******************************************************************************
* Function Name:		ESP8266_connectWifi
********************************************************************************/
void ESP8266_connectWifiAndServer(const char *SSID, const char *Pass,const char *IP,const char *Port)
{
	char AT_Command[60] = {0};

	u8 OldPrimask = 0;
	__asm volatile ("MRS %0, PRIMASK " : "=r"(OldPrimask) : ); /* Save the primask register */
	__asm("CPSID i"); /* close the global interrupt so we don't get interrupted while initializing */

	/* Command to connect to Wi-fi with SSID and Password */
	sprintf((char*) AT_Command, (char*) "AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, Pass);
	ESP8266_sendATCommand(AT_Command);

	/* Command to connect to TCP server with IP and Port */
	sprintf((char*) AT_Command, (char*) "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n", IP, Port);
	ESP8266_sendATCommand(AT_Command);

	__asm volatile ("MSR PRIMASK,%0" : :"r"(OldPrimask)); /* Return the Primask to it's last value */

	LCD_clearScreen();
}

/*******************************************************************************
* Function Name:		ESP8266_sendData
********************************************************************************/
void ESP8266_sendData(const char *IP,const char *Port,const char *ESP_Data)
{
	LCD_clearScreen();

	u8 OldPrimask = 0;
	__asm volatile ("MRS %0, PRIMASK " : "=r"(OldPrimask) : ); /* Save the primask register */

	char AT_Command[60] = {0};
	u8 length = strlen(ESP_Data);

	/* Command to check the ESP connection */
	strcpy(AT_Command,"AT+CIPSTATUS");
	if(ESP8266_sendATCommand(AT_Command) != ESP_ok)
	{
		/* Connecting to the server again so we can use it later */
		sprintf((char*) AT_Command, (char*) "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n", IP, Port);
		ESP8266_sendATCommand(AT_Command);
	}

	/* Command to send data server with defined length */
	sprintf((char*) AT_Command, (char*) "AT+CIPSEND=%d\r\n", length+2);
	ESP8266_sendATCommand(AT_Command);

	/* Sending the data starting with 0 then the length then that actual data */
	UART_u8SendByte(ESP_u8_UART, 0x00); /* The first byte is zero */
	UART_u8SendByte(ESP_u8_UART, length); /* The second byte is the length of the data */
	UART_u8SendString(ESP_u8_UART, (u8 *)ESP_Data);  /* Sending the actual data */
	__asm("CPSIE i");
	STK_u8SetmSBusyWait(3);
	__asm("CPSID i");
	ESP8266_resetBuffer();

	/* Command to close the connection so we can send the data */
	strcpy(AT_Command,"AT+CIPCLOSE\r\n");
	ESP8266_sendATCommand(AT_Command);

	__asm volatile ("MSR PRIMASK,%0" : :"r"(OldPrimask)); /* Return the Primask to it's last value */

	LCD_clearScreen();
}

/*******************************************************************************
* Functions Name:		ESP8266_responseToServer
********************************************************************************/
void ESP8266_responseToServer(void)
{
	if(OrdersWaiting <= MAX_ORDERS)
	{
		OrdersWaiting++;
		u8 index = 0;
		while(temp[index++] != ':'); /* increment the index till it reach the order */
		index += 2; /* add two to skip the first two garbage characters */
		strcpy(P_Orders[PushPointer],(char *)(temp+index)); /* Save the order into the buffer */
		PushPointer++;
		if(PushPointer >= MAX_ORDERS)
		{
			PushPointer = 0;
		}
	}
	ESP8266_resetBuffer();
}
