# <ins>STM32 Pilot</ins>

STM32 Pilot is a Remote Vehicle Piloting tool, allowing remote vehicle operators to map, and (optionally) mix, one or more forms of input, to one or more forms of output. (Sensors, RC receivers, autopilots, gyros etc.)

The signal mixing provides a way for RC pilots with older radios to operate vehicles that their radios don't support natively, by doing the mixing for them on an STM32 (Eg. An airplane radio can be used to fly a quadcopter)

Using STM32 Pilot, a user would connect their RC receiver to the STM32's input channels, and then connect the STM32's output channels to your ESCs and / or servos.

The project is built using STM32 Cube IDE so the .ioc file and much of the boiler-plate code, is pre-configured to have multiple timers enabled for input capture and PWM output.
The current supported device is an STM32F401CCU6, and the core clock speed is configured at 72Mhz (because using 84Mhz does not allow use of the USB peripheral)

Core functionality will include:
- Switching vehicle control input source - from RC receiver to Autopilot and vice versa
- Switching vehicle control output destinations, or switching mixing methods on control outputs - For vehicles with multiple drive systems (air to ground transition, air to water transition, vtol to forward flight etc.)
- Mixing or mimicking the signal(s) of an RC receiver, sensor, or any other digital / analog device. (The vehicle type and control input configuration will dictate how the vehicle's control channels are mixed (if at all) before being output)
- The same methodology applies to peripherals that aren't used for the vehicle's control. One or more inputs can have their values replicated or transformed, and then be written to one or more outputs.
- Modularity - Signal mixers, input sources, and output destinations, should be user-programmable. That way, its easy to use the RPV system with a sensor, peripheral, vehicle, or radio that it does not support by default.


NOTE: At the time of writing, not all of the above features exist yet, but they will be implemented over time. This is just an overview of what the project is meant to achieve.
