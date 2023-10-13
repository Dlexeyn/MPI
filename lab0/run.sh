#!/bin/bash

mpiexec -n 1 --use-hwthread-cpus --oversubscribe ./cmake-build-debug/lab0 > out.txt
for((i=2; i <= 36; i++))
do
   mpiexec -n "$i" --use-hwthread-cpus --oversubscribe ./cmake-build-debug/lab0 >> out.txt
done

python3 plot.py