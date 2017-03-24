# BeagleBoneBlack-QuadCopter
This project hopes to achieve a flying BeagleBone, this project is a hobby. The build is custom (see installation section for a list of parts required).
The general goal is to have a Linux board (BeagleBone Black currently) attached to a Quadcopter frame and acting as it's flight controller.
The flight controller will maintain targets, the targets are currently set as part of testing but they could easily be modified to come from a controller.

## Current version : 0.1.3

## Project status

* Pitch and Roll are being controlled and are maintaining targets correctly.
* Tests are being done in a controlled environment with the Quadcopter tethered.
* PID results are looking ok but require further refinement.

## Current TODO's :

* Add 'maintain height' / 'move to target height' functionality utilising both the onboard Barometer and the Sonic Sensor.
* Add 'maintain heading' / 'move to target heading' functionality utilising the onboard magnetometer.
* Implement GPS.
* Add maintain location / move to location functionality utilising onboard GPS.
* (abstract) Add some sort of goals method, which allows for setting of targets.

## Setup

* [MAC](http://gnuarmeclipse.github.io/toolchain/install/#macos) - Setting up an ARM toolchain on a MAC
* [Linux](http://gnuarmeclipse.github.io/toolchain/install/#gnulinux) - Setting up an ARM toolchain on Linux
* [Windows](http://gnuarmeclipse.github.io/toolchain/install/#windows) - Setting up an ARM toolchain using Windows

Next :

1. Fork the project.
2. git clone https://github.com/YOUR-USERNAME/BeagleBoneBlack-QuadCopter
3. Create a samba connection to your beaglebone
4. Compile the program locally using your arm cross compiler
5. Upload the binary file to your beagle bone
6. Run chmod go+x on the file
7. Run ./[binary_file_name]

Nothing should happen - unless you have your beaglebone connected to all the correct sensors and motors.

## Requirements

1. BeagleBone Black
2. [10 DOF IMU Breakout Board](https://www.adafruit.com/products/1604)
  * L3GD20H 3-axis gyroscope: ±250, ±500, or ±2000 degree-per-second scale
  * LSM303 3-axis compass: ±1.3 to ±8.1 gauss magnetic field scale
  * LSM303 3-axis accelerometer: ±2g/±4g/±8g/±16g selectable scale
  * BMP180 barometric pressure/temperature: -40 to 85 °C, 300 - 1100hPa range, 0.17m resolution
3. [MaxBotix UltraSonic RangeFinder - LV-EZ1](https://www.adafruit.com/products/172)  
4. [Recommended : DJI Frame Kit](http://www.dji.com/flame-wheel-arf)

## Contributing
These projects have a tendency to grow big quite quickly - help is appreciated.

1. Fork the project.
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request.

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [C++](http://www.cplusplus.com)
* [I2C C++ Library](https://github.com/mbircohoakeels/BeagleBone-I2C)
* [LSM303DLHC C++ Library](https://github.com/mbircohoakeels/BeagleBone-LSM303DLHC)
* [Analog C++ Library](https://github.com/mbircohoakeels/BeagleBone-Analog)
* [PWM C++ Library](https://github.com/mbircohoakeels/BeagleBone-PWM)
* [L3GD20H C++ Library](https://github.com/mbircohoakeels/BeagleBoneBlack-L3GD20H)

## Versioning

I use [SemVer](http://semver.org/) for versioning.

## Authors

* **Michael Brookes** - *Initial work* - [MBircohoakeels](https://github.com/mbircohoakeels)

## License

This project is licensed under the GNU General Public License - see the [GNU License](http://www.gnu.org/licenses/) website for details.

## Acknowledgments

* http://www.tkjelectronics.com               - Kalman Filter
* https://gist.github.com/bradley219/5373998  - PID Algorithm
* https://www.adafruit.com                    - Electronic Sensors
* https://ie.farnell.com                      - Electronic Equipment
