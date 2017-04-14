#!/bin/bash

function clear_docs {
	> /home/pi/rocket_hawk/logs/altimeters_logs/altimeter_altitude.txt
	> /home/pi/rocket_hawk/logs/altimeters_logs/altimeter_pressure.txt
	> /home/pi/rocket_hawk/logs/altimeters_logs/altimeter_temperature.txt
	> /home/pi/rocket_hawk/logs/altimeters_logs/altimeter.txt
	> /home/pi/rocket_hawk/logs/accelerometer_logs/accelerometer.txt
}


echo "Are you sure you want to delete all rocket log files?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) clear_docs
	      break;;
        No ) exit;;
    esac
done
