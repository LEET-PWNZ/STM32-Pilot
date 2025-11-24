#include "RPVRcRXInputCapture.h"

RPVRcRXInputCapture::RPVRcRXInputCapture(RemoteVehicleType vehicleType, RPVInputCaptureChannel* inputCaptureChannels) {
	_inputCaptureChannels = inputCaptureChannels;
	_vehicleType = vehicleType;
}

RPVRcRXInputCapture::~RPVRcRXInputCapture() {
	// TODO Auto-generated destructor stub
}

void RPVRcRXInputCapture::InputCaptureCallback(TIM_HandleTypeDef* timer){

}
