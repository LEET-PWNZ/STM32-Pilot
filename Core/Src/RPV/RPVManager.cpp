#include "RPVManager.h"

RPVManager::RPVManager(RPVTypeConfiguration* vehicleType, RPVPWMOutputChannel* outputChannels, RPVInputCaptureChannel* inputChannels) {
	_vehicleType = vehicleType;
	_outputSystem = new RPVOutputSystem(vehicleType, outputChannels);
	_inputSystem = new RPVRcRXInputCapture(vehicleType, inputChannels);
}

RPVManager::~RPVManager() {
	// TODO Auto-generated destructor stub
}

void RPVManager::InputCaptureCallback(TIM_HandleTypeDef* timer){
	_inputSystem->InputCaptureCallback(timer);
}
