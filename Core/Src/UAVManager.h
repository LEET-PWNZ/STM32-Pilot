/*
 * UAVMixer.h
 *
 *  Created on: Oct 11, 2025
 *      Author: stuyvenstein
 */

#ifndef UAVMIXER_H_
#define UAVMIXER_H_

#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void UAVStartup(TIM_HandleTypeDef*, TIM_HandleTypeDef*, TIM_HandleTypeDef*);
void UAVTick();

#ifdef __cplusplus
}
#endif

#endif /* SRC_UAVMIXER_UAVMIXER_H_ */
