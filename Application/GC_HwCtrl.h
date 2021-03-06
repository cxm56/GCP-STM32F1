#ifndef  __GC_HW_CFG_H
#define  __GC_HW_CFG_H

#include "../DataType/DataType.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * 硬件配置接口
 ****************************************************************************/

/**
  * @brief  系统硬件初始化
  * @param  None
  * @retval None
  */
void GC_HwInit(void);


/*****************************************************************************
 * 主线程LED显示接口
 ****************************************************************************/

/**
  * @brief  LED 流水灯循环
  * @param  None
  * @retval None
  */
void GC_MainWorkLedShow(void);


#ifdef __cplusplus
}
#endif


#endif /* __GC_HW_CFG_H */
