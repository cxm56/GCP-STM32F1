#ifndef  __HAL_TIME_INPUT_H
#define  __HAL_TIME_INPUT_H

#include "chip.h"

//定时器输入模式定义
#define TIM_INPUT_MODE_NORMAL               (0)         //正常捕获模式
#define TIM_INPUT_MODE_PWM1                 (1)         //正常PWM捕获模式
#define TIM_INPUT_MODE_PWM2                 (2)         //反相PWM捕获模式
#define TIM_INPUT_MODE_ENCODE               (3)         //编码器捕获模式

#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
 * 定时器输入捕获相关控制接口
 ****************************************************************************/

/**
  * @brief  定时器输入模式初始化
  * @param  uTimeNode 定时器节点
  * @param  uChannelMask 通道掩码字
  * @param  uInputMode 输入模式(普通/PWM输入/编码器模式)
  * @retval None
  */
void HAL_TIM_InputInit(uint8_t uTimeNode, uint8_t uChannelMask, uint8_t uInputMode);


/**
  * @brief  定时器输入中断使能
  * @param  uTimeNode 定时器节点
  * @param  uChannelMask 通道掩码字
  * @param  bIsEnable 使能位
  * @retval None
  */
void HAL_TIM_EnableInputIRQ(uint8_t uTimeNode, uint8_t uChannelMask, bool bIsEnable);


/**
  * @brief  定时器计数值获取
  * @param  uTimeNode 定时器节点
  * @retval 定时器计数寄存器值
  */
uint16_t HAL_TIM_GetInputCount(uint8_t uTimeNode);


/**
  * @brief  定时器输入捕获值获取
  * @param  uTimeNode 定时器节点
  * @param  uChannelMask 通道掩码字
  * @retval 定时器通道捕获寄存器值
  */
uint16_t HAL_TIM_GetInputCapValue(uint8_t uTimeNode, uint8_t uChannelMask);
  
#ifdef __cplusplus
}
#endif


#endif /* __HAL_TIME_INPUT_H */
