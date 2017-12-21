#!/bin/bash
BASEDIR=$(dirname "$0")
cd $BASEDIR
{ date '+%Y-%m-%d %H:%M:%S' ; ./read-dht22 7 ; } > temp