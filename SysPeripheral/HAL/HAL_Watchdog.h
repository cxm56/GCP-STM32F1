#ifndef  __HAL_WATCHDOG_H
#define  __HAL_WATCHDOG_H

#include "chip.h"

#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
 * WatchDog 基本功能接口
 ****************************************************************************/

/**
  * @brief  看门狗初始化
  * @param  ulTimeOutMs 超时时间
  * @retval None
  */
void HAL_WWDT_Init(uint32_t ulTimeOutMs);


/**
  * @brief  看门狗启动
  * @param  None
  * @retval None
  * @note   看门狗一旦开启,就无法停止
  */
void HAL_WWDT_Start(void);


/**
  * @brief  喂狗
  * @param  None
  * @retval None
  */
void WWDT_Feed(void);

    
#ifdef __cplusplus
}
#endif



#endif /* __HAL_WATCHDOG_H */
