/******************************************************************************
*  File name:		ESP_config.h
*  Date:			Mar 24, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef ESP_CONFIG_H_
#define ESP_CONFIG_H_

#define UART_RX_BUFFER_SIZE			100
#define BUFFER_SIZE					20
#define MAX_ORDERS					10
#define ESP_u8_UART					UART_u8_2
#define ESP_UART_DATA				UART2->DR
#define ESP_EOS						'\n'

#endif /* ESP_CONFIG_H_ */
