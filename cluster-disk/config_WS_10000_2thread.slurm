#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=main.out
#SBATCH --wait-all-nodes=1
echo 
./mydiskbenchmark disk-WS-10000-2thread.dat output_disk_throughput.dat
