BASEDIR=$(dirname "$0")
cd $BASEDIR
{ date '+%Y-%m-%d %H:%M:%S' ; ./read-dht11 7 ; } > temp