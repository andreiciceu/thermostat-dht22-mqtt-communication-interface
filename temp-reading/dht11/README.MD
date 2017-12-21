### Odroid DHT11 GPIO
`git clone https://github.com/hardkernel/wiringPi`
`cd wiringPi`
`make`
`sudo make install`

`gcc -o read-dht11 read-dht11.c -lwiringPi -pthread`
`sudo ./read-dht11 <pinNo>`     - default pin is 7
`chmod +x read_save_temp.sh`
Add the following to `sudo crontab -e` `/absolute/project/path/dht11/read_save_temp.sh`