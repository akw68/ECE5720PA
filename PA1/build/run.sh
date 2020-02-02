
#qsub run_serial.sh

for i in {2..2}
do
  qsub -v p=$i run_parallel.sh
done