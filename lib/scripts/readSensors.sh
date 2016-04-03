#!/bin/bash

while true; do
        (echo -en '\033[H'
        CMD="$@"
        while read LINE; do
                echo -n "$LINE"
                echo -e '\033[0K'
        done < /root/robotics/QuadCopter/Debug/accel_data.dat
        echo -en '\033[J') | tac | tac
        sleep 0.1;
done