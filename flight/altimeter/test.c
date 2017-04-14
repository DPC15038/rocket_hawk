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

  // For taking command line arguments (cycle-seconds)
  int seconds = (argc > 1) ? atoi(argv[1])*10 : 100;
  bmp180_eprom_t eprom;
  bmp180_dump_eprom(bmp, &eprom);

  printf("seconds is %d\n", seconds);
  bmp180_set_oss(bmp, 1);

  if(bmp != NULL) {
    int i;
    double timestamps[2];
    // struct timeval  tv;
    // gettimeofday(&tv, NULL);
    // double time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ; // convert tv_sec & tv_u
    // timestamps[0] = time_in_mill;
    //
    // for (i = 0; i < seconds; i++){
    //   fprintf(altimeter_full_data, "time = %d, t = %f, p = %lu, a= %f\n",(int)time(0) , 3, 3, 4);
    //   float t = bmp180_temperature(bmp);
    //   long p = bmp180_pressure(bmp);
    //   float alt = bmp180_altitude(bmp);
    //   usleep(0);
    //   // ;
    // }
    // gettimeofday(&tv, NULL);
    // time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ; // convert tv_sec & tv_u
    // timestamps[1] = time_in_mill;
    // printf ("The time is %lf\n", timestamps[0]);
    // printf ("The time is %lf\n", timestamps[1]);
    // printf ("difference = %lf\n", timestamps[1]-timestamps[0]);
    // // printf ("The time is %lf\n", time_in_mill);
    // exit(1);

    struct timeval  tv;
    gettimeofday(&tv, NULL);
    double time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ; // convert tv_sec & tv_u
    timestamps[0] = time_in_mill;
    for(i = 0; i < seconds; i++) {
      float t = bmp180_temperature(bmp);
      long p = bmp180_pressure(bmp);
      float alt = bmp180_altitude(bmp);
      fprintf(altimeter_full_data, "time = %d, t = %f, p = %lu, a= %f\n",(int)time(0) , t, p, alt);
      usleep(100000);
    }
    gettimeofday(&tv, NULL);
    time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ; // convert tv_sec & tv_u
    timestamps[1] = time_in_mill;
    printf ("difference = %lf\n", timestamps[1]-timestamps[0]);
    bmp180_close(bmp);
  }
  fclose(altimeter_full_data);
  return 0;
}
