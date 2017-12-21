### Odroid DHT22 GPIO
`git clone https://github.com/hardkernel/wiringPi`
`cd wiringPi`
`make`
`sudo make install`

`gcc -o read-dht22 read-dht22.c -lwiringPi -pthread`
`sudo ./read-dht22 <pinNo>`     - default pin is 7
`chmod +x read_save_temp.sh`
Add the following to `sudo crontab -e` `/absolute/project/path/dht22/read_save_temp.sh`
