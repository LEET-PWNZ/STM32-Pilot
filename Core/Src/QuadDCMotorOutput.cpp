/*
 * QuadDCMotorOutput.cpp
 *
 *  Created on: Oct 26, 2025
 *      Author: stuyvenstein
 */

#include "QuadDCMotorOutput.h"

QuadDCMotorOutput::QuadDCMotorOutput(TIM_HandleTypeDef *timer3) {
	_dutyCounterRange = timer3->Init.Period + 1;
	TIM3->CCR1 = 0;
	TIM3->CCR2 = 0;
	TIM3->CCR3 = 0;
	TIM3->CCR4 = 0;
	HAL_TIM_PWM_Start(timer3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(timer3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(timer3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(timer3, TIM_CHANNEL_4);

}

void QuadDCMotorOutput::UpdateInputDuty(float dutyCycle, UAVControlChannel inputChannel){
	float dutyDiff = 0.0f;
	switch (inputChannel) {
		case UAVC_NONE:
			break;
		case UAVC_LINEAR_PITCH:
			dutyDiff = GetDutyDifference(dutyCycle, _pitchUpdateDuty);
			if(dutyDiff >= 0.01f){
				_pitchUpdateDuty = dutyCycle;
				updateOutputDuty();
			}
			break;
		case UAVC_LINEAR_ROLL:
			dutyDiff = GetDutyDifference(dutyCycle, _rollUpdateDuty);
			if(dutyDiff >= 0.01f){
				_rollUpdateDuty = dutyCycle;
				updateOutputDuty();
			}
			break;
		case UAVC_LINEAR_THROTTLE:
			dutyDiff = GetDutyDifference(dutyCycle, _throttleUpdateDuty);
			if(dutyDiff >= 0.01f){
				_throttleUpdateDuty = dutyCycle;
				updateOutputDuty();
			}
			break;
		case UAVC_LINEAR_YAW:
			dutyDiff = GetDutyDifference(dutyCycle, _yawUpdateDuty);
			if(dutyDiff >= 0.01f){
				_yawUpdateDuty = dutyCycle;
				updateOutputDuty();
			}
			break;
		case UAVC_LINEAR_AUTOPILOT:
			dutyDiff = GetDutyDifference(dutyCycle, _autoPilotUpdateDuty);
			if(dutyDiff >= 0.01f){
				_autoPilotUpdateDuty = dutyCycle;
				//updateOutputDuty();
			}
			break;
	}
}

float GetDutyDifference(float newDuty, float oldDuty){
	float result = 0.0f;
	if(newDuty > oldDuty){
		result = newDuty - oldDuty;
	}else{
		result = oldDuty - newDuty;
	}
	return result;
}

void QuadDCMotorOutput::updateOutputDuty(){
	TIM3->CCR1 = (_dutyCounterRange * (_rollUpdateDuty / 100.0f)) - 1;
}

QuadDCMotorOutput::~QuadDCMotorOutput() {
	// TODO Auto-generated destructor stub
}

