#ifndef SRC_RPVMANAGER_H_
#define SRC_RPVMANAGER_H_

#include "RPVBase/RPVShared.h"
#include "RPVBase/RPVOutputSystem.h"
#include "RPVRcRXInputCapture.h"

class RPVManager {
public:
	RPVManager(RPVTypeConfiguration*, RPVPWMOutputChannel*, RPVInputCaptureChannel*);
	virtual ~RPVManager();
	void InputCaptureCallback(TIM_HandleTypeDef*);
private:
	RPVTypeConfiguration* _vehicleType;
	RPVOutputSystem * _outputSystem;
	RPVRcRXInputCapture * _inputSystem;
};

#endif
