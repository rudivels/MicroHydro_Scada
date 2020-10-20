#!/bin/bash 
for (( ; ; ))
do
   # echo "infinite loops [ hit CTRL+C to stop]"   
   python3 /home/pi/src/MicroHydro_Scada/publish_microhydro_002.py /home/pi/src/MicroHydro_Scada/local_log1.txt 
   sleep 10
done 