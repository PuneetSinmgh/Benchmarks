#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=main.out
#SBATCH --wait-all-nodes=1
echo 
./mydiskbenchmark disk-RR-1-128thread.dat output_disk_latency.dat
