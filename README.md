# Lathe Electronic Gearbox

Welcome to the Lathe Electronic Gearbox repository. This project is intended for adding an electronic gearbox to all those small metal lathes with a painful gear change for the longitudinal carriage. The goal of the project is give the lathe's operator the ability to change the gear ratio for the longitudinal carriage in a fast, precise and confortable way. 

# Features

The project has the following features:

 - Presetted gear ratios (bunch of metric and imperial standard screw ratios).
 - RPM count, and detection of the rotation direction.
 - Custom gear ratios (from 0.000 to 9.998mm), in steps of 0.002mm's.
 - Configurable for your encoder and motor.
 - Security EndStop, for avoiding crashes with the headstock.
 - Engage in direct and inverted mode (for left-handed screws, for example).
 - ESP32 Compatible.

# Boards

The project has the following compatibility with microcontrollers:
| Microcontroller / Board | Status |
|--|--|
| ESP32 - WROOM32 | 100% Compatible |
| Mega2560 - RAMPS 1.4 | Deprecated |

# What do you need
You will need some components in order to start working with LEG:

- ESP32 WROOM
- RepRapDiscount Full Graphic Smart Controller (128x64)
- Incremental encoder (A, B, Vcc, GND)
- Stepper motor (like Nema 23 or similar) (you can use a closed loop kit with it's driver)
- Stepper motor controller (A4988, DRV8825, TB6600, DM542...) 
- NC Endstop for security