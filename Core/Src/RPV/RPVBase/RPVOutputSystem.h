#ifndef RPVOUTPUTSYSTEM_H_
#define RPVOUTPUTSYSTEM_H_

#include "stm32f4xx_hal.h"
#include "RPVShared.h"

class RPVOutputSystem {
public:
	RPVOutputSystem(RemoteVehicleType, RPVPWMOutputChannel*);
	virtual ~RPVOutputSystem();
	void UpdateOutputTicks(RPAVControlChannel, uint32_t);
private:
	RemoteVehicleType _vehicleType;
	RPVPWMOutputChannel* _outputChannels;
	void updateOutputDuty();

};

#endif
