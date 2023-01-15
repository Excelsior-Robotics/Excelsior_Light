# Excelsior_Light
<img src="Logo/Logo_small.jpg" alt="Logo" width="200"/>

## Excelsior_Light - an Arduino library to enable easy use of the Excelsior-Lightsensor
[![version](https://badgen.net/github/release/Excelsior-Robotics/Excelsior_Light)](https://github.com/Excelsior-Robotics/Excelsior_Light/releases)
### Version 1.0.0
- Added the basic and the percentual reading of the sensor with the possible colors being: (White, Red, Green, Blue, Cyan, Magenta, Yellow)
### Version 1.0.1
- Added Basic example
- Fixed Bugs in read and the constructor
### Version 1.0.2
- Added readRGB and readHSV to enable the use of any color as the color of the LED
- Added the ability to get dynamic percentage values for custom colors by calculating the next Triad along the color wheel
### Version 1.0.3
- Removed readHSV in favour of readHue, since there is no point in not reading at full brightness
- Bug Fixes