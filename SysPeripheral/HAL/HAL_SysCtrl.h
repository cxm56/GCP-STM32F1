#ifndef  __HAL_SYSCTRL_H
#define  __HAL_SYSCTRL_H

#include <chip.h>


/*----------------------------------------------------------------------------
    内核/全局相关宏
 *----------------------------------------------------------------------------*/

/* ---时钟总线定义--- */
#ifndef SYSTEM_FCLK
#define SYSTEM_FCLK    (SystemCoreClock)       //系统时钟总线
#endif

#ifndef AHB_FCLK
#define AHB_FCLK       SYSTEM_FCLK      //高性能总线
#endif

#ifndef APB2_FCLK
#define APB2_FCLK      SYSTEM_FCLK      //高速外设时钟总线(最高72M)
#endif

#ifndef APB1_FCLK
#define APB1_FCLK      (SYSTEM_FCLK/2)  //低速外设时钟总线(最高36M)
#endif

#ifndef TIMx_FCLK
#define TIMx_FCLK      SYSTEM_FCLK      //低速外设时钟总线2倍频(最高72M)
#endif



/*----------------------------------------------------------------------------
    内核NVIC相关宏
 *----------------------------------------------------------------------------*/

/* ---全局中断分组--- */
#define NVIC_PRIORITY_GROUP_0   (7 - 0)
#define NVIC_PRIORITY_GROUP_1   (7 - 1)
#define NVIC_PRIORITY_GROUP_2   (7 - 2)
#define NVIC_PRIORITY_GROUP_3   (7 - 3)
#define NVIC_PRIORITY_GROUP_4   (7 - 4)
#define NVIC_PRIORITY_GROUP        (NVIC_PRIORITY_GROUP_2)      //设置为组2



#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * 系统复位相关
 ****************************************************************************/

/**
  * @brief  系统复位函数
  * @param  None
  * @retval None
  */
void HAL_SystemReset(void);


/*****************************************************************************
 * 系统NVIC相关
 ****************************************************************************/

/**
  * @brief  NVIC使能
  * @param  IRQn 中断号
  * @param  ulPreemptPrio  抢占优先级
  * @param  ulSubPrio  响应优先级
  * @retval None
  */
void HAL_NVIC_Enable(IRQn_Type IRQn, uint32_t ulPreemptPrio, uint32_t ulSubPrio);


/**
  * @brief  禁止对应的内核中断
  * @param  IRQn 中断号
  * @retval None
  */
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn);


/*****************************************************************************
 * 系统唤醒休眠相关
 ****************************************************************************/

/**
  * @brief  待机模式进入
  * @param  None
  * @retval None
  */
void HAL_EnterSrandby(void);


#ifdef __cplusplus
}
#endif

#endif /* __HAL_SYSCTRL_H */
