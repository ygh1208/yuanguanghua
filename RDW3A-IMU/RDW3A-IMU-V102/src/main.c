/**************************************************************************//**
 * $Id: ssp_master_polling.c 8558 2011-11-02 19:22:19Z nxp41306 $
 *
 * @file     ssp_master_polling.c
 * @brief    Main program body used to test SSP master on polling mode
 * @version  1.0
 * @date     26. Sep. 2010
 * @author   NXP MCU Team
 *
 * @note
 * Copyright (C) 2010 NXP Semiconductors(NXP). All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 ******************************************************************************/
 
/* Example group ----------------------------------------------------------- */
/** @defgroup SSP_Master_Polling  Master_Polling
 * @ingroup SSP_Examples
 * @{
 */
 
/* Includes ------------------------------------------------------------------*/  
#include "lpc12xx_libcfg.h"
#include "math.h" 
#include "stdio.h"

#include "head.h"
/* Private define ------------------------------------------------------------*/


#define UART_PORT 1

#if (UART_PORT == 0)
#define TEST_UART LPC_UART0
#define TEST_UART_RXD  IOCON_UART_RXD0_LOC0
#define TEST_UART_TXD  IOCON_UART_TXD0_LOC0

#elif (UART_PORT == 1)
#define TEST_UART (LPC_UART_TypeDef *)LPC_UART1
#define TEST_UART_RXD  IOCON_UART_RXD1_LOC0
#define TEST_UART_TXD  IOCON_UART_TXD1_LOC0
#endif


#define DATA_BLOCK_SIZE     128

/* Private variables ---------------------------------------------------------*/
static SSP_InitTypeDef SSP_InitStructure;
static IOCON_PIO_CFG_Type PIO_ConfigStructure;

static uint16_t buff_tx[DATA_BLOCK_SIZE], buff_rx[DATA_BLOCK_SIZE];

static uint32_t test_ret_code = 0;

uint8_t UartSendLabel = 0 ; 


/* Private functions ---------------------------------------------------------*/
uint32_t SSP_Master_Polling (void);
uint16_t SSP_SendByte(uint16_t byte);
uint16_t SSP_RecvByte(void);
extern uint8_t IMUDataBuffer[] ;

/**
  * @brief  Main program
  *
  * @param  None
  * @retval None
  */
void delay_ms(uint32_t x)
{


    while(x)
    {
        x -- ; 
    }
}



long double xxx = 4.11 ; 


int main (void) 
{

    SystemInit() ;
//    SYS_ConfigAHBCLK (SYS_AHBCLKCTRL_IOCON, ENABLE);    /* Enable clock to IOCON*/

    /*  SSP I/O config: CLK, SSEL, MISO, MOSI */
    IOCON_StructInit (&PIO_ConfigStructure);
    PIO_ConfigStructure.type = IOCON_SSP_SCK;
    IOCON_SetFunc (&PIO_ConfigStructure);
    PIO_ConfigStructure.type = IOCON_SSP_SSEL;
    IOCON_SetFunc (&PIO_ConfigStructure);
    PIO_ConfigStructure.type = IOCON_SSP_MISO;
    IOCON_SetFunc (&PIO_ConfigStructure);
    PIO_ConfigStructure.type = IOCON_SSP_MOSI;
    IOCON_SetFunc (&PIO_ConfigStructure);
 
    /* Initialize SSP configuration structure with user specified parameter */
    SSP_InitStructure.DataSize = SSP_DATASIZE_16;
    SSP_InitStructure.FrameFormat = SSP_FRAMEFORMAT_SPI;
    SSP_InitStructure.CPOL = SSP_CPOL_HIGH;
    SSP_InitStructure.CPHA = SSP_CPHA_SECOND;//SSP_CPHA_FIRST;
    SSP_InitStructure.Mode = SSP_MODE_MASTER;
    SSP_InitStructure.ClockRate = 1000000;
    SSP_Init(&SSP_InitStructure);

    /* Enable SSP peripheral */
    SSP_Cmd (ENABLE);

    /* Initialize debug via UART1, 9600-8-N-1-N */
    DB_Init ();
    
    while(1)
    {

        imu_pro() ; // Imu数据处理   
        accel_data_save() ; 
        
        if ( 1 == UartSendLabel )
        {
            UartSendLabel = 0 ; 
            DB_PutStr(IMUDataBuffer) ; 
            delay_ms(67000) ; 
        }
        
    }
        
        
    
    if (test_ret_code)
    {
        DB_PutStr ("\n\rNot all tests passed!\n\r");
    }
    else
    {
        DB_PutStr ("\n\rAll tests passed!\n\r");
    }

    DB_PutStr ("\n\rExample terminated!\n\r");

    while (1);
    
}

/**
  * @brief  Test SSP master working at polling mode
  *
  * @param  None
  * @retval status code indicates the test result. 
  *         0 for success, others for failure.
  */
uint16_t recvByte;
uint32_t SSP_Master_Polling ()
{
  //  uint16_t recvByte;
    uint32_t i;
    
    /* Init the data in buffer */
    for (i=0;i<DATA_BLOCK_SIZE;i++) 
    {
        buff_rx[i] = 0;
        buff_tx[i] = i;
    }

    /* Clear RX FIFO */
    while (SSP_GetStatus(SSP_STATUS_RNE) == SET)
    {
        recvByte = (uint8_t)SSP_ReceiveData(); 
    }
    
    /* Test1  ---------------------------------------------------------------*/     
    /* Master requests slave to send a block of data (CMD: 0xC1) */
    DB_PutStr ("Test1 description: \n\r");
    DB_PutStr ("  Master requests slave to send a block of data.\n\r");
    DB_PutStr ("  Then master will receive the data via POLLING mode and verify.\n\r");
    DB_PutStr ("Test1 started ...\n\r");    
    //SSP_SendByte (0x0600);  
    while(1)
    {
        recvByte =  SSP_RecvByte();
    }
    //do {
     //   recvByte =  SSP_RecvByte();
    //} while (recvByte != 0xD1);      
  
    /* slave will send a block of data (0x00, 0x01, ...),
    master will receive and verify */
    //for (i=0;i<DATA_BLOCK_SIZE;i++)
    //{
    //    buff_rx[i] = SSP_RecvByte();
    //}
             
    /* verify the received data */
   // for (i=0;i<DATA_BLOCK_SIZE;i++)
    //{
    //    if (buff_rx[i] != i)
    //    {
      //      DB_PutStr ("Master verify failed, Test1 failed!\n\r");
      //      return 1;
     //   }
   // }
   // DB_PutStr ("Master verify OK, Test1 passed!\n\r\n\r");

    /* Test2  ---------------------------------------------------------------*/
    /* Master request slave to receive a block of data (CMD: 0xC2) */
    //DB_PutStr ("Test2 description: \n\r");
    //DB_PutStr ("  Master send slave a block of data via POLLING modere.\n\r");
    //DB_PutStr ("  Then request slave to receive and verify.\n\r");
    //DB_PutStr ("  At last slave inform master whether the verify passed or not.\n\r");
    //DB_PutStr ("Test2 started ...\n\r");    
    //SSP_SendByte (0xC2);
    //do {
    //    recvByte =  SSP_RecvByte();   
    //} while ( recvByte != 0xD2 );      

    /* Master will send a block of data (0x0, 0x1, ...),
    slave will receive and verify */
   // for (i=0;i<DATA_BLOCK_SIZE;i++)
     //   SSP_SendByte(i); 
    
    /* 0xE0: slave verify ok
       0xE1: slave verify failed */
   // do {
     //   recvByte =  SSP_RecvByte();   
    //} while (recvByte != 0xE0 && recvByte != 0xE1);    
    //if (recvByte != 0xE0)
    //{
     //   DB_PutStr ("Slave verify failed, Test2 failed!\n\r");
    //    return 1;  
    //}
   // DB_PutStr ("Slave verify OK, Test2 passed!\n\r\n\r");

    return 0;
}

/**
  * @brief  Sends a byte through the SSP interface and return the byte received
  *         from the SSP bus.  
  *
  * @param  byte: byte to send.
  * @retval The value of the received byte.
  */
uint16_t SSP_SendByte(uint16_t byte)
{
    uint16_t byte_r;

    /* Clear Rx FIFO */
    while (SSP_GetStatus(SSP_STATUS_RNE) == SET)
        byte_r =  SSP_ReceiveData();

    /* Wait if Tx FIFO is not empty */ 
    while (SSP_GetStatus(SSP_STATUS_TFE) == RESET);    

    /* Send byte through the SSP peripheral */
    SSP_SendData(byte);

    /* Wait for transfer to finish */
    while (SSP_GetStatus(SSP_STATUS_BSY) == SET);

    /* Wait to receive a byte */
    while (SSP_GetStatus(SSP_STATUS_RNE) == RESET); 

    /* Return the byte read from the SSP bus */
    byte_r = (uint16_t)SSP_ReceiveData(); 

    return byte_r;
}

/**
  * @brief  Master reads a byte from the SSP bus.
  *
  * @param  None
  * @retval Byte Read from the SSP bus.
  */
uint16_t SSP_RecvByte(void)
{
    return (SSP_SendByte(0x1000));
}




/**
  * @}
  */

  
/* --------------------------------- End Of File ------------------------------ */
