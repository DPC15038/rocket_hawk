#!/bin/bash

timestamp() {
 date +"%F %T.%3N"
}

NUMBEROFCYCLES=10

cd /home/pi/rocket_hawk/flight/altimeter/
for x in $(seq  $NUMBEROFCYCLES);
do
	timestamp
	SECONDS=2        
	./bmp180 $SECONDS
	timestamp
	echo
done

