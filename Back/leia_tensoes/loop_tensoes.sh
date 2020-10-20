#!/bin/bash 
for (( ; ; ))
do
   /home/pi/src/leia_tensoes/le_rede > /home/pi/src/leia_tensoes/rede.log 
   /home/pi/src/leia_tensoes/le_bateria > /home/pi/src/leia_tensoes/bateria.log 
   sleep 1
done 
