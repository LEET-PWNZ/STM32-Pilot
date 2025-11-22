/*
 * AVManager.h
 *
 *  Created on: Oct 11, 2025
 *      Author: stuyvenstein
 */

#ifndef RPVMANAGER_H_
#define RPVMANAGER_H_

#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void RPVStartup(TIM_HandleTypeDef*t2, TIM_HandleTypeDef*t5,TIM_HandleTypeDef*t3);
void RPVTick();

#ifdef __cplusplus
}
#endif

#endif /* SRC_UAVMIXER_UAVMIXER_H_ */
