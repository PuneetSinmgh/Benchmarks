#!/bin/bash

for i in RWR RWS
do
	for j in 1 1000 1000000 10000000 
	do 
		for k in 4
		do
			sbatch config_${i}_${j}_${k}thread.slurm
		done
	done 
done
