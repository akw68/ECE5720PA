#!/bin/bash
#PBS -k eo
#PBS -m abe
#PBS -N AdamJob
/home/akw68/ECE5750PA/PA1/build/bksb $n
for i in {1..20}
do
  /home/akw68/ECE5750PA/PA1/build/pbksb $n $i
done
