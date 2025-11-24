#include "C2CPP.h"

#include "RPV/RPVManager.h"
#include "RPV/RPVBase/RPVShared.h"

RPVManager * rpvMan;

void C2CPPStartup(TIM_HandleTypeDef *htim2, TIM_HandleTypeDef *htim5, TIM_HandleTypeDef *htim3){

	RPVPWMOutputChannel* outputChannels = new RPVPWMOutputChannel[4];
	RPVInputCaptureChannel* inputChannels = new RPVInputCaptureChannel[5];

	// Output
	// Front Left Motor
	outputChannels[0].Timer = htim3;
	outputChannels[0].TimerChannel = TIM_CHANNEL_1;
	outputChannels[0].OutputChannelType = RC_RX_SQUARE_WAVE;
	// Front Right Motor
	outputChannels[1].Timer = htim3;
	outputChannels[1].TimerChannel = TIM_CHANNEL_2;
	outputChannels[1].OutputChannelType = RC_RX_SQUARE_WAVE;
	// Rear Left Motor
	outputChannels[2].Timer = htim3;
	outputChannels[2].TimerChannel = TIM_CHANNEL_3;
	outputChannels[2].OutputChannelType = RC_RX_SQUARE_WAVE;
	// Rear Right Motor
	outputChannels[3].Timer = htim3;
	outputChannels[3].TimerChannel = TIM_CHANNEL_4;
	outputChannels[3].OutputChannelType = RC_RX_SQUARE_WAVE;

	// Input
	// Roll
	inputChannels[0].Timer = htim5;
	inputChannels[0].TimerChannel = TIM_CHANNEL_1;
	inputChannels[0].GPIOPort = GPIOA;
	inputChannels[0].GPIOPin = GPIO_PIN_0;
	// Pitch
	inputChannels[1].Timer = htim5;
	inputChannels[1].TimerChannel = TIM_CHANNEL_2;
	inputChannels[1].GPIOPort = GPIOA;
	inputChannels[1].GPIOPin = GPIO_PIN_1;
	// Throttle
	inputChannels[2].Timer = htim5;
	inputChannels[2].TimerChannel = TIM_CHANNEL_3;
	inputChannels[2].GPIOPort = GPIOA;
	inputChannels[2].GPIOPin = GPIO_PIN_2;
	// Yaw
	inputChannels[3].Timer = htim5;
	inputChannels[3].TimerChannel = TIM_CHANNEL_4;
	inputChannels[3].GPIOPort = GPIOA;
	inputChannels[3].GPIOPin = GPIO_PIN_3;
	// Autopilot
	inputChannels[4].Timer = htim2;
	inputChannels[4].TimerChannel = TIM_CHANNEL_1;
	inputChannels[4].GPIOPort = GPIOA;
	inputChannels[4].GPIOPin = GPIO_PIN_5;

	RPVTypeConfiguration *vehicleTypeInfo = new RPVTypeConfiguration();
	vehicleTypeInfo->VehicleClass = RPV_TYPE_MULTI_ROTOR;

	rpvMan = new RPVManager(vehicleTypeInfo, outputChannels, inputChannels);
}

void C2CPPLoop(){
	//No need for this yet but implementing it anyway
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	rpvMan->InputCaptureCallback(htim);
}
