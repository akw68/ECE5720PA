#!/bin/bash

for p in 128 256 512 1024 2048
do
  ./rbyc $p
done
for p in 128 256 512 1024 2048
do
  for b in 2 4 8 16 32 64
  do
    ./tile $p $b
  done
done
