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

void C2CPPStartup(TIM_HandleTypeDef*t2, TIM_HandleTypeDef*t5,TIM_HandleTypeDef*t3);
void C2CPPLoop();

#ifdef __cplusplus
}
#endif

#endif /* SRC_UAVMIXER_UAVMIXER_H_ */
