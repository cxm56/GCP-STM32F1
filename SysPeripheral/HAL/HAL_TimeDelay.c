/**
  ******************************************************************************
  * @file    HAL_TimeDelay.c
  * @author  Duhanfneg
  * @version V1.0 
  * @date    2017.08.17
  * @brief   UART delay drivers
  ******************************************************************************
  * @attention
  * 
  * 
  ******************************************************************************
  */
  
/***********************************<INCLUDES>**********************************/
#include "HAL_TimeDelay.h"
#include "HAL_SysCtrl.h"
#include "chip.h"

typedef enum
{
    HAL_TIM_0 = 0,  //TIM1 高级定时器
    HAL_TIM_1,      //TIM8 高级定时器
    HAL_TIM_2,      //TIM2 通用定时器
    HAL_TIM_3,      //TIM3 通用定时器
    HAL_TIM_4,      //TIM4 通用定时器
    HAL_TIM_5,      //TIM5 通用定时器
    HAL_TIM_6,      //TIM6 基本定时器
    HAL_TIM_7,      //TIM7 基本定时器(F103的资源到此)
    HAL_TIM_8,      //TIM9 通用定时器
    HAL_TIM_9,      //TIM10 通用定时器
    HAL_TIM_10,     //TIM11 通用定时器
    HAL_TIM_11,     //TIM12 通用定时器
    HAL_TIM_12,     //TIM13 通用定时器
    HAL_TIM_13,     //TIM14 通用定时器
    HAL_TIM_14,     //TIM15 通用定时器
    HAL_TIM_15,     //TIM16 通用定时器
    HAL_TIM_16,     //TIM17 通用定时器
    HAL_TIM_NODE_NUM,
    
}HAL_TIME_NODE;


//定时器节点定义
TIM_TypeDef * const TIM[HAL_TIM_NODE_NUM] = {   TIM1,TIM8, TIM2, TIM3, TIM4, TIM5, TIM6, TIM7, \
                                                TIM9, TIM10, TIM11, TIM12, TIM13, TIM14, TIM15, TIM16, TIM17};


/* ---定时器分频系数计算宏--- */
#define TIM_GET_PSC_BY_CNT_FRE(CntFre)            (TIMx_FCLK/(CntFre) - 1)   //通过计数频率计算预分频值
#define TIM_GET_PSC_BY_OP_FRE(OutFre, AutoLoad)   (TIM_GET_PSC_BY_CNT_FRE((OutFre) * (AutoLoad))) //通过输出频率计算预分频值(计数频率=输出频率*自动重装载值)


/**
  * @brief  开启定时器时钟.
  * @param  TIMx: where x can be 1 to 17 to select the TIM peripheral.
  * @retval None
  */
static void HAL_TIM_ClockEnable(uint8_t uTimeNode)
{
    TIM_TypeDef * const TIMx = TIM[uTimeNode];
    
    if (TIMx == TIM1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    }     
    else if (TIMx == TIM2)
    {
        RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    }
    else if (TIMx == TIM3)
    {
        RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    }
    else if (TIMx == TIM4)
    {
        RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    } 
    else if (TIMx == TIM5)
    {
        RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    } 
    else if (TIMx == TIM6)
    {
        RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    } 
    else if (TIMx == TIM7)
    {
        RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    } 
    else if (TIMx == TIM8)
    {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM8, ENABLE);
    }
    else if (TIMx == TIM9)
    {      
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM9, ENABLE);
    }  
    else if (TIMx == TIM10)
    {      
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM10, ENABLE);
    }  
    else if (TIMx == TIM11) 
    {     
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM11, ENABLE);
    }  
    else if (TIMx == TIM12)
    {      
        RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
    }  
    else if (TIMx == TIM13) 
    {       
        RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
    }
    else if (TIMx == TIM14) 
    {       
        RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
    }        
    else if (TIMx == TIM15)
    {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM15, ENABLE);
    } 
    else if (TIMx == TIM16)
    {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM16, ENABLE);
    } 
    else if (TIMx == TIM17)
    {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM17, ENABLE);
    }  
    else;
    
}


/*****************************************************************************
 * 延时功能定时器接口函数
 ****************************************************************************/

/**
  * @brief  定时器初始化
  * @param  uTimeNode 定时器节点
  * @retval None
  */
void HAL_TIM_DelayInit(uint8_t uTimeNode)
{
    HAL_TIM_ClockEnable(uTimeNode);
    
    //配置工作模式
    TIM[uTimeNode]->CR1  |=  TIM_CR1_ARPE;   //开影子
    TIM[uTimeNode]->CR1  |=  TIM_CR1_OPM;    //单脉冲模式
    TIM[uTimeNode]->CR1  &= ~TIM_CR1_URS;    //配置更新源
    TIM[uTimeNode]->CR1  &= ~TIM_CR1_UDIS;   //使能更新源
    
    //配置事件,中断
    TIM[uTimeNode]->EGR  |=  TIM_EGR_UG;    //开启更新事件
    TIM[uTimeNode]->DIER &= ~TIM_DIER_UDE;  //禁止更新DMA
    TIM[uTimeNode]->DIER &= ~TIM_DIER_UIE;  //禁止更新中断
    
    //关定时器
    TIM[uTimeNode]->CR1  &= ~TIM_CR1_CEN;  
    
}


/**
  * @brief  us级延时
  * @param  uTimeNode 定时器节点
  * @param  要延时的us数,取值范围为: 0xFFFF FFFF/0x18 ==> 约178S
  * @retval None
  * @note   调用本函数所延时的时间,会比预期的时间多3~4us,
  *         因为软件上的运算,寄存器读写等步骤占用了一定的时间
  */
void HAL_TIM_DelayUs(uint8_t uTimeNode, uint32_t ulUs)
{
    if (!ulUs) return;
    
    //配置时序参数
    TIM[uTimeNode]->PSC = TIM_GET_PSC_BY_CNT_FRE(1000000); //计数频率为1MHz
    TIM[uTimeNode]->ARR = ulUs;            //计数器每记1个数为1us
    TIM[uTimeNode]->EGR  |=  TIM_EGR_UG;  //给更新,刷新影子
    TIM[uTimeNode]->SR   &= ~TIM_SR_UIF;  //清标志位
    
    //开定时器
    TIM[uTimeNode]->CR1  |=  TIM_CR1_CEN;
    
    //等待计数完成
    while (!(TIM[uTimeNode]->SR & TIM_SR_UIF)); //等待计数完成
    
}


/**
  * @brief  ms级延时
  * @param  uTimeNode 定时器节点
  * @param  要延时的ms数,取值范围为: 0xFFFF FFFF/24000
  * @retval None
  */
void HAL_TIM_DelayMs(uint8_t uTimeNode, uint32_t ulMs)
{
    if (!ulMs) return;
    
    //配置时序参数
    TIM[uTimeNode]->PSC = TIM_GET_PSC_BY_CNT_FRE(2000);   //计数频率为2KHz
    TIM[uTimeNode]->ARR = 2 * ulMs;        //计数器每记2个数为1ms
    TIM[uTimeNode]->EGR  |=  TIM_EGR_UG;  //给更新,刷新影子
    TIM[uTimeNode]->SR   &= ~TIM_SR_UIF;  //清标志位
    
    //开定时器
    TIM[uTimeNode]->CR1  |=  TIM_CR1_CEN;
    
    //等待计数完成
    while (!(TIM[uTimeNode]->SR & TIM_SR_UIF)); //等待计数完成
}
