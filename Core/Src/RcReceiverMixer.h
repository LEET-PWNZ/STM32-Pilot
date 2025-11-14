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
	TIM_HandleTypeDef* Timer;
	uint32_t Channel;
	bool Invert = false;
	uint32_t LowTick = 0;
	uint32_t HighTick = 0;
	UAVControlChannel ControlChannel;
	GPIO_TypeDef* GpioPort;
	uint16_t GpioPin;
};

float GetRcChannelDutyFactor(uint32_t, InputCaptureChannel*);

class RcReceiverMixer {
public:
	//RcReceiverMixer(TIM_HandleTypeDef*, TIM_HandleTypeDef*, QuadDCMotorOutput*);
	RcReceiverMixer(InputCaptureChannel*, uint8_t, QuadDCMotorOutput*);
	//
	virtual ~RcReceiverMixer();
	void InputCaptureCallback(TIM_HandleTypeDef*);
private:
	uint32_t ** _timerDmaBuffer;
	InputCaptureChannel * _icChannels;
	uint8_t _icChannelCnt;
//	RcReceiverChannel _rollCapture;
//	RcReceiverChannel _pitchCapture;
//	RcReceiverChannel _throttleCapture;
//	RcReceiverChannel _yawCapture;
//	RcReceiverChannel _autoPilotCapture;
	QuadDCMotorOutput * _motorOutput;
};

#endif
