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



 160901 �޸�
����ʶ�� --�� �شŴ����־
���  һ�β��� ����һ������ �ı�����ǰ һ�εشŷ���һ�����ݵ�bug


 ******************************************************************************/

/* Example group ----------------------------------------------------------- */
/** @defgroup SSP_Master_Polling  Master_Polling
 * @ingroup SSP_Examples
 * @{
 */




 
/* Includes ------------------------------------------------------------------*/  
#include "lpc12xx_libcfg.h"
#include <stdlib.h>
#include <math.h>
#include "stdio.h"

#include "head.h"
/* Private define ------------------------------------------------------------*/


/* Private functions ---------------------------------------------------------*/

extern uint8_t IMUDataBuffer[] ;
extern uint8_t StaticLabel ; 
extern uint8_t UartSendTimerLabel ; 
extern uint8_t UartSendTimerValue ; 
extern int32_t PaceRecognitionFlag ;
/*��־λ*/
uint8_t UartSendLabel = 0 ; // ���ڷ��ͱ�־λ
uint8_t StepCoordProLabel = 0 ; // �������괦���־λ
uint8_t StepStaticProLabel = 0 ; // ������ֹ��־λ
uint8_t MAGNAngleProLabel = 0 ; // �����Ƕȴ����־λ
uint8_t StepAngleProFlag = 0 ; // �����Ƕȴ����־λ

uint8_t ImuDataProLabel = 0  ; // imu���ݴ����־λ
uint8_t AccelDataProLabel = 0  ; // ���ٶ����ݴ���
uint8_t MAGNDataProLabel = 0 ; // �ش����ݴ���
uint8_t GyroDataProLabel = 0 ; // ���������ݴ���

void symbol_pro()
{
    static int MAGNAngleProLabelTemp = 1 ; 
    
    if ( ( 1 == StaticLabel ) && ( 1 == MAGNAngleProLabelTemp ) &&( 1 == PaceRecognitionFlag ) )
    {
        MAGNAngleProLabel = 1 ;
        MAGNAngleProLabelTemp = 0 ; 
        PaceRecognitionFlag = 0;
    }
    if ( 0 == StaticLabel )
    {
        MAGNAngleProLabelTemp = 1 ; 
    }
}    
     
long double xyz = 0 ; 
int main (void)   
{
    init_devices() ; // ��ʼ���豸
      
    while(1)
    {
        if (1)
        {
            symbol_pro() ; // ��־������    
        }

        
        if (1 == ImuDataProLabel)
        {
            ImuDataProLabel = 0 ; 
            
        }
        
        if (1 == AccelDataProLabel)
        {
            AccelDataProLabel = 0 ; 
            
        }
        
        if (1 == GyroDataProLabel)
        {  
            GyroDataProLabel = 0 ; 
            
        }
        
        if (1 == MAGNDataProLabel)   
        {
            MAGNDataProLabel = 0 ; 
            
        }
  
        StepStaticProLabel = 1 ; 
        if ( 1 == StepStaticProLabel ) // ������ֹ״̬������
        {
            StepStaticProLabel = 0 ; 
            static_state_pro() ; 
        }      
  
        if ( 1 == MAGNAngleProLabel )
        {
            MAGNAngleProLabel = MAGN_angle_pro() ; // �شŽǶȴ���
        }
  
        if ( 1 == StepAngleProFlag )
        {   
            StepAngleProFlag = 0 ; 
            step_angle_pro() ; // �����Ƕȴ���
            StepCoordProLabel = 1;     
        }
 
        if ( 1 == StepCoordProLabel ) 
        {
            //��ʼ�Ƕȼ���
            StepCoordProLabel = 0 ; 
            altitude_pro(); //���θ߶ȴ���
            step_coord_pro() ; // �������괦��
        }           
        
        if ( ( 1 == UartSendLabel ) || ( 1 == UartSendTimerLabel ) )
        {
            UartSendLabel = 0 ; 
            UartSendTimerLabel = 0 ; 
            UartSendTimerValue = 0 ; 
            DB_PutStr(IMUDataBuffer) ; // ���ݷ��� 
        }   
        
    }
    
}


  
/* --------------------------------- End Of File ------------------------------ */
