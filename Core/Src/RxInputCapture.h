/*
 *
 *  Created on: Oct 11, 2025
 *      Author: stuyvenstein
 */

#ifndef RCRECEIVERMIXER_H_
#define RCRECEIVERMIXER_H_

#include "stm32f4xx_hal.h"
#include <algorithm>
#include "QuadDCMotorOutput.h"

#define RC_RX_DUTY_VARIANCE 0.069118f
#define RC_RX_DUTY_MIN 0.060432f

struct InputCaptureChannel{
public:
	bool Invert = false;
	uint32_t LowTick = 0;
	uint32_t HighTick = 0;
	UAVControlChannel ControlChannel;
};

float GetRcChannelDutyFactor(uint32_t, InputCaptureChannel*);

class RxInputCapture {
public:
	RxInputCapture(TIM_HandleTypeDef*);
	virtual ~RxInputCapture();
	void InputCaptureCallback(TIM_HandleTypeDef*);
private:
	InputCaptureChannel * _rollCapture;
	InputCaptureChannel * _pitchCapture;
	InputCaptureChannel * _throttleCapture;
	InputCaptureChannel * _yawCapture;
	InputCaptureChannel * _autoPilotCapture;
	QuadDCMotorOutput * _motorOutput;
};

#endif
