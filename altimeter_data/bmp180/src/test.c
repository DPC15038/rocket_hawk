#include "bmp180.h"
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv){
  char *i2c_device = "/dev/i2c-1";
  int address = 0x77;
  FILE* altimeter_full_data = fopen("../../altimeter.txt", "w");
  FILE* altimeter_temperature = fopen("../../altimeter_temperature.txt", "w");
  FILE* altimeter_pressure = fopen("../../altimeter_pressure.txt", "w");
  FILE* altimeter_altitude = fopen("../../altimeter_altitude.txt", "w");
        void *bmp = bmp180_init(address, i2c_device);

  bmp180_eprom_t eprom;
  bmp180_dump_eprom(bmp, &eprom);


  bmp180_set_oss(bmp, 1);

  if(bmp != NULL){
    int i;
    for(i = 0; i < 100 /*1200*/; i++) {
      float t = bmp180_temperature(bmp);
      long p = bmp180_pressure(bmp);
      float alt = bmp180_altitude(bmp);
      fprintf(altimeter_full_data, "t = %f, p = %lu, a= %f\n", t, p, alt);
      fprintf(altimeter_temperature, "[\'%d\', \'%f\'],", i, t);
      fprintf(altimeter_pressure, "[\'%d\', \'%ld\'],", i, p);
      fprintf(altimeter_altitude, "[\'%d\', \'%f\'],", i, alt);
      fprintf(stdout, "t = %f, p = %lu, a= %f\n", t, p, alt);
      usleep(2*1000*250);
    }

    bmp180_close(bmp);
  }
  fclose(altimeter_full_data);
  fclose(altimeter_temperature);
  fclose(altimeter_pressure);
  fclose(altimeter_altitude);
  return 0;
}
