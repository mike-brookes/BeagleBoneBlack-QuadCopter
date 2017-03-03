#=============================================================================
# target rules for targets named QuadroCopter

Lib/analogBase/analogBase.o: Lib/analogBase/analogBase.cpp.o

.PHONY : Lib/analogBase/analogBase.o

# target to build an object file
Lib/analogBase/analogBase.cpp.o:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/analogBase/analogBase.cpp.o
.PHONY : Lib/analogBase/analogBase.cpp.o

Lib/analogBase/analogBase.i: Lib/analogBase/analogBase.cpp.i

.PHONY : Lib/analogBase/analogBase.i

# target to preprocess a source file
Lib/analogBase/analogBase.cpp.i:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/analogBase/analogBase.cpp.i
.PHONY : Lib/analogBase/analogBase.cpp.i

Lib/analogBase/analogBase.s: Lib/analogBase/analogBase.cpp.s

.PHONY : Lib/analogBase/analogBase.s

# target to generate assembly for a file
Lib/analogBase/analogBase.cpp.s:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/analogBase/analogBase.cpp.s
.PHONY : Lib/analogBase/analogBase.cpp.s

Lib/I2C/i2cDevice.o: Lib/I2C/i2cDevice.cpp.o

.PHONY : Lib/I2C/i2cDevice.o

# target to build an object file
Lib/I2C/i2cDevice.cpp.o:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/I2C/i2cDevice.cpp.o
.PHONY : Lib/I2C/i2cDevice.cpp.o

Lib/I2C/i2cDevice.i: Lib/I2C/i2cDevice.cpp.i

.PHONY : Lib/I2C/i2cDevice.i

# target to preprocess a source file
Lib/I2C/i2cDevice.cpp.i:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/I2C/i2cDevice.cpp.i
.PHONY : Lib/I2C/i2cDevice.cpp.i

Lib/I2C/i2cDevice.s: Lib/I2C/i2cDevice.cpp.s

.PHONY : Lib/I2C/i2cDevice.s

# target to generate assembly for a file
Lib/I2C/i2cDevice.cpp.s:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/I2C/i2cDevice.cpp.s
.PHONY : Lib/I2C/i2cDevice.cpp.s

Lib/LSM303/accelerometer/LSM303Accelerometer.o: Lib/LSM303/accelerometer/LSM303Accelerometer.cpp.o

.PHONY : Lib/LSM303/accelerometer/LSM303Accelerometer.o

# target to build an object file
Lib/LSM303/accelerometer/LSM303Accelerometer.cpp.o:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/LSM303/accelerometer/LSM303Accelerometer.cpp.o
.PHONY : Lib/LSM303/accelerometer/LSM303Accelerometer.cpp.o

Lib/LSM303/accelerometer/LSM303Accelerometer.i: Lib/LSM303/accelerometer/LSM303Accelerometer.cpp.i

.PHONY : Lib/LSM303/accelerometer/LSM303Accelerometer.i

# target to preprocess a source file
Lib/LSM303/accelerometer/LSM303Accelerometer.cpp.i:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/LSM303/accelerometer/LSM303Accelerometer.cpp.i
.PHONY : Lib/LSM303/accelerometer/LSM303Accelerometer.cpp.i

Lib/LSM303/accelerometer/LSM303Accelerometer.s: Lib/LSM303/accelerometer/LSM303Accelerometer.cpp.s

.PHONY : Lib/LSM303/accelerometer/LSM303Accelerometer.s

# target to generate assembly for a file
Lib/LSM303/accelerometer/LSM303Accelerometer.cpp.s:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/LSM303/accelerometer/LSM303Accelerometer.cpp.s
.PHONY : Lib/LSM303/accelerometer/LSM303Accelerometer.cpp.s

Lib/LSM303/LSM303DLHC.o: Lib/LSM303/LSM303DLHC.cpp.o

.PHONY : Lib/LSM303/LSM303DLHC.o

# target to build an object file
Lib/LSM303/LSM303DLHC.cpp.o:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/LSM303/LSM303DLHC.cpp.o
.PHONY : Lib/LSM303/LSM303DLHC.cpp.o

Lib/LSM303/LSM303DLHC.i: Lib/LSM303/LSM303DLHC.cpp.i

.PHONY : Lib/LSM303/LSM303DLHC.i

# target to preprocess a source file
Lib/LSM303/LSM303DLHC.cpp.i:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/LSM303/LSM303DLHC.cpp.i
.PHONY : Lib/LSM303/LSM303DLHC.cpp.i

Lib/LSM303/LSM303DLHC.s: Lib/LSM303/LSM303DLHC.cpp.s

.PHONY : Lib/LSM303/LSM303DLHC.s

# target to generate assembly for a file
Lib/LSM303/LSM303DLHC.cpp.s:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/LSM303/LSM303DLHC.cpp.s
.PHONY : Lib/LSM303/LSM303DLHC.cpp.s

Lib/LSM303/magnetometer/LSM303Magnetometer.o: Lib/LSM303/magnetometer/LSM303Magnetometer.cpp.o

.PHONY : Lib/LSM303/magnetometer/LSM303Magnetometer.o

# target to build an object file
Lib/LSM303/magnetometer/LSM303Magnetometer.cpp.o:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/LSM303/magnetometer/LSM303Magnetometer.cpp.o
.PHONY : Lib/LSM303/magnetometer/LSM303Magnetometer.cpp.o

Lib/LSM303/magnetometer/LSM303Magnetometer.i: Lib/LSM303/magnetometer/LSM303Magnetometer.cpp.i

.PHONY : Lib/LSM303/magnetometer/LSM303Magnetometer.i

# target to preprocess a source file
Lib/LSM303/magnetometer/LSM303Magnetometer.cpp.i:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/LSM303/magnetometer/LSM303Magnetometer.cpp.i
.PHONY : Lib/LSM303/magnetometer/LSM303Magnetometer.cpp.i

Lib/LSM303/magnetometer/LSM303Magnetometer.s: Lib/LSM303/magnetometer/LSM303Magnetometer.cpp.s

.PHONY : Lib/LSM303/magnetometer/LSM303Magnetometer.s

# target to generate assembly for a file
Lib/LSM303/magnetometer/LSM303Magnetometer.cpp.s:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/LSM303/magnetometer/LSM303Magnetometer.cpp.s
.PHONY : Lib/LSM303/magnetometer/LSM303Magnetometer.cpp.s

Lib/LVMaxSonarEZ/LVMaxSonarEZ.o: Lib/LVMaxSonarEZ/LVMaxSonarEZ.cpp.o

.PHONY : Lib/LVMaxSonarEZ/LVMaxSonarEZ.o

# target to build an object file
Lib/LVMaxSonarEZ/LVMaxSonarEZ.cpp.o:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/LVMaxSonarEZ/LVMaxSonarEZ.cpp.o
.PHONY : Lib/LVMaxSonarEZ/LVMaxSonarEZ.cpp.o

Lib/LVMaxSonarEZ/LVMaxSonarEZ.i: Lib/LVMaxSonarEZ/LVMaxSonarEZ.cpp.i

.PHONY : Lib/LVMaxSonarEZ/LVMaxSonarEZ.i

# target to preprocess a source file
Lib/LVMaxSonarEZ/LVMaxSonarEZ.cpp.i:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/LVMaxSonarEZ/LVMaxSonarEZ.cpp.i
.PHONY : Lib/LVMaxSonarEZ/LVMaxSonarEZ.cpp.i

Lib/LVMaxSonarEZ/LVMaxSonarEZ.s: Lib/LVMaxSonarEZ/LVMaxSonarEZ.cpp.s

.PHONY : Lib/LVMaxSonarEZ/LVMaxSonarEZ.s

# target to generate assembly for a file
Lib/LVMaxSonarEZ/LVMaxSonarEZ.cpp.s:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/LVMaxSonarEZ/LVMaxSonarEZ.cpp.s
.PHONY : Lib/LVMaxSonarEZ/LVMaxSonarEZ.cpp.s

Lib/motors/dji_2212/dji_2212.o: Lib/motors/dji_2212/dji_2212.cpp.o

.PHONY : Lib/motors/dji_2212/dji_2212.o

# target to build an object file
Lib/motors/dji_2212/dji_2212.cpp.o:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/motors/dji_2212/dji_2212.cpp.o
.PHONY : Lib/motors/dji_2212/dji_2212.cpp.o

Lib/motors/dji_2212/dji_2212.i: Lib/motors/dji_2212/dji_2212.cpp.i

.PHONY : Lib/motors/dji_2212/dji_2212.i

# target to preprocess a source file
Lib/motors/dji_2212/dji_2212.cpp.i:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/motors/dji_2212/dji_2212.cpp.i
.PHONY : Lib/motors/dji_2212/dji_2212.cpp.i

Lib/motors/dji_2212/dji_2212.s: Lib/motors/dji_2212/dji_2212.cpp.s

.PHONY : Lib/motors/dji_2212/dji_2212.s

# target to generate assembly for a file
Lib/motors/dji_2212/dji_2212.cpp.s:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/motors/dji_2212/dji_2212.cpp.s
.PHONY : Lib/motors/dji_2212/dji_2212.cpp.s

Lib/motors/motors.o: Lib/motors/motors.cpp.o

.PHONY : Lib/motors/motors.o

# target to build an object file
Lib/motors/motors.cpp.o:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/motors/motors.cpp.o
.PHONY : Lib/motors/motors.cpp.o

Lib/motors/motors.i: Lib/motors/motors.cpp.i

.PHONY : Lib/motors/motors.i

# target to preprocess a source file
Lib/motors/motors.cpp.i:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/motors/motors.cpp.i
.PHONY : Lib/motors/motors.cpp.i

Lib/motors/motors.s: Lib/motors/motors.cpp.s

.PHONY : Lib/motors/motors.s

# target to generate assembly for a file
Lib/motors/motors.cpp.s:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/motors/motors.cpp.s
.PHONY : Lib/motors/motors.cpp.s

Lib/overlayBase/analogBase/analogOverlay.o: Lib/overlayBase/analogBase/analogOverlay.cpp.o

.PHONY : Lib/overlayBase/analogBase/analogOverlay.o

# target to build an object file
Lib/overlayBase/analogBase/analogOverlay.cpp.o:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/overlayBase/analogBase/analogOverlay.cpp.o
.PHONY : Lib/overlayBase/analogBase/analogOverlay.cpp.o

Lib/overlayBase/analogBase/analogOverlay.i: Lib/overlayBase/analogBase/analogOverlay.cpp.i

.PHONY : Lib/overlayBase/analogBase/analogOverlay.i

# target to preprocess a source file
Lib/overlayBase/analogBase/analogOverlay.cpp.i:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/overlayBase/analogBase/analogOverlay.cpp.i
.PHONY : Lib/overlayBase/analogBase/analogOverlay.cpp.i

Lib/overlayBase/analogBase/analogOverlay.s: Lib/overlayBase/analogBase/analogOverlay.cpp.s

.PHONY : Lib/overlayBase/analogBase/analogOverlay.s

# target to generate assembly for a file
Lib/overlayBase/analogBase/analogOverlay.cpp.s:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/overlayBase/analogBase/analogOverlay.cpp.s
.PHONY : Lib/overlayBase/analogBase/analogOverlay.cpp.s

Lib/overlayBase/PWM/pwmOverlay.o: Lib/overlayBase/PWM/pwmOverlay.cpp.o

.PHONY : Lib/overlayBase/PWM/pwmOverlay.o

# target to build an object file
Lib/overlayBase/PWM/pwmOverlay.cpp.o:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/overlayBase/PWM/pwmOverlay.cpp.o
.PHONY : Lib/overlayBase/PWM/pwmOverlay.cpp.o

Lib/overlayBase/PWM/pwmOverlay.i: Lib/overlayBase/PWM/pwmOverlay.cpp.i

.PHONY : Lib/overlayBase/PWM/pwmOverlay.i

# target to preprocess a source file
Lib/overlayBase/PWM/pwmOverlay.cpp.i:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/overlayBase/PWM/pwmOverlay.cpp.i
.PHONY : Lib/overlayBase/PWM/pwmOverlay.cpp.i

Lib/overlayBase/PWM/pwmOverlay.s: Lib/overlayBase/PWM/pwmOverlay.cpp.s

.PHONY : Lib/overlayBase/PWM/pwmOverlay.s

# target to generate assembly for a file
Lib/overlayBase/PWM/pwmOverlay.cpp.s:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/overlayBase/PWM/pwmOverlay.cpp.s
.PHONY : Lib/overlayBase/PWM/pwmOverlay.cpp.s

Lib/overlayBase/PWM/pinOverlay.o: Lib/overlayBase/PWM/pinOverlay.cpp.o

.PHONY : Lib/overlayBase/PWM/pinOverlay.o

# target to build an object file
Lib/overlayBase/PWM/pinOverlay.cpp.o:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/overlayBase/PWM/pinOverlay.cpp.o
.PHONY : Lib/overlayBase/PWM/pinOverlay.cpp.o

Lib/overlayBase/PWM/pinOverlay.i: Lib/overlayBase/PWM/pinOverlay.cpp.i

.PHONY : Lib/overlayBase/PWM/pinOverlay.i

# target to preprocess a source file
Lib/overlayBase/PWM/pinOverlay.cpp.i:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/overlayBase/PWM/pinOverlay.cpp.i
.PHONY : Lib/overlayBase/PWM/pinOverlay.cpp.i

Lib/overlayBase/PWM/pinOverlay.s: Lib/overlayBase/PWM/pinOverlay.cpp.s

.PHONY : Lib/overlayBase/PWM/pinOverlay.s

# target to generate assembly for a file
Lib/overlayBase/PWM/pinOverlay.cpp.s:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/overlayBase/PWM/pinOverlay.cpp.s
.PHONY : Lib/overlayBase/PWM/pinOverlay.cpp.s

Lib/overlayBase/overlayBase.o: Lib/overlayBase/overlayBase.cpp.o

.PHONY : Lib/overlayBase/overlayBase.o

# target to build an object file
Lib/overlayBase/overlayBase.cpp.o:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/overlayBase/overlayBase.cpp.o
.PHONY : Lib/overlayBase/overlayBase.cpp.o

Lib/overlayBase/overlayBase.i: Lib/overlayBase/overlayBase.cpp.i

.PHONY : Lib/overlayBase/overlayBase.i

# target to preprocess a source file
Lib/overlayBase/overlayBase.cpp.i:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/overlayBase/overlayBase.cpp.i
.PHONY : Lib/overlayBase/overlayBase.cpp.i

Lib/overlayBase/overlayBase.s: Lib/overlayBase/overlayBase.cpp.s

.PHONY : Lib/overlayBase/overlayBase.s

# target to generate assembly for a file
Lib/overlayBase/overlayBase.cpp.s:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/overlayBase/overlayBase.cpp.s
.PHONY : Lib/overlayBase/overlayBase.cpp.s

Lib/PWM/pwmDevice.o: Lib/PWM/pwmDevice.cpp.o

.PHONY : Lib/PWM/pwmDevice.o

# target to build an object file
Lib/PWM/pwmDevice.cpp.o:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/PWM/pwmDevice.cpp.o
.PHONY : Lib/PWM/pwmDevice.cpp.o

Lib/PWM/pwmDevice.i: Lib/PWM/pwmDevice.cpp.i

.PHONY : Lib/PWM/pwmDevice.i

# target to preprocess a source file
Lib/PWM/pwmDevice.cpp.i:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/PWM/pwmDevice.cpp.i
.PHONY : Lib/PWM/pwmDevice.cpp.i

Lib/PWM/pwmDevice.s: Lib/PWM/pwmDevice.cpp.s

.PHONY : Lib/PWM/pwmDevice.s

# target to generate assembly for a file
Lib/PWM/pwmDevice.cpp.s:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/Lib/PWM/pwmDevice.cpp.s
.PHONY : Lib/PWM/pwmDevice.cpp.s

QuadroCopter.o: QuadroCopter.cpp.o

.PHONY : QuadroCopter.o

# target to build an object file
QuadroCopter.cpp.o:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/QuadroCopter.cpp.o
.PHONY : QuadroCopter.cpp.o

QuadroCopter.i: QuadroCopter.cpp.i

.PHONY : QuadroCopter.i

# target to preprocess a source file
QuadroCopter.cpp.i:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/QuadroCopter.cpp.i
.PHONY : QuadroCopter.cpp.i

QuadroCopter.s: QuadroCopter.cpp.s

.PHONY : QuadroCopter.s

# target to generate assembly for a file
QuadroCopter.cpp.s:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/QuadroCopter.cpp.s
.PHONY : QuadroCopter.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f Src/QuadroCopter.dir/build.make Src/QuadroCopter.dir/main.cpp.s
.PHONY : main.cpp.s
