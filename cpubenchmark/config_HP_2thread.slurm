#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=main.out
#SBATCH --wait-all-nodes=1
echo 
./mybenchmark cpu_HP_2thread.dat output_cpu_benchmark.dat
