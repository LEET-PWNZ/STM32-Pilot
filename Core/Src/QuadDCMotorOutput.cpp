#include "QuadDCMotorOutput.h"

QuadDCMotorOutput::QuadDCMotorOutput(TIM_HandleTypeDef *timer3) {
	_dutyCounterRange = timer3->Init.Period + 1;
	TIM3->CCR1 = 0;
	TIM3->CCR2 = 0;
	TIM3->CCR3 = 0;
	TIM3->CCR4 = 0;
	HAL_TIM_PWM_Start(timer3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(timer3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(timer3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(timer3, TIM_CHANNEL_4);
}

void QuadDCMotorOutput::UpdateInputDuty(float dutyCycle, UAVControlChannel inputChannel){
	switch (inputChannel) {
		case UAVC_NONE:
			break;
		case UAVC_LINEAR_PITCH:
			_pitchUpdateDuty = dutyCycle;
			break;
		case UAVC_LINEAR_ROLL:
			_rollUpdateDuty = dutyCycle;
			break;
		case UAVC_LINEAR_THROTTLE:
			_throttleUpdateDuty = std::clamp((dutyCycle - _throttleBottomOffset), 0.0f, 100.0f);
			break;
		case UAVC_LINEAR_YAW:
			_yawUpdateDuty = dutyCycle;
			break;
		case UAVC_LINEAR_AUTOPILOT:
			_autoPilotUpdateDuty = dutyCycle;
			break;
	}
	updateOutputDuty();
}

//Ignoring autopilot for now
void QuadDCMotorOutput::updateOutputDuty(){

	// All rotors start with throttle
	if(_throttleUpdateDuty >= 1.0f){
		float frontLeftRotorDuty = _throttleUpdateDuty;
		float frontRightRotorDuty = _throttleUpdateDuty;
		float rearLeftRotorDuty = _throttleUpdateDuty;
		float rearRightRotorDuty = _throttleUpdateDuty;

		// Get pitch, yaw and roll offsets from center
	    float pitchCenterOffset =  _pitchUpdateDuty - 50.0f;
	    float rollCenterOffset =  _rollUpdateDuty - 50.0f;
	    float yawCenterOffset =  _yawUpdateDuty - 50.0f;


	    // Set the actual values we want to alter the throttle of each rotor with from yaw, pitch and roll
	    float pitchFrontDifference = -pitchCenterOffset * _pitchSensitivity;
	    float pitchRearDifference = pitchCenterOffset * _pitchSensitivity;

	    float rollLeftDifference = rollCenterOffset * _rollSensitivity;
	    float rollRightDifference = -rollCenterOffset * _rollSensitivity;

	    float yawLeftDifference = -yawCenterOffset * _yawSensitivity;
	    float yawRightDifference = yawCenterOffset * _yawSensitivity;

	    // Increment the throttle values using the calculated adjustments from other channels
	    frontLeftRotorDuty = frontLeftRotorDuty + yawLeftDifference;
	    frontRightRotorDuty = frontRightRotorDuty + yawRightDifference;
	    rearLeftRotorDuty = rearLeftRotorDuty + yawRightDifference;
	    rearRightRotorDuty = rearRightRotorDuty + yawLeftDifference;

	    frontLeftRotorDuty = frontLeftRotorDuty + rollLeftDifference;
	    frontRightRotorDuty = frontRightRotorDuty + rollRightDifference;
	    rearLeftRotorDuty = rearLeftRotorDuty + rollLeftDifference;
	    rearRightRotorDuty = rearRightRotorDuty + rollRightDifference;

	    frontLeftRotorDuty = frontLeftRotorDuty + pitchFrontDifference;
	    frontRightRotorDuty = frontRightRotorDuty + pitchFrontDifference;
	    rearLeftRotorDuty = rearLeftRotorDuty + pitchRearDifference;
	    rearRightRotorDuty = rearRightRotorDuty + pitchRearDifference;

	    // Output the final values as duty cycle on our timer
		TIM3->CCR1 = (_dutyCounterRange * (frontLeftRotorDuty / 100.0f)) - 1;
		TIM3->CCR2 = (_dutyCounterRange * (frontRightRotorDuty / 100.0f)) - 1;
		TIM3->CCR3 = (_dutyCounterRange * (rearLeftRotorDuty / 100.0f)) - 1;
		TIM3->CCR4 = (_dutyCounterRange * (rearRightRotorDuty / 100.0f)) - 1;
	}else{ // Dont do anything if there's not enough throttle
		TIM3->CCR1 = 0;
		TIM3->CCR2 = 0;
		TIM3->CCR3 = 0;
		TIM3->CCR4 = 0;
	}
}

QuadDCMotorOutput::~QuadDCMotorOutput() {
	// TODO Auto-generated destructor stub
}

