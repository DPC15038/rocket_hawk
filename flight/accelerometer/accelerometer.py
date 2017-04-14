# Author: Tony DiCola
# https://github.com/adafruit/Adafruit_Python_LSM303/blob/master/examples/simpletest.py
# Modified for UML Rocket Club: David Connolly and Jacob Hempel
# License: Public Domain
import time
import sys
# Import the LSM303 module.
import Adafruit_LSM303


# Create a LSM303 instance.
lsm303 = Adafruit_LSM303.LSM303()
N = 10; # Number of samples per second
fo = open("/home/pi/rocket_hawk/logs/accelerometer_logs/accelerometer.txt", "a")
if len(sys.argv) > 1:  # If a command line argument is provided, use it
	seconds = [int(i) for i in (sys.argv[1:])][0]*10
else:  # else, default to 10 second intervals
	seconds = 10*N

duration = ((1/float(N)) - .0034) # Off set slightly to account for i2c bus delay
for x in range(0, seconds):
    accel, mag = lsm303.read()
    accel_x, accel_y, accel_z = accel
    fo.write('time = {0}, Accel X={1}, Y={2}, Z={3}\n'.format( int(time.time()),
    accel_x, accel_y, accel_z))
    time.sleep(duration)
fo.close()
