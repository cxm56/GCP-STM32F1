/**
  ******************************************************************************
  * @file    HAL_SysCtrl.h
  * @author  Duhanfneg
  * @version V1.0
  * @date    2017.10.19
  * @brief   MCU Ctrl Interface
  ******************************************************************************
  * @attention
  * 
  * 
  * 
  * 
  ******************************************************************************
  */
   
   
/***********************************<INCLUDES>**********************************/
#include "HAL_SysCtrl.h"
#include "chip.h"


/*****************************************************************************
 * 系统相关控制接口
 ****************************************************************************/

/**
  * @brief  系统复位函数
  * @param  None
  * @retval None
  */
void HAL_SystemReset(void)
{
    NVIC_SystemReset(); //复位
    
}


/**
  * @brief  NVIC使能
  * @param  IRQn 中断号
  * @param  PreemptPriority  抢占优先级
  * @param  SubPriority  响应优先级
  * @retval None
  */
void HAL_NVIC_Enable(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
    NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP);  
    NVIC_SetPriority((IRQn), NVIC_EncodePriority (NVIC_PRIORITY_GROUP, PreemptPriority, SubPriority));  
    NVIC_EnableIRQ(IRQn); 
    
}


/**
  * @brief  禁止对应的内核中断
  * @param  IRQn 中断号
  * @retval None
  */
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn)
{ 
    NVIC_DisableIRQ((IRQn));
    
}







