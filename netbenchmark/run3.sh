#!/bin/bash

for i in TCP UDP
do
	for j in 1
	do 
		for k in 1 2 4 8
		do 
			sbatch config_${i}_${j}_${k}thread.slurm
		done
	done 
done
