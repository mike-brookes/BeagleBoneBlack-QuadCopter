#!/bin/bash

proc_id=$(pidof Quadro)
if [ -z ${proc_id} ]; then
    echo "Quadro process is not currently running"
else
    kill -9 $proc_id
   echo "Found process : "$proc_id" : Quadro has been terminated."
fi

DIRS=`ls -l /sys/devices/ocp.3/ | grep 'pwm_test_P' | awk '{print $9}'`

for DIR in $DIRS
do
echo "Stopping motors..."
echo 780000 > '/sys/devices/ocp.3/'${DIR}'/duty'
done