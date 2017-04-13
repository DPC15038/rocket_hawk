#!/bin/bash

timestamp() {
 date +"%F %T.%3N"
}

NUMBEROFCYCLES=5
pids1=""
pids2=""

echo Altimeter.txt:
stat -c %s /home/pi/rocket_hawk/logs/altimeters_logs/altimeter.txt 
echo Accelerometer.txt:
stat -c %s /home/pi/rocket_hawk/logs/accelerometer_logs/accelerometer.txt 
cd /home/pi/rocket_hawk/flight/altimeter/
for x in $(seq  $NUMBEROFCYCLES);
do
	ALT_SECONDS=10       
	/home/pi/rocket_hawk/flight/altimeter/bmp180 $ALT_SECONDS &
	pids1="$pids $!"
	ACC_SECONDS=10
	python /home/pi/rocket_hawk/flight/accelerometer/accelerometer.py $ACC_SECONDS &
	pids2="$pids $!"
done
wait $pids1 || $pids2
echo POST FLIGHT
echo Altimeter.txt:
stat -c %s /home/pi/rocket_hawk/logs/altimeters_logs/altimeter.txt
echo Accelerometer.txt:
stat -c %s /home/pi/rocket_hawk/logs/accelerometer_logs/accelerometer.txt
