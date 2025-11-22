/*
 * MixerInputCapture.cpp
 *
 *  Created on: Oct 11, 2025
 *      Author: stuyvenstein
 */

#include "RxInputCapture.h"

RxInputCapture::RxInputCapture(TIM_HandleTypeDef* timer3) {
	_motorOutput = new QuadDCMotorOutput(timer3);

	_rollCapture = new InputCaptureChannel();
	_pitchCapture = new InputCaptureChannel();
	_throttleCapture = new InputCaptureChannel();
	_yawCapture = new InputCaptureChannel();
	_autoPilotCapture = new InputCaptureChannel();

	// Futaba T7C configuration
	_rollCapture->ControlChannel = UAVC_LINEAR_ROLL;
	_pitchCapture->ControlChannel = UAVC_LINEAR_PITCH;
	_pitchCapture->Invert = true;
	_throttleCapture->ControlChannel = UAVC_LINEAR_THROTTLE;
	_throttleCapture->Invert = true;
	_yawCapture->ControlChannel = UAVC_LINEAR_YAW;
	_autoPilotCapture->ControlChannel = UAVC_LINEAR_AUTOPILOT;
}

void RxInputCapture::InputCaptureCallback(TIM_HandleTypeDef* timer){
		uint32_t tickVal = 0;
		GPIO_PinState pinState = GPIO_PIN_RESET;
		switch (timer->Channel) {
			case HAL_TIM_ACTIVE_CHANNEL_1:
				tickVal = HAL_TIM_ReadCapturedValue(timer, TIM_CHANNEL_1);
				if(timer->Instance == TIM5){
					pinState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
					if(pinState == GPIO_PIN_SET){
						float dutyFactor = GetRcChannelDutyFactor(tickVal, _rollCapture);
						_motorOutput->UpdateInputDuty(dutyFactor, _rollCapture->ControlChannel);
						_rollCapture->HighTick = tickVal;
					}else{
						_rollCapture->LowTick = tickVal;
					}
				}
				// Not using autopilot atm
//				else{
//					pinState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
//					if(pinState == GPIO_PIN_SET){
//						float dutyFactor = GetRcChannelDutyFactor(tickVal, _autoPilotCapture);
//						_motorOutput->UpdateInputDuty(dutyFactor, _autoPilotCapture->ControlChannel);
//						_autoPilotCapture->HighTick = tickVal;
//					}else{
//						_autoPilotCapture->LowTick = tickVal;
//					}
//				}
				break;
			case HAL_TIM_ACTIVE_CHANNEL_2:
				tickVal = HAL_TIM_ReadCapturedValue(timer, TIM_CHANNEL_2);
				pinState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
				if(pinState == GPIO_PIN_SET){
					float dutyFactor = GetRcChannelDutyFactor(tickVal, _pitchCapture);
					_motorOutput->UpdateInputDuty(dutyFactor, _pitchCapture->ControlChannel);
					_pitchCapture->HighTick = tickVal;
				}else{
					_pitchCapture->LowTick = tickVal;
				}
				break;
			case HAL_TIM_ACTIVE_CHANNEL_3:
				tickVal = HAL_TIM_ReadCapturedValue(timer, TIM_CHANNEL_3);
				pinState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
				if(pinState == GPIO_PIN_SET){
					float dutyFactor = GetRcChannelDutyFactor(tickVal, _throttleCapture);
					_motorOutput->UpdateInputDuty(dutyFactor, _throttleCapture->ControlChannel);
					_throttleCapture->HighTick = tickVal;
				}else{
					_throttleCapture->LowTick = tickVal;
				}
				break;
			case HAL_TIM_ACTIVE_CHANNEL_4:
				tickVal = HAL_TIM_ReadCapturedValue(timer, TIM_CHANNEL_4);
				pinState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
				if(pinState == GPIO_PIN_SET){
					float dutyFactor = GetRcChannelDutyFactor(tickVal, _yawCapture);
					_motorOutput->UpdateInputDuty(dutyFactor, _yawCapture->ControlChannel);
					_yawCapture->HighTick = tickVal;
				}else{
					_yawCapture->LowTick = tickVal;
				}
				break;
			case HAL_TIM_ACTIVE_CHANNEL_CLEARED:
				break;
		}
}

float GetRcChannelDutyFactor(uint32_t newTick, InputCaptureChannel * rcChannel){
	uint32_t pulseTicks = newTick - rcChannel->HighTick;
	uint32_t minDutyTicks = pulseTicks * RC_RX_DUTY_MIN;
	uint32_t dutyVarianceTicks = pulseTicks * RC_RX_DUTY_VARIANCE;
	uint32_t relevantDutyTicks = (rcChannel->LowTick - rcChannel->HighTick) - minDutyTicks;
	return rcChannel->Invert ? -(std::clamp(((float)relevantDutyTicks / (float)dutyVarianceTicks) * 100.0f, 0.0f, 100.0f) - 100.0f)
								: std::clamp(((float)relevantDutyTicks / (float)dutyVarianceTicks) * 100.0f, 0.0f, 100.0f);
}

RxInputCapture::~RxInputCapture() {
	// TODO Auto-generated destructor stub
}

