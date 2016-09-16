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


/* Private functions ---------------------------------------------------------*/

uint8_t UartSendLabel = 0 ; 
extern uint8_t IMUDataBuffer[] ;
extern uint8_t UartSendTimerLabel ; 
extern uint8_t UartSendTimerValue ; 



long double xxx = 4.11 ; 

void delay_ms(uint32_t x)
{


    while(x)
    {
        x -- ; 
    }
}

int main (void)
{
    init_devices() ; // 初始化设备
        
    while(1)
    {

        delay_ms(500) ; 
        imu_pro() ; // Imu数据处理  
        accel_data_save() ; 
        
        if ( ( 1 == UartSendLabel ) && ( 1 == UartSendTimerLabel ) )
        {
            UartSendLabel = 0 ; 
            UartSendTimerLabel = 0 ; 
            UartSendTimerValue = 0 ; 
            DB_PutStr(IMUDataBuffer) ;   
        
        }
        
    }
        
        
     
}


  
/* --------------------------------- End Of File ------------------------------ */
