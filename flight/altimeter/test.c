#include "bmp180.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv){
  char *i2c_device = "/dev/i2c-1";
  int address = 0x77;
  FILE* altimeter_full_data = fopen("/home/pi/rocket_hawk/logs/altimeters_logs/altimeter.txt", "a");
  void *bmp = bmp180_init(address, i2c_device);
  int N = 10; // Number of samples per second
  int number_of_runs = (argc > 1) ? atoi(argv[1])*N : 10*N;
  double sleepDuration = (1000000/(double)N) - 40540;
  bmp180_eprom_t eprom;
  bmp180_dump_eprom(bmp, &eprom);
  bmp180_set_oss(bmp, 1);

  if(bmp != NULL) {
    int i;
    for(i = 0; i < number_of_runs; i++) {
      float t = bmp180_temperature(bmp);
      long p = bmp180_pressure(bmp);
      float alt = bmp180_altitude(bmp);
      fprintf(altimeter_full_data, "time = %d, t = %f, p = %lu, a= %f\n",(int)time(0) , t, p, alt);
      usleep(sleepDuration);
    }
    bmp180_close(bmp);
  }
  fclose(altimeter_full_data);
  return 0;
}
