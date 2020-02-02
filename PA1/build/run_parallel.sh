#!/bin/bash
#PBS -k eo
#PBS -m abe
#PBS -N XiaoyuJob

for i in {0..50000..1000}
do 
  /home/xy97/ece5750/ee/PA1/build/pbksb $i $p
done
