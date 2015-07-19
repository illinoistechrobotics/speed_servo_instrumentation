# speed_servo_instrumentation

In this repository is the periphial code I wrote while implemeting Fenrir's speed servos

There's an exploratory i2c test sketch in `i2c`

There's a sketch to easily set victor calibrations in `victor_calibrate`.
Victors are controlled by a PWM input. The limits of the PWM can be set by sweeping to both extremes, then returning to center while holding the calibrate button on the victor.

The last directory `pid_tuner` is essentially a serial->i2c bridge to enable the tuning of the controller from a laptop.
