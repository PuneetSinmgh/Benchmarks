#!/bin/bash

for i in RWR RWS
do
	for j in 1 1000 
	do 
		for k in 1 2
		do
			sbatch config_${i}_${j}_${k}thread.slurm
		done
	done 
done
