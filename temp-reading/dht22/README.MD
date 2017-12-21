# Odroid/RaspberryPI DHT22 read using GPIO
Create a cron-job for reading DHT22 sensor from RapsberryPI GPIO and storing the current date and result in a file `temp` in the current directory.



## Installing wiringPi dependency
If wiringPi is not installed, run
```
git clone https://github.com/hardkernel/wiringPi
cd wiringPi
make
sudo make install
```


## Building
```
gcc -o read-dht22 read-dht22.c -lwiringPi -pthread
sudo ./read-dht22 <pinNo>     - default pin is 7
chmod +x read_save_temp.sh
```
Add the following to `sudo crontab -e`: `/absolute/project/path/dht22/read_save_temp.sh`



## Format of `temp` file
```
2017-12-22 01:50:01
Humidity = 37.30 % Temperature = 21.00 *C
```
