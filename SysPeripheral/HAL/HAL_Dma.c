/**
  ******************************************************************************
  * @file    hw_dma.h
  * @author  Duhanfeng
  * @version V1.0 寄存器版本
  * @date    2017.05.22
  * @brief   DMA驱动层实现文件
  ******************************************************************************
  * @attention
  * 
  * 
  * 
  ******************************************************************************
  */
  
  
/***********************************<INCLUDES>**********************************/
#include "hal_dma.h"
#include "chip.h"


typedef enum
{
    HAL_DMA1_CH0 = 0,
    HAL_DMA1_CH1,
    HAL_DMA1_CH2,
    HAL_DMA1_CH3,
    HAL_DMA1_CH4,
    HAL_DMA1_CH5,
    HAL_DMA1_CH6,
    HAL_DMA2_CH0,
    HAL_DMA2_CH1,
    HAL_DMA2_CH2,
    HAL_DMA2_CH3,
    HAL_DMA2_CH4,
    HAL_DMA_NODE_NUM,
    
}HAL_DMA_NODE;


static DMA_Channel_TypeDef * const DMA[HAL_DMA_NODE_NUM] = {DMA1_Channel1, DMA1_Channel2, DMA1_Channel3, DMA1_Channel4,
                                                               DMA1_Channel5, DMA1_Channel6, DMA1_Channel7, DMA2_Channel1,
                                                               DMA2_Channel2, DMA2_Channel3, DMA2_Channel4, DMA2_Channel5};

/**                                                            
  * @brief  外设传输模式配置                                   
  * @param  DMA[uDmaChannel] DMA通道标号                           
  * @param  PeriAddr 外设地址
  * @param  MemAddr 内存地址
  * @param  cDir 方向(外设到内存/内存到外设)
  * @retval None
  */
void HAL_DMA_PeriTransferConfig(uint8_t uDmaChannel, void *PeriAddr, void *MemAddr, uint8_t cDir)
{
    //开时钟
    //  RCC_EnableClock(DMA[uDmaChannel], 1);
    
    //配置模式
    DMA[uDmaChannel]->CCR &= ~DMA_CCR1_MEM2MEM; //非内存-内存模式
    DMA[uDmaChannel]->CCR &= ~DMA_CCR1_PL; 
    DMA[uDmaChannel]->CCR |=  DMA_CCR1_PL_0;    //中等优先级
    
    DMA[uDmaChannel]->CCR &= ~DMA_CCR1_MSIZE;   //内存:8位数据帧格式
    DMA[uDmaChannel]->CCR &= ~DMA_CCR1_PSIZE;   //外设:8位数据帧格式
    
    DMA[uDmaChannel]->CCR |=  DMA_CCR1_MINC;    //内存增量模式
    DMA[uDmaChannel]->CCR &= ~DMA_CCR1_PINC;    //外设非增量模式
    DMA[uDmaChannel]->CCR &= ~DMA_CCR1_CIRC;    //非循环模式
    
    //配置传输方向
    DMA[uDmaChannel]->CCR &= ~DMA_CCR1_DIR;
    DMA[uDmaChannel]->CCR |=  (cDir ? DMA_CCR1_DIR : 0);  //cDir: 0--外设到内存 1--内存到外设
    
    //配置外设中断
    DMA[uDmaChannel]->CCR &= ~DMA_CCR1_TEIE;    //关闭错误中断
    DMA[uDmaChannel]->CCR &= ~DMA_CCR1_HTIE;    //关闭半传输中断
    DMA[uDmaChannel]->CCR &= ~DMA_CCR1_TCIE;    //关闭传输完成中断
    
    //配置外设地址
    DMA[uDmaChannel]->CPAR = (uint32_t)PeriAddr;
    
    //配置内存地址
    DMA[uDmaChannel]->CMAR = (uint32_t)MemAddr;
    
    //关闭DMA
    DMA[uDmaChannel]->CCR &= ~DMA_CCR1_EN;
    
}



/**
  * @brief  外设传输模式配置
  * @param  DMA[uDmaChannel] DMA通道标号
  * @param  isEnable 1-开启DMA,0-关闭DMA
  * @retval None
  */
void DMAx_Enable(DMA_Channel_TypeDef *DMA[uDmaChannel], uint8_t isEnable)
{
    if (isEnable)
    {
        DMA[uDmaChannel]->CCR |=  DMA_CCR1_EN;
    }
    else 
    {
        DMA[uDmaChannel]->CCR &= ~DMA_CCR1_EN;
    }
    
}



/**
  * @brief  复位对应的通道的计数器
  * @param  DMA[uDmaChannel] DMA通道标号
  * @param  nCount 计数器的复位值
  * @retval None
  */
void DMAx_ResetCounter(DMA_Channel_TypeDef *DMA[uDmaChannel], uint16_t nCount)
{
    //关闭通道
    DMA[uDmaChannel]->CCR &= ~DMA_CCR1_EN;
    
    //配置发送数量
    DMA[uDmaChannel]->CNDTR = nCount;
    
    //开启通道
    DMA[uDmaChannel]->CCR |=  DMA_CCR1_EN;
    
}



/**
  * @brief  复位对应的通道的内存地址以及计数器
  * @param  DMA[uDmaChannel] DMA通道标号
  * @param  MemAddr 内存地址的复位值
  * @param  nCount 计数器的复位值
  * @retval None
  */
void DMAx_ResetMemAddrAndCounter(DMA_Channel_TypeDef *DMA[uDmaChannel], void *MemAddr, uint16_t nCount)
{
    //关闭通道
    DMA[uDmaChannel]->CCR &= ~DMA_CCR1_EN;
    
    //配置内存地址
    DMA[uDmaChannel]->CMAR = (uint32_t)MemAddr;
    
    //配置发送数量
    DMA[uDmaChannel]->CNDTR = nCount;
    
    //开启通道
    DMA[uDmaChannel]->CCR |=  DMA_CCR1_EN;
    
}



/**
  * @brief  外设中断配置
  * @param  DMA[uDmaChannel] DMA通道标号
  * @param  IRQ_Mask 对应中断的掩码
  * @retval None
  */
void DMAx_ITConfig(DMA_Channel_TypeDef *DMA[uDmaChannel], uint8_t IRQ_Mask)
{
    //关闭所有中断
    DMA[uDmaChannel]->CCR &= ~(DMA_CCR1_TCIE | DMA_CCR1_HTIE | DMA_CCR1_TEIE);
    
    //开启对应的中断
    DMA[uDmaChannel]->CCR |= (IRQ_Mask);
    
}



/**
  * @brief  设置传输数量
  * @param  DMA[uDmaChannel] DMA通道标号
  * @param  nCount 要设置的计数器的值
  * @retval None
  */
void DMAx_SetTransferCount(DMA_Channel_TypeDef *DMA[uDmaChannel], uint16_t nCount)
{
    DMA[uDmaChannel]->CNDTR = nCount;
    
}



/**
  * @brief  获取当前计数器的值
  * @param  DMA[uDmaChannel] DMA通道标号
  * @retval 当前计数器的值
  */
uint16_t DMAx_GetCurrentCount(DMA_Channel_TypeDef *DMA[uDmaChannel])
{
    
    return DMA[uDmaChannel]->CNDTR;
}



/**
  * @brief  配置外设地址
  * @param  DMA[uDmaChannel] DMA通道标号
  * @param  PeriAddr 外设地址
  * @retval None
  */
void DMAx_SetPeriAddr(DMA_Channel_TypeDef *DMA[uDmaChannel], void *PeriAddr)
{
    DMA[uDmaChannel]->CPAR = (uint32_t)PeriAddr;
    
}



/**
  * @brief  配置内存地址
  * @param  DMA[uDmaChannel] DMA通道标号
  * @param  MemAddr 内存地址
  * @retval None
  */
void DMAx_SetMemAddr(DMA_Channel_TypeDef *DMA[uDmaChannel], void *MemAddr)
{
    DMA[uDmaChannel]->CMAR = (uint32_t)MemAddr;
    
}



/**
  * @brief  获取DMA的状态
  * @param  DMAx DMA标号
  * @retval 当前DMA的状态
  */
uint32_t DMAx_GetITStatus(DMA_TypeDef *DMAx)
{
    
    return DMAx->ISR;
}



/**
  * @brief  清除对应的标志位
  * @param  DMAx DMA标号
  * @param  iMask 要清除的状态位的掩码
  * @retval None
  */
void DMAx_ClearITStatus(DMA_TypeDef *DMAx, uint32_t iMask)
{
    DMAx->IFCR = iMask;
    
}

