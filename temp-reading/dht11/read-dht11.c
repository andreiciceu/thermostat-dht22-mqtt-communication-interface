/*
 *      dht11.c:
 *      Simple test program to test the wiringPi functions
 *      Based on the existing dht11.c
 *      Amended by technion@lolware.net
 */

#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXTIMINGS 85
static int DHTPIN = 7;
static int dht11_dat[5] = {0,0,0,0,0};

static uint8_t sizecvt(const int read)
{
  /* digitalRead() and friends from wiringpi are defined as returning a value
  < 256. However, they are returned as int() types. This is a safety function */

  if (read > 255 || read < 0)
  {
    printf("Invalid data from wiringPi library\n");
    exit(EXIT_FAILURE);
  }
  return (uint8_t)read;
}

static int read_dht11_dat()
{
  uint8_t laststate = HIGH;
  uint8_t counter = 0;
  uint8_t j = 0, i;

  dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

  // pull pin down for 18 milliseconds
  pinMode(DHTPIN, OUTPUT);
  digitalWrite(DHTPIN, HIGH);
  delay(10);
  digitalWrite(DHTPIN, LOW);
  delay(18);
  // then pull it up for 40 microseconds
  digitalWrite(DHTPIN, HIGH);
  delayMicroseconds(40);
  // prepare to read the pin
  pinMode(DHTPIN, INPUT);

  // detect change and read data
  for ( i=0; i< MAXTIMINGS; i++) {
    counter = 0;
    while (sizecvt(digitalRead(DHTPIN)) == laststate) {
      counter++;
      delayMicroseconds(2);
      if (counter == 255) {
        break;
      }
    }
    laststate = sizecvt(digitalRead(DHTPIN));
   // printf("me here, trying to figure out what is going on in the world %i \n", laststate);
//    delay(1);

    if (counter == 255) break;

    // ignore first 3 transitions
    if ((i >= 4) && (i%2 == 0)) {
      // shove each bit into the storage bytes
      dht11_dat[j/8] <<= 1;
      if (counter > 16)
        dht11_dat[j/8] |= 1;
      j++;
    }
  }

  // check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
  // print it out if data is good
  if ((j >= 40) &&
      (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF)) ) {
      // 1 ) {
        float h = (float)((dht11_dat[0] << 8) + dht11_dat[1]) / 10;
    		if ( h > 100 )
    		{
    			h = dht11_dat[0];	// for DHT11
    		}
    		float c = (float)(((dht11_dat[2] & 0x7F) << 8) + dht11_dat[3]) / 10;
    		if ( c > 125 )
    		{
    			c = dht11_dat[2];	// for DHT11
    		}
    		if ( dht11_dat[2] & 0x80 )
    		{
    			c = -c;
    		}
    		float f = c * 1.8f + (float)32;
    		printf( "Humidity = %.1f %% Temperature = %.2f *C (%.2f *F)\n", h, c, f );
  }
  else
  {
    printf("Data not good, skip\n");
    return 0;
  }
}

int main (int argc, char *argv[])
{
  int lockfd;

  if (argc != 2)
    printf ("usage: %s <pin>\ndescription: pin is the wiringPi pin number\nusing 7 (GPIO 4)\n",argv[0]);
  else
    DHTPIN = atoi(argv[1]);


  // printf ("Raspberry Pi wiringPi DHT22 reader\nwww.lolware.net\n") ;


  if (wiringPiSetup () == -1)
    exit(EXIT_FAILURE) ;

  if (setuid(getuid()) < 0)
  {
    perror("Dropping privileges failed\n");
    exit(EXIT_FAILURE);
  }

  while (read_dht11_dat() == 0) {
     delay(1000); // wait 1sec to refresh
  }


  return 0 ;
}