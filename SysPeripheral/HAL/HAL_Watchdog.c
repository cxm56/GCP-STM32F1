/**
  ******************************************************************************
  * @file    HAL_Watchdog.c
  * @author  Duhanfneg
  * @version V1.0
  * @date    2017.07.21
  * @brief   C_CAN drivers
  ******************************************************************************
  * @attention
  * 
  * 引脚,
  *     CAN1_TD  --- P0_1(Fun1),  P0_22(Fun3),
  *     CAN1_RD  --- P0_0(Fun1),  P0_21(Fun3),
  *                  
  *     CAN2_TD  --- P0_5(Fun2),  P2_8(Fun1),
  *     CAN2_RD  --- P0_4(Fun2),  P2_7(Fun1),
  * 
  * 
  *  
  ******************************************************************************
  */
  
/***********************************<INCLUDES>**********************************/
#include "HAL_Watchdog.h"
#include "chip.h"


/*****************************************************************************
 * 私有成员定义及实现
 ****************************************************************************/
//独立看门狗命令
#define IWDG_ACCESS_REG_ENABLE      ( 0x5555 )      //看门狗写寄存器使能
#define IWDG_START                  ( 0xCCCC )      //看门狗开始工作
#define IWDG_FEED                   ( 0xAAAA )      //喂狗,需定期发送此命令到IWDG_KEY中,否则系统会复位


/*****************************************************************************
 * WatchDog 基本功能接口
 ****************************************************************************/

/**
  * @brief  看门狗初始化
  * @param  ulTimeOutMs 超时时间
  * @retval None
  */
void HAL_WWDT_Init(uint32_t ulTimeOutMs)
{
    //配置工作模式
    IWDG->KR = IWDG_ACCESS_REG_ENABLE;  //操作寄存器使能
    IWDG->PR = 3;           //32分频,0.8S记一个数,最大超时时间为3276.8S
    IWDG->RLR = 2500;       //设置超时时间为2S
    IWDG->KR = IWDG_FEED;   //喂狗
    
}


/**
  * @brief  看门狗启动
  * @param  None
  * @retval None
  * @note   看门狗一旦开启,就无法停止
  */
void HAL_WWDT_Start(void)
{
    IWDG->KR = IWDG_START;  //独立看门狗开始工作
    
}


/**
  * @brief  喂狗
  * @param  None
  * @retval None
  */
void WWDT_Feed(void)
{
    IWDG->KR = IWDG_FEED;   //喂狗
    
}

