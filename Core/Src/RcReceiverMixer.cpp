/*
 * MixerInputCapture.cpp
 *
 *  Created on: Oct 11, 2025
 *      Author: stuyvenstein
 */

#include "RcReceiverMixer.h"

//RcReceiverMixer::RcReceiverMixer(TIM_HandleTypeDef* timer2, TIM_HandleTypeDef* timer5, QuadDCMotorOutput* motorOutput) {
RcReceiverMixer::RcReceiverMixer(InputCaptureChannel* icChannels, uint8_t channelCount, QuadDCMotorOutput* motorOutput) {
	_motorOutput = motorOutput;
	_timerDmaBuffer = new uint32_t*[channelCount];
	_icChannelCnt = channelCount;
	_icChannels = icChannels;
	for (uint8_t i = 0; i < channelCount; ++i) {
		_timerDmaBuffer[i] = new uint32_t[1];
		HAL_TIM_IC_Start_DMA(icChannels[i].Timer, icChannels[i].Channel, _timerDmaBuffer[i], 1);
	}
//	HAL_TIM_IC_Start_DMA(timer2, TIM_CHANNEL_1, _timerDmaBuffer[0], 1);
//	HAL_TIM_IC_Start_DMA(timer5, TIM_CHANNEL_1, _timerDmaBuffer[1], 1);
//	HAL_TIM_IC_Start_DMA(timer5, TIM_CHANNEL_2, _timerDmaBuffer[2], 1);
//	HAL_TIM_IC_Start_DMA(timer5, TIM_CHANNEL_3, _timerDmaBuffer[3], 1);
//	HAL_TIM_IC_Start_DMA(timer5, TIM_CHANNEL_4, _timerDmaBuffer[4], 1);
}

void RcReceiverMixer::InputCaptureCallback(TIM_HandleTypeDef* timer){
		uint32_t tickVal = 0;
		GPIO_PinState pinState = GPIO_PIN_RESET;

		for (uint8_t i = 0; i < _icChannelCnt; ++i){
			if(timer->Instance == _icChannels[i].Timer->Instance){
				tickVal = HAL_TIM_ReadCapturedValue(timer, _icChannels[i].Channel);
				pinState = HAL_GPIO_ReadPin(_icChannels[i].GpioPort , _icChannels[i].GpioPin);
				if(pinState == GPIO_PIN_SET){
					float DutyCycle = GetRcChannelDutyFactor(tickVal, &_icChannels[i]);
					_motorOutput->UpdateInputDuty(DutyCycle, _icChannels[i].ControlChannel);
					_icChannels[i].HighTick = tickVal;
				}else{
					_icChannels[i].LowTick = tickVal;
				}
				break;
			}
		}
}

float GetRcChannelDutyFactor(uint32_t newTick, InputCaptureChannel * rcChannel){
	uint32_t pulseTicks = newTick - rcChannel->HighTick;
	uint32_t minDutyTicks = pulseTicks * RC_RX_DUTY_MIN;
	uint32_t dutyVarianceTicks = pulseTicks * RC_RX_DUTY_VARIANCE;
	uint32_t relevantDutyTicks = (rcChannel->LowTick - rcChannel->HighTick) - minDutyTicks;
	return std::clamp(((float)relevantDutyTicks / (float)dutyVarianceTicks) * 100.0f, 0.0f, 100.0f);
}

RcReceiverMixer::~RcReceiverMixer() {
	// TODO Auto-generated destructor stub
}

