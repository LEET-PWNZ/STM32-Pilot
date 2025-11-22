STM32 Pilot is a hobby project. The idea is to bring multi-rotor support to older generations of RC radios that only have support for fixed-wing and / or helicopters.
It does this by using a aircraft profile where the 4 channels for throttle, yaw, pitch and roll are output individually and linear.
An STM32 then mixes the signals and outputs a square wave that can be directly fed into N type mosfets / NPN transistors.

Functionality will change in later versions and this will be updated accordingly.

The intention for this project is to be compatible with the signal output of all major brands of RC radios that do not have multi-rotor mixing, and to run on any STM32 Black Pill or Blue Pill board.
I'm also thinking of flight controller integration for autopilot.

The project is for STM32 Cube IDE.

At the time of writing, I have only used a Futaba T7C radio and an STM32F401 black pill board.
