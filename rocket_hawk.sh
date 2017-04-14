#/bin/bash

timestamp() {
 date +"%F %T.%3N"
}

picamera() {
  raspivid -t 10000 -w 1920 -h 1080 -fps 30 -b 1200000 -p 0,0,1920,1080 -o pivideo.h264

  MP4Box -add pivideo.h264 pivideo.mp4

  rm pivideo.h264
}

NUMBEROFCYCLES=5
pids=""

echo Altimeter.txt:
stat -c %s /home/pi/rocket_hawk/logs/altimeters_logs/altimeter.txt
echo Accelerometer.txt:
stat -c %s /home/pi/rocket_hawk/logs/accelerometer_logs/accelerometer.txt
cd /home/pi/rocket_hawk/flight/altimeter/


for x in $(seq  $NUMBEROFCYCLES);
do
	echo pids
	/home/pi/rocket_hawk/flight/altimeter/bmp180 10 &
	pids="$!"
	wait $pids

done

#wait $pids



echo POST FLIGHT
echo Altimeter.txt:
stat -c %s /home/pi/rocket_hawk/logs/altimeters_logs/altimeter.txt
echo Accelerometer.txt:
stat -c %s /home/pi/rocket_hawk/logs/accelerometer_logs/accelerometer.txt


# python /home/pi/rocket_hawk/flight/accelerometer/accelerometer.py 10 &
