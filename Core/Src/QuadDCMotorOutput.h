/*
 * QuadDCMotorOutput.h
 *
 *  Created on: Oct 26, 2025
 *      Author: stuyvenstein
 */

#ifndef QUADDCMOTOROUTPUT_H_
#define QUADDCMOTOROUTPUT_H_

#include "stm32f4xx_hal.h"

float GetDutyDifference(float, float);

enum UAVControlChannel{
	UAVC_NONE = 0,
	UAVC_LINEAR_PITCH = 1,
	UAVC_LINEAR_ROLL = 2,
	UAVC_LINEAR_THROTTLE = 3,
	UAVC_LINEAR_YAW = 4,
	UAVC_LINEAR_AUTOPILOT = 5
};

class QuadDCMotorOutput {
public:
	QuadDCMotorOutput(TIM_HandleTypeDef *);
	void UpdateInputDuty(float, UAVControlChannel);
	virtual ~QuadDCMotorOutput();
private:
	void updateOutputDuty();
	float _pitchUpdateDuty = 0.0f;
	float _rollUpdateDuty = 0.0f;
	float _throttleUpdateDuty = 0.0f;
	float _yawUpdateDuty = 0.0f;
	float _autoPilotUpdateDuty = 0.0f;
	uint32_t _dutyCounterRange;
};

#endif /* SRC_QUADDCMOTOROUTPUT_H_ */
