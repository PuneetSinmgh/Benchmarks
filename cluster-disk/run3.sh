#!/bin/bash

for i in WR
do
	for j in 1000 10000 100000
	do 
		for k in 1 2 4
		do 
			sbatch config_${i}_${j}_${k}thread.slurm
		done
	done 
done
