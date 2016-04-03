#!/bin/bash

FULL_THROTTLE=150000;
TAKEOFF_THROTTLE=250000;
STOP_THROTTLE=780000;
LOW_THROTTLE=700000;
STARTING_POS=1;
ENDING_POS=126;
STATUS_STR='';
LOOP_COUNTER=0;
OUTPUT_STR='';

DIRS=`ls -l /sys/devices/ocp.3/ | grep 'pwm_test_P' | awk '{print $9}'`
MOTOR1=`ls -l /sys/devices/ocp.3/ | grep 'pwm_test_P9_42' | awk '{print $9}'`
MOTOR2=`ls -l /sys/devices/ocp.3/ | grep 'pwm_test_P8_19' | awk '{print $9}'`
MOTOR3=`ls -l /sys/devices/ocp.3/ | grep 'pwm_test_P9_14' | awk '{print $9}'`
MOTOR4=`ls -l /sys/devices/ocp.3/ | grep 'pwm_test_P9_22' | awk '{print $9}'`

frame_str="         ";
for ((i=$STARTING_POS; i<=$ENDING_POS; i++)); do frame_str="$frame_str="; done

{
while :
do
        for DIR in $DIRS;
        do
                LOOP_COUNTER=$((LOOP_COUNTER + 1));
                while read line
                do
                        let num=$line/10000;
                        let "READING_END = num";
                        let "READING_END -= 15";
                        let "READING_END *= 2";

                        for ((i=$ENDING_POS; i>=$STARTING_POS; i--));
                        do
                                if [ "$i" -lt "$READING_END" ]; then
                                        STATUS_STR="$STATUS_STR\e[7m\e[0m ";
                                else
                                        STATUS_STR="$STATUS_STR\e[7m\e[32m \e[0m";
                                fi
                        done

                        STATUS_STR="$line - |$STATUS_STR| - $FULL_THROTTLE\n         |$STATUS_STR|";
                done < /sys/devices/ocp.3/${DIR}/duty

                OUTPUT_STR="$OUTPUT_STR $frame_str\n$STATUS_STR\n $frame_str\n\n";
                STATUS_STR='';
                STATUS_STR1='';
                if [ $LOOP_COUNTER -eq 4 ]; then
                        clear;
                        printf "$OUTPUT_STR";
                        LOOP_COUNTER=0;
                        OUTPUT_STR='';
                fi
        done
done