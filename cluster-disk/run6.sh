#!/bin/bash

for i in RR WR
do
	for j in 1
	do 
		for k in 16 32 64 128
		do 
			sbatch config_${i}_${j}_${k}thread.slurm
		done
	done 
done
