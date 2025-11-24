#include "RPVOutputSystem.h"

RPVOutputSystem::RPVOutputSystem(RPVTypeConfiguration* vehicleType, RPVPWMOutputChannel* pwmOutputs) {
	_vehicleType = vehicleType;
	_outputChannels = pwmOutputs;

	HAL_TIM_PWM_Start(_outputChannels[0].Timer, _outputChannels[0].TimerChannel);
	HAL_TIM_PWM_Start(_outputChannels[1].Timer, _outputChannels[1].TimerChannel);
	HAL_TIM_PWM_Start(_outputChannels[2].Timer, _outputChannels[2].TimerChannel);
	HAL_TIM_PWM_Start(_outputChannels[3].Timer, _outputChannels[3].TimerChannel);

	for(uint8_t i = 0; i < 4; i++){
		switch (_outputChannels[i].TimerChannel) {
			case TIM_CHANNEL_1:
				_outputChannels[i].Timer->Instance->CCR1 = 0;
				break;
			case TIM_CHANNEL_2:
				_outputChannels[i].Timer->Instance->CCR2 = 0;
				break;
			case TIM_CHANNEL_3:
				_outputChannels[i].Timer->Instance->CCR3 = 0;
				break;
			case TIM_CHANNEL_4:
				_outputChannels[i].Timer->Instance->CCR4 = 0;
				break;
		}
	}
}

void RPVOutputSystem::UpdateOutputTicks(RPAVControlChannel controlChannel, uint32_t onPeroidTicks){
	switch (controlChannel) {
		case RPV_CTL_ROLL:

			break;
		case RPV_CTL_PITCH:

			break;
		case RPV_CTL_THROTTLE:

			break;
		case RPV_CTL_YAW:

			break;
		case RPV_CTL_AUTOPILOT:

			break;
	}
	updateOutputDuty();
}

void RPVOutputSystem::updateOutputDuty(){

}

RPVOutputSystem::~RPVOutputSystem() {
	// TODO Auto-generated destructor stub
}

