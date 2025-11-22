/*
 * AVManager.cpp
 *
 *  Created on: Oct 11, 2025
 *      Author: stuyvenstein
 */

#include "RPVManager.h"

#include "RxInputCapture.h"
#include "QuadDCMotorOutput.h"

RxInputCapture *inputCapture;


void RPVStartup(TIM_HandleTypeDef *htim2, TIM_HandleTypeDef *htim5, TIM_HandleTypeDef *htim3){
	inputCapture = new RxInputCapture(htim3);
	uint32_t * dma_buff = new uint32_t[5];
	HAL_TIM_IC_Start_DMA(htim2, TIM_CHANNEL_1, &dma_buff[0], 1);
	HAL_TIM_IC_Start_DMA(htim5, TIM_CHANNEL_1, &dma_buff[1], 1);
	HAL_TIM_IC_Start_DMA(htim5, TIM_CHANNEL_2, &dma_buff[2], 1);
	HAL_TIM_IC_Start_DMA(htim5, TIM_CHANNEL_3, &dma_buff[3], 1);
	HAL_TIM_IC_Start_DMA(htim5, TIM_CHANNEL_4, &dma_buff[4], 1);
}

void RPVTick(){
	//No need for this yet but implementing it anyway
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	inputCapture->InputCaptureCallback(htim);
}
