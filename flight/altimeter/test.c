#include "bmp180.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv){
  char *i2c_device = "/dev/i2c-1";
  int address = 0x77;
  FILE* altimeter_full_data = fopen("/home/pi/rocket_hawk/logs/altimeters_logs/altimeter.txt", "a");
 // FILE* altimeter_temperature = fopen("/home/pi/rocket_hawk/logs/altimeters_logs/altimeter_temperature.txt", "a");
 // FILE* altimeter_pressure = fopen("/home/pi/rocket_hawk/logs/altimeters_logs/altimeter_pressure.txt", "a");
 // FILE* altimeter_altitude = fopen("/home/pi/rocket_hawk/logs/altimeters_logs/altimeter_altitude.txt", "a");
        void *bmp = bmp180_init(address, i2c_device);

  // For taking command line arguments (cycle-seconds)
  int seconds = (argc > 1) ? atoi(argv[1])*4 : 40;
  bmp180_eprom_t eprom;
  bmp180_dump_eprom(bmp, &eprom);


  bmp180_set_oss(bmp, 1);
	
  if(bmp != NULL) {
    int i;
    for(i = 0; i < seconds; i++) {
      float t = bmp180_temperature(bmp);
      long p = bmp180_pressure(bmp);
      float alt = bmp180_altitude(bmp);
      fprintf(altimeter_full_data, "time = %d, t = %f, p = %lu, a= %f\n",(int)time(0) , t, p, alt);
   //   fprintf(altimeter_temperature, "[\'%d\', %f],", i, t);
     // fprintf(altimeter_pressure, "[\'%d\', %ld],", i, p);
     // fprintf(altimeter_altitude, "[\'%d\', %f],", i, alt);
      // fprintf(stdout, "t = %f, p = %lu, a= %f\n", t, p, alt);
      usleep(25*10*1000);
    }

    bmp180_close(bmp);
  }
  fclose(altimeter_full_data);
 // fclose(altimeter_temperature);
 // fclose(altimeter_pressure);
 // fclose(altimeter_altitude);
  return 0;
}
