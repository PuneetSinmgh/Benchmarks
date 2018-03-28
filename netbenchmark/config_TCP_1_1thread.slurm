#!/bin/bash
#SBATCH --nodes=2
#SBATCH --ntasks=2
#SBATCH --output=main.out
#SBATCH --wait-all-nodes=1
sbcast netbenchtcp /tmp/netbenchtcp
srun tcp-run.sh $SLURM_JOB_NODELIST //exports/home/psingh52/PA1/MyNetBenchmark/network-TCP-1-1thread.dat //exports/home/psingh52/PA1/MyNetBenchmark/output_net_throughput.dat
