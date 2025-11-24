#ifndef RPVRCRXINPUTCAPTURE_H_
#define RPVRCRXINPUTCAPTURE_H_

#include "stm32f4xx_hal.h"
#include "RPVBase/RPVShared.h"

class RPVRcRXInputCapture {
public:
	RPVRcRXInputCapture(RPVTypeConfiguration*, RPVInputCaptureChannel*);
	virtual ~RPVRcRXInputCapture();
	void InputCaptureCallback(TIM_HandleTypeDef*);
private:
	RPVInputCaptureChannel* _inputCaptureChannels;
	RPVTypeConfiguration* _vehicleType;
};

#endif
