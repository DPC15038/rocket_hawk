# Simple demo of of the LSM303 accelerometer & magnetometer library.
# Will print the accelerometer & magnetometer X, Y, Z axis values every half
# second.
# Author: Tony DiCola
# License: Public Domain
import time
import sys
# Import the LSM303 module.
import Adafruit_LSM303


# Create a LSM303 instance.
lsm303 = Adafruit_LSM303.LSM303()

# Alternatively you can specify the I2C bus with a bus parameter:
#lsm303 = Adafruit_LSM303.LSM303(busum=2)

# print('Printing accelerometer & magnetometer X, Y, Z axis values, press Ctrl-C to quit...')
fo = open("/home/pi/rocket_hawk/logs/accelerometer_logs/accelerometer.txt", "a")
if len(sys.argv) > 1:
	seconds = [int(i) for i in (sys.argv[1:])][0]
else:
	seconds = 5
seconds = seconds * 10
for x in range(0, seconds):
    # Read the X, Y, Z axis acceleration values and print them.
    accel, mag = lsm303.read()
    # Grab the X, Y, Z components from the reading and print them out.
    accel_x, accel_y, accel_z = accel
    mag_x, mag_z, mag_y = mag
   # print('Accel X={0}, Accel Y={1}, Accel Z={2}'.format(
    #      accel_x, accel_y, accel_z))
    fo.write('Accel X={0}, Accel Y={1}, Accel Z={2}\n'.format(
          accel_x, accel_y, accel_z))

    # Wait quarter of a second and repeat.
    time.sleep(0.1)

fo.close()

