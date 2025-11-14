/*
 * UAVMixer.cpp
 *
 *  Created on: Oct 11, 2025
 *      Author: stuyvenstein
 */

#include "UAVManager.h"

#include "RcReceiverMixer.h"
#include "QuadDCMotorOutput.h"

RcReceiverMixer *mixerInputCapture;
QuadDCMotorOutput *quadMotorOutput;
InputCaptureChannel * inputCaptureChannels;
InputCaptureChannel channel1 = {0};
InputCaptureChannel channel2 = {0};
InputCaptureChannel channel3 = {0};
InputCaptureChannel channel4 = {0};
InputCaptureChannel channel5 = {0};

void UAVStartup(TIM_HandleTypeDef *htim2, TIM_HandleTypeDef *htim5, TIM_HandleTypeDef * htim3){
	quadMotorOutput = new QuadDCMotorOutput(htim3);
	inputCaptureChannels = new InputCaptureChannel[5];

	channel1.Timer = htim5;
	channel1.Channel = TIM_CHANNEL_1;
	channel1.ControlChannel = UAVC_LINEAR_PITCH;
	channel1.GpioPin = GPIO_PIN_0;
	channel1.GpioPort = GPIOA;

	channel2.Timer = htim5;
	channel2.Channel = TIM_CHANNEL_2;
	channel2.ControlChannel = UAVC_LINEAR_ROLL;
	channel2.GpioPin = GPIO_PIN_1;
	channel2.GpioPort = GPIOA;

	channel3.Timer = htim5;
	channel3.Channel = TIM_CHANNEL_3;
	channel3.ControlChannel = UAVC_LINEAR_THROTTLE;
	channel3.GpioPin = GPIO_PIN_2;
	channel3.GpioPort = GPIOA;

	channel4.Timer = htim5;
	channel4.Channel = TIM_CHANNEL_4;
	channel4.ControlChannel = UAVC_LINEAR_YAW;
	channel4.GpioPin = GPIO_PIN_3;
	channel4.GpioPort = GPIOA;

	channel5.Timer = htim2;
	channel5.Channel = TIM_CHANNEL_1;
	channel5.ControlChannel = UAVC_LINEAR_AUTOPILOT;
	channel5.GpioPin = GPIO_PIN_5;
	channel5.GpioPort = GPIOA;

	inputCaptureChannels[0] = channel1;
	inputCaptureChannels[1] = channel2;
	inputCaptureChannels[2] = channel3;
	inputCaptureChannels[3] = channel4;
	inputCaptureChannels[4] = channel5;
	mixerInputCapture = new RcReceiverMixer(inputCaptureChannels, 5, quadMotorOutput);
	//mixerInputCapture = new RcReceiverMixer(htim2, htim5, quadMotorOutput);
}

void UAVTick(){
	//uint32_t sysTicks = HAL_GetTick();
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	mixerInputCapture->InputCaptureCallback(htim);
}
