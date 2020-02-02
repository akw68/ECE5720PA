#!/bin/bash
#PBS -k eo
#PBS -m abe
#PBS -N XiaoyuJob

for i in {40500..51000..500}
do 
  /home/xy97/ece5750/ee/PA1/build/bksb $i
done 

