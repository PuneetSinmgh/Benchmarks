#!/bin/bash

for i in SP DP
do
	for j in 1 2 4 
	do 
		sbatch config_${i}_${j}thread.slurm
	done 
done
