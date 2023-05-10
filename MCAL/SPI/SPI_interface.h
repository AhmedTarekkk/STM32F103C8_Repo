/******************************************************************************
*  File name:		SPI_interface.h
*  Date:			May 8, 2023
*  Author:			Ahmed Tarek
*  Version:         1.0
*******************************************************************************/
#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/

/*******************************************************************************
* Name: SPI_configStruct_t
* Type: Structure
* Description: Data type to initialize the DMA channel
********************************************************************************/

typedef struct
{
	u8 SPI_u8_MCU_TYPE;
	u8 SPI_u8_BAUD_RATE;
	u8 SPI_u8_CLOCK_SETUP;
	u8 SPI_u8_DATA_SIZE;
	u8 SPI_u8_FRAME_FORMAT;
	u8 SPI_u8_NSS_SETUP;
	u8 SPI_u8_RECEIVE_METHOD;
}SPI_configStruct_t;

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

/*******************************************************************************
*                       	   	SPI NUMBER		                	        	   *
*******************************************************************************/
#define SPI_u8_1							0
#define SPI_u8_2							1

/*******************************************************************************
*                       	   	DEVICE	TYPE		                	        	   *
*******************************************************************************/
#define SPI_u8_SLAVE						0
#define SPI_u8_MASTER						1

/*******************************************************************************
*                       	   	BAUD RATE		                	        	   *
*******************************************************************************/
#define SPI_u8_FCLK_DIVIDED_BY_2			0
#define SPI_u8_FCLK_DIVIDED_BY_4			1
#define SPI_u8_FCLK_DIVIDED_BY_8			2
#define SPI_u8_FCLK_DIVIDED_BY_16			3
#define SPI_u8_FCLK_DIVIDED_BY_32			4
#define SPI_u8_FCLK_DIVIDED_BY_64			5
#define SPI_u8_FCLK_DIVIDED_BY_128			6
#define SPI_u8_FCLK_DIVIDED_BY_256			7

/*******************************************************************************
*                       	   	CLOCK SETUP		                	       	   *
*******************************************************************************/
#define SPI_u8_CPOL_0_CPHA_0				0
#define SPI_u8_CPOL_0_CPHA_1				1
#define SPI_u8_CPOL_1_CPHA_0				2
#define SPI_u8_CPOL_1_CPHA_1				3

/*******************************************************************************
*                       	   	DATA SIZE		                	      	   *
*******************************************************************************/
#define SPI_u8_8_BITS						0
#define SPI_u8_16_BITS						1

/*******************************************************************************
*                       	   	FRAME FORMAT		          	        	   *
*******************************************************************************/
#define SPI_u8_MSB_FIRST					0
#define SPI_u8_LSB_FIRST					1

/*******************************************************************************
*                       	   	NSS SETUP		                               *
*******************************************************************************/
#define SPI_u8_NSS_SW						2
#define SPI_u8_NSS_HW_OP_ENABLED			1 /* Used only when device operates in master mode */
#define SPI_u8_NSS_HW_OP_DISABLED			0 /* Used in master mode for multi-master and
												in slave mode for controlled by the gpio pin */

/*******************************************************************************
*                       	   	SLAVE SELECT		          	        	   *
*******************************************************************************/
#define SPI_u8_SLAVE_SELECT				0
#define SPI_u8_SLAVE_DESELECT					1

/*******************************************************************************
*                       	   	RECEIVE METHOD		          	        	   *
*******************************************************************************/
#define SPI_u8_POLLING						0b000 /* DMA disabled, send and receive with poling */
#define SPI_u8_INTERRUP						0b001 /* DMA disabled, send with polling and receive with interrupt */
#define SPI_u8_DMA_TX_POL_RX				0b100 /* Send with DMA receive with polling */
#define SPI_u8_DMA_TX_INT_RX				0b101 /* Send with DMA receive with interrupt */
#define SPI_u8_DMA_RX						0b010 /* Receive with DMA send with polling */
#define SPI_u8_DMA_TX_RX					0b110 /* Send with DMA receive with DMA */

/*******************************************************************************
*                       	   	DATA REGISTERS		          	        	   *
*******************************************************************************/
#define SPI_u8_1_DATA						SPI1->DR
#define SPI_u8_2_DATA						SPI2->DR

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		SPI_u8Init
* Description:			Function to init the SPI peripheral
* Parameters (in):    	SPI number
* 						Pointer to structure of type SPI_configStruct_t
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 SPI_u8Init(u8 Copy_u8SPINumber, SPI_configStruct_t * Copy_PstrSPIConfig);

/*******************************************************************************
* Function Name:		SPI_u8SWSlaveSelect
* Description:			Function to select or deselect the SPI slave
* Parameters (in):    	SPI number and slave status
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 SPI_u8SWSlaveSelect(u8 Copy_u8SPINumber, u8 Copy_SlaveState);

/*******************************************************************************
* Function Name:		SPI_u8SendReceiveByte
* Description:			Function to send 8 bits using SPI
* Parameters (in):    	SPI number and the data we want to transmit
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 SPI_u8SendReceiveByte(u8 Copy_u8SPINumber, u8 Copy_u8DataByte , u8 * Copy_pu8DataByte);

/*******************************************************************************
* Function Name:		SPI_u8SendReceive2Bytes
* Description:			Function to send 8 or 16 bits using SPI
* Parameters (in):    	SPI number and the data we want to transmit
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 SPI_u8SendReceive2Bytes(u8 Copy_u8SPINumber, u16 Copy_u16DataByte , u16 * Copy_pu16DataByte);

/*******************************************************************************
* Function Name:		SPI_u8SendString
* Description:			Function to send string using the SPI
* Parameters (in):    	SPI number and the data we want to transmit
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 SPI_u8SendString(u8 Copy_u8SPINumber, u8* Copy_Pu8DataString);

/*******************************************************************************
* Function Name:		SPI_u8ReceiveString
* Description:			Function to receive string using SPI
* Parameters (in):    	SPI number and Pointer to variable to receive the string on it
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 SPI_u8ReceiveString(u8 Copy_u8SPINumber, u8* Copy_Pu8DataString);

/*******************************************************************************
* Function Name:		SPI_u8SendString
* Description:			Function to send stream using the SPI
* Parameters (in):    	SPI number and the data we want to transmit
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 SPI_u8SendStream(u8 Copy_u8SPINumber, u8* Copy_Pu8DataStream , u8 Copy_StreamSize);

/*******************************************************************************
* Function Name:		SPI_u8ReceiveString
* Description:			Function to receive stream using SPI
* Parameters (in):    	SPI number , Pointer to variable to receive the stream on it and the data size
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 SPI_u8ReceiveStream(u8 Copy_u8SPINumber, u8* Copy_Pu8DataStream , u8 Copy_StreamSize);

/*******************************************************************************
* Function Name:		SPI_u8SetCallBack
* Description:			Function to set the ISR
* Parameters (in):    	SPI number and Pointer to function to act as the ISR
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 SPI_u8SetCallBack(u8 Copy_u8SPINumber, void(*Copy_pfCallback)(void));

/*******************************************************************************
* Function Name:		SPI_u8DeInit
* Description:			Function to de initialize the SPI
* Parameters (in):    	SPI number
* Parameters (out):   	u8
* Return value:      	OK or Error
********************************************************************************/
u8 SPI_u8DeInit(u8 Copy_u8SPINumber);

#endif /* SPI_INTERFACE_H_ */
