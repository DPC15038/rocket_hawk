SENSOR=bmp180

all:
	gcc -Wall -c $(SENSOR).c -o $(SENSOR).o -lm
	gcc -Wall $(SENSOR).o test.c -o $(SENSOR) -lm
	rm $(SENSOR).o 

clean:
	rm *.o > /dev/null 2>&1 &
