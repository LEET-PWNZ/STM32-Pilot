/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file         stm32f4xx_hal_msp.c
  * @brief        This file provides code for the MSP Initialization
  *               and de-Initialization codes.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */
extern DMA_HandleTypeDef hdma_tim2_ch1;

extern DMA_HandleTypeDef hdma_tim5_ch1;

extern DMA_HandleTypeDef hdma_tim5_ch2;

extern DMA_HandleTypeDef hdma_tim5_ch3_up;

extern DMA_HandleTypeDef hdma_tim5_ch4_trig;

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
                    /**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{

  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();

  /* System interrupt init*/

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
  * @brief RTC MSP Initialization
  * This function configures the hardware resources used in this example
  * @param hrtc: RTC handle pointer
  * @retval None
  */
void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(hrtc->Instance==RTC)
  {
    /* USER CODE BEGIN RTC_MspInit 0 */

    /* USER CODE END RTC_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_RTC_ENABLE();
    /* USER CODE BEGIN RTC_MspInit 1 */

    /* USER CODE END RTC_MspInit 1 */

  }

}

/**
  * @brief RTC MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param hrtc: RTC handle pointer
  * @retval None
  */
void HAL_RTC_MspDeInit(RTC_HandleTypeDef* hrtc)
{
  if(hrtc->Instance==RTC)
  {
    /* USER CODE BEGIN RTC_MspDeInit 0 */

    /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();
    /* USER CODE BEGIN RTC_MspDeInit 1 */

    /* USER CODE END RTC_MspDeInit 1 */
  }

}

/**
  * @brief TIM_IC MSP Initialization
  * This function configures the hardware resources used in this example
  * @param htim_ic: TIM_IC handle pointer
  * @retval None
  */
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef* htim_ic)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(htim_ic->Instance==TIM2)
  {
    /* USER CODE BEGIN TIM2_MspInit 0 */

    /* USER CODE END TIM2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM2 GPIO Configuration
    PA5     ------> TIM2_CH1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* TIM2 DMA Init */
    /* TIM2_CH1 Init */
    hdma_tim2_ch1.Instance = DMA1_Stream5;
    hdma_tim2_ch1.Init.Channel = DMA_CHANNEL_3;
    hdma_tim2_ch1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_tim2_ch1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim2_ch1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim2_ch1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_tim2_ch1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_tim2_ch1.Init.Mode = DMA_CIRCULAR;
    hdma_tim2_ch1.Init.Priority = DMA_PRIORITY_LOW;
    hdma_tim2_ch1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_tim2_ch1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(htim_ic,hdma[TIM_DMA_ID_CC1],hdma_tim2_ch1);

    /* USER CODE BEGIN TIM2_MspInit 1 */

    /* USER CODE END TIM2_MspInit 1 */
  }
  else if(htim_ic->Instance==TIM5)
  {
    /* USER CODE BEGIN TIM5_MspInit 0 */

    /* USER CODE END TIM5_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM5_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM5 GPIO Configuration
    PA0-WKUP     ------> TIM5_CH1
    PA1     ------> TIM5_CH2
    PA2     ------> TIM5_CH3
    PA3     ------> TIM5_CH4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* TIM5 DMA Init */
    /* TIM5_CH1 Init */
    hdma_tim5_ch1.Instance = DMA1_Stream2;
    hdma_tim5_ch1.Init.Channel = DMA_CHANNEL_6;
    hdma_tim5_ch1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_tim5_ch1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim5_ch1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim5_ch1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_tim5_ch1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_tim5_ch1.Init.Mode = DMA_CIRCULAR;
    hdma_tim5_ch1.Init.Priority = DMA_PRIORITY_LOW;
    hdma_tim5_ch1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_tim5_ch1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(htim_ic,hdma[TIM_DMA_ID_CC1],hdma_tim5_ch1);

    /* TIM5_CH2 Init */
    hdma_tim5_ch2.Instance = DMA1_Stream4;
    hdma_tim5_ch2.Init.Channel = DMA_CHANNEL_6;
    hdma_tim5_ch2.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_tim5_ch2.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim5_ch2.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim5_ch2.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_tim5_ch2.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_tim5_ch2.Init.Mode = DMA_CIRCULAR;
    hdma_tim5_ch2.Init.Priority = DMA_PRIORITY_LOW;
    hdma_tim5_ch2.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_tim5_ch2) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(htim_ic,hdma[TIM_DMA_ID_CC2],hdma_tim5_ch2);

    /* TIM5_CH3_UP Init */
    hdma_tim5_ch3_up.Instance = DMA1_Stream0;
    hdma_tim5_ch3_up.Init.Channel = DMA_CHANNEL_6;
    hdma_tim5_ch3_up.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_tim5_ch3_up.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim5_ch3_up.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim5_ch3_up.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_tim5_ch3_up.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_tim5_ch3_up.Init.Mode = DMA_CIRCULAR;
    hdma_tim5_ch3_up.Init.Priority = DMA_PRIORITY_LOW;
    hdma_tim5_ch3_up.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_tim5_ch3_up) != HAL_OK)
    {
      Error_Handler();
    }

    /* Several peripheral DMA handle pointers point to the same DMA handle.
     Be aware that there is only one stream to perform all the requested DMAs. */
    __HAL_LINKDMA(htim_ic,hdma[TIM_DMA_ID_CC3],hdma_tim5_ch3_up);
    __HAL_LINKDMA(htim_ic,hdma[TIM_DMA_ID_UPDATE],hdma_tim5_ch3_up);

    /* TIM5_CH4_TRIG Init */
    hdma_tim5_ch4_trig.Instance = DMA1_Stream1;
    hdma_tim5_ch4_trig.Init.Channel = DMA_CHANNEL_6;
    hdma_tim5_ch4_trig.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_tim5_ch4_trig.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim5_ch4_trig.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim5_ch4_trig.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_tim5_ch4_trig.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_tim5_ch4_trig.Init.Mode = DMA_CIRCULAR;
    hdma_tim5_ch4_trig.Init.Priority = DMA_PRIORITY_LOW;
    hdma_tim5_ch4_trig.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_tim5_ch4_trig) != HAL_OK)
    {
      Error_Handler();
    }

    /* Several peripheral DMA handle pointers point to the same DMA handle.
     Be aware that there is only one stream to perform all the requested DMAs. */
    __HAL_LINKDMA(htim_ic,hdma[TIM_DMA_ID_CC4],hdma_tim5_ch4_trig);
    __HAL_LINKDMA(htim_ic,hdma[TIM_DMA_ID_TRIGGER],hdma_tim5_ch4_trig);

    /* USER CODE BEGIN TIM5_MspInit 1 */

    /* USER CODE END TIM5_MspInit 1 */
  }

}

/**
  * @brief TIM_PWM MSP Initialization
  * This function configures the hardware resources used in this example
  * @param htim_pwm: TIM_PWM handle pointer
  * @retval None
  */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm)
{
  if(htim_pwm->Instance==TIM3)
  {
    /* USER CODE BEGIN TIM3_MspInit 0 */

    /* USER CODE END TIM3_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();
    /* USER CODE BEGIN TIM3_MspInit 1 */

    /* USER CODE END TIM3_MspInit 1 */

  }

}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(htim->Instance==TIM3)
  {
    /* USER CODE BEGIN TIM3_MspPostInit 0 */

    /* USER CODE END TIM3_MspPostInit 0 */

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM3 GPIO Configuration
    PA6     ------> TIM3_CH1
    PA7     ------> TIM3_CH2
    PB0     ------> TIM3_CH3
    PB1     ------> TIM3_CH4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USER CODE BEGIN TIM3_MspPostInit 1 */

    /* USER CODE END TIM3_MspPostInit 1 */
  }

}
/**
  * @brief TIM_IC MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param htim_ic: TIM_IC handle pointer
  * @retval None
  */
void HAL_TIM_IC_MspDeInit(TIM_HandleTypeDef* htim_ic)
{
  if(htim_ic->Instance==TIM2)
  {
    /* USER CODE BEGIN TIM2_MspDeInit 0 */

    /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();

    /**TIM2 GPIO Configuration
    PA5     ------> TIM2_CH1
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5);

    /* TIM2 DMA DeInit */
    HAL_DMA_DeInit(htim_ic->hdma[TIM_DMA_ID_CC1]);
    /* USER CODE BEGIN TIM2_MspDeInit 1 */

    /* USER CODE END TIM2_MspDeInit 1 */
  }
  else if(htim_ic->Instance==TIM5)
  {
    /* USER CODE BEGIN TIM5_MspDeInit 0 */

    /* USER CODE END TIM5_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM5_CLK_DISABLE();

    /**TIM5 GPIO Configuration
    PA0-WKUP     ------> TIM5_CH1
    PA1     ------> TIM5_CH2
    PA2     ------> TIM5_CH3
    PA3     ------> TIM5_CH4
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    /* TIM5 DMA DeInit */
    HAL_DMA_DeInit(htim_ic->hdma[TIM_DMA_ID_CC1]);
    HAL_DMA_DeInit(htim_ic->hdma[TIM_DMA_ID_CC2]);
    HAL_DMA_DeInit(htim_ic->hdma[TIM_DMA_ID_CC3]);
    HAL_DMA_DeInit(htim_ic->hdma[TIM_DMA_ID_UPDATE]);
    HAL_DMA_DeInit(htim_ic->hdma[TIM_DMA_ID_CC4]);
    HAL_DMA_DeInit(htim_ic->hdma[TIM_DMA_ID_TRIGGER]);
    /* USER CODE BEGIN TIM5_MspDeInit 1 */

    /* USER CODE END TIM5_MspDeInit 1 */
  }

}

/**
  * @brief TIM_PWM MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param htim_pwm: TIM_PWM handle pointer
  * @retval None
  */
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* htim_pwm)
{
  if(htim_pwm->Instance==TIM3)
  {
    /* USER CODE BEGIN TIM3_MspDeInit 0 */

    /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();
    /* USER CODE BEGIN TIM3_MspDeInit 1 */

    /* USER CODE END TIM3_MspDeInit 1 */
  }

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
