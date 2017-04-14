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

  // For taking command line arguments (cycle-number_of_runs)
  int samplesPerSecond = 2;
  int number_of_runs = (argc > 1) ? atoi(argv[1])*samplesPerSecond : 10*samplesPerSecond;
  // int sleepDuration = ((1000000/(double)samplesPerSecond));
  int sleepDuration = ((10000000/(double)samplesPerSecond) - (number_of_runs*((405.1727*(double)samplesPerSecond)-1.363)));
  // printf("Each sleep would've occured for %g\n", ((1000000/(double)samplesPerSecond)));
  printf("offset of %g\n", (4051.727*(double)samplesPerSecond)-13.63);
  // double myShit = ((1000000/(double)samplesPerSecond) - (4051.727*(double)samplesPerSecond)-13.63);
  // sleepDuration = myShit;
  // printf("But it'll actually occur for %g\n", myShit);
  // printf("samplesPerSecond = %d, number_of_runs = %d, sleepDuration = %d\n", samplesPerSecond, number_of_runs, sleepDuration);
  // exit(1);
  // printf("The sleep duration offset is %d\n", sleepDuration);
  printf("Each sleep will occur for %d.\n", sleepDuration);
  // exit(1);
  bmp180_eprom_t eprom;
  bmp180_dump_eprom(bmp, &eprom);

  // printf("number_of_runs is %d\n", number_of_runs/10);
  // printf("cycles  is %d\n", number_of_runs);

  bmp180_set_oss(bmp, 1);

  if(bmp != NULL) {
    int i;
    double timestamps[2];
    // struct timeval  tv;
    // gettimeofday(&tv, NULL);
    // double time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ; // convert tv_sec & tv_u
    // timestamps[0] = time_in_mill;
    //
    // for (i = 0; i < number_of_runs; i++){
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
    for(i = 0; i < number_of_runs; i++) {
      float t = bmp180_temperature(bmp);
      long p = bmp180_pressure(bmp);
      float alt = bmp180_altitude(bmp);
      fprintf(altimeter_full_data, "time = %d, t = %f, p = %lu, a= %f\n",(int)time(0) , t, p, alt);
      usleep(sleepDuration);
      // usleep(sleepDuration);
      // printf("slept....\n");
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
