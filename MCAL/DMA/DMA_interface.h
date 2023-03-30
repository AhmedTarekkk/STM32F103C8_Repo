/******************************************************************************
*  File name:		DMA_interface.h
*  Date:			Mar 18, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/

#ifndef DMA_INTERFACE_H_
#define DMA_INTERFACE_H_

/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/

/*******************************************************************************
* Name: DMA_configStruct
* Type: Structure
* Description: Data type to initialize the DMA channel
********************************************************************************/

typedef struct
{
	u8 ChannelNumber;
	u8 ChannelPriority;
	u8 DataSize;
	u8 DataTransferType;
	u8 IncrementMode;
	u8 EnableTCInt ; /* Transmission Complete Interrupt */
}DMA_configStruct_t;

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

/*******************************************************************************
*                       	   	DMA CHANNELS                 	               *
*******************************************************************************/
#define DMA_u8_CHANNEL1							1
#define DMA_u8_CHANNEL2							2
#define DMA_u8_CHANNEL3							3
#define DMA_u8_CHANNEL4							4
#define DMA_u8_CHANNEL5							5
#define DMA_u8_CHANNEL6							6
#define DMA_u8_CHANNEL7							7

/*******************************************************************************
*                       	   	CHANNELS PRIORITY                	           *
*******************************************************************************/
#define DMA_u8_PRIORITY_LOW						0
#define DMA_u8_PRIORITY_MEDIUM					1
#define DMA_u8_PRIORITY_HIGH					2
#define DMA_u8_PRIORITY_VERYHIGH				3

/*******************************************************************************
*                       	   		DATA SIZE	                	           *
*******************************************************************************/
#define DMA_u8_DATA_SIZE_1BYTE					0
#define DMA_u8_DATA_SIZE_2BYTES					1
#define DMA_u8_DATA_SIZE_4BYTES					2

/*******************************************************************************
*                       	   	TRANSFER TYPE	                	           *
*******************************************************************************/
#define DMA_u8_PER_TO_MEM						0
#define DMA_u8_MEM_TO_PER						1
#define DMA_u8_MEM_TO_MEM						2

/*******************************************************************************
*                       	   	TC INTERRUPT	                	           *
*******************************************************************************/
#define DMA_u8_TC_INT_DISABLE					0
#define DMA_u8_TC_INT_ENABLE					1

/*******************************************************************************
*                       	   	AUTO INCREMENT	                	           *
*******************************************************************************/
#define DMA_u8_AUTO_INC_DISABLE					0
#define DMA_u8_AUTO_INC_PER						1
#define DMA_u8_AUTO_INC_MEM						2
#define DMA_u8_AUTO_INC_PER_MEM					3

/*******************************************************************************
*                         	PERIPHERALS ADDRESS AND CHANNEL	                   *
*******************************************************************************/
#define DMA_u8_UART1_TX_CH4						(u32)(&(UART1->DR))
#define DMA_u8_UART1_RX_CH5						(u32)(&(UART1->DR))
#define DMA_u8_UART2_TX_CH7						(u32)(&(UART2->DR))
#define DMA_u8_UART2_RX_CH6						(u32)(&(UART2->DR))
#define DMA_u8_UART3_TX_CH2						(u32)(&(UART3->DR))
#define DMA_u8_UART3_RX_CH3						(u32)(&(UART3->DR))
/* Update the rest of the peripherals data address when you need them */

/*******************************************************************************
*                       Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		DMA_u8ChannelInit
* Description:			Function to initialize the DMA channel
* Parameters (in):    	Pointer to structure of type DMA_configStruct_t
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 DMA_u8ChannelInit	(DMA_configStruct_t * Copy_PstrDMAChannelConfig);

/*******************************************************************************
* Function Name:		DMA_u8ChannelTransfer
* Description:			Function to setup the DMA connection with interrupt method
* Parameters (in):    	Channel Number
* 						Memory and Peripheral address
* 						The total number of transfers
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 DMA_u8ChannelTransfer	(u8 Copy_u8ChannelNumber, u32 Copy_u32MemAddress,u32 Copy_u32PerAddress,u32 Copy_u32NumberOfTransfers);

/*******************************************************************************
* Function Name:		DMA_u8ChannelTransfer_BusyWait
* Description:			Function to setup the DMA connection with polling method
* Parameters (in):    	Channel Number
* 						Memory and Peripheral address
* 						The total number of transfers
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 DMA_u8ChannelTransfer_BusyWait	(u8 Copy_u8ChannelNumber, u32 Copy_u32MemAddress,u32 Copy_u32PerAddress,u32 Copy_u32NumberOfTransfers);

/*******************************************************************************
* Function Name:		DMA_u8CheckIfErrorOcuured
* Description:			Function to check if transmission error occurred on the required channel
* Parameters (in):    	Channel Number
* 						Pointer to Variable to indicate if error occurred or not
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 DMA_u8CheckIfErrorOccurred	(u8 Copy_u8ChannelNumber, u8 * Copy_Pu8ErrorState);

/*******************************************************************************
* Function Name:		DMA_u8SetCallBack
* Description:			Function to set the ISR for the required Channel
* Parameters (in):    	Channel Number
* 						Pointer to function to act as ISR
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 DMA_u8SetCallBack(u8 Copy_u8ChannelNumber, void(*Copy_pfCallback)(void));

#endif /* DMA_INTERFACE_H_ */
