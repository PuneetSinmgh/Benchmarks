#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=main.out
#SBATCH --wait-all-nodes=1
echo 
./mymembenchmark memory-RWR-1000-2thread.dat output_mem_throughput.dat
