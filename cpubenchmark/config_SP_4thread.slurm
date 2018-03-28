#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=main.out
#SBATCH --wait-all-nodes=1
echo 
./mybenchmark cpu_SP_4thread.dat output_cpu_benchmark.dat
