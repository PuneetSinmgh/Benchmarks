#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=main.out
#SBATCH --wait-all-nodes=1
echo 
./mymembenchmark memory-RWS-10000000-1thread.dat output_mem_throughput.dat
