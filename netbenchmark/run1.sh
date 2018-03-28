#!/bin/bash

for i in TCP
do
	for j in 1000 32000
	do 
		for k in 1 2 4 8
		do 
			sbatch config_${i}_${j}_${k}thread.slurm
		done
	done 
done
