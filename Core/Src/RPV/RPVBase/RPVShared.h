#ifndef RPVSHARED_H_
#define RPVSHARED_H_

#include "stm32f4xx_hal.h"

enum RPVTypeClass{
	RPV_TYPE_ROVER = 0,
	RPV_TYPE_FIXED_WING = 1,
	RPV_TYPE_HELICOPTER = 2,
	RPV_TYPE_MULTI_ROTOR = 3
};

enum RPAVControlChannel{
	RPV_CTL_ROLL= 0,
	RPV_CTL_PITCH = 1,
	RPV_CTL_THROTTLE = 2,
	RPV_CTL_YAW = 3,
	RPV_CTL_AUTOPILOT = 4
};

enum RPVOutputChannelType{
	FULL_SQUARE_WAVE = 0,
	INVERTED_FULL_SQUARE_WAVE = 1,
	RC_RX_SQUARE_WAVE = 2
};

#define RPV_CTL_STEERING RPV_CTL_ROLL
#define RPV_CTL_GV_THROTTLE RPV_CTL_PITCH

struct RPVTypeConfiguration{
	RPVTypeClass VehicleClass;
};

struct RPVPWMOutputChannel{
	TIM_HandleTypeDef* Timer;
	uint32_t TimerChannel;
	uint32_t DutyCycle;
	RPVOutputChannelType OutputChannelType;
};

struct RPVInputCaptureChannel{
	TIM_HandleTypeDef* Timer;
	uint32_t TimerChannel;
	uint16_t GPIOPin;
	GPIO_TypeDef * GPIOPort;
	bool Invert = false;
	uint32_t LowTick = 0;
	uint32_t HighTick = 0;
};

#endif
