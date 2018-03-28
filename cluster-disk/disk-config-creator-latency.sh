#!/bin/bash

touch output_disk_latency.dat
echo "Workload type Concurrency BlockSize MyDiskBenchLatency TheoreticalLatency Efficiency MyDiskIOPS TheoriticalIOps Efficiency" >> output_disk_latency.dat

for i in RR WR
do
	for j in 1
	do
		for k in 1 2 4 6 8 16 32 64 128
		do 
			touch config_${i}_${j}_${k}thread.slurm
		
			echo "#!/bin/bash" >> config_${i}_${j}_${k}thread.slurm
		
			echo "#SBATCH --nodes=1" >> config_${i}_${j}_${k}thread.slurm
			echo "#SBATCH --output=main.out" >> config_${i}_${j}_${k}thread.slurm
			echo "#SBATCH --wait-all-nodes=1" >> config_${i}_${j}_${k}thread.slurm
			

			echo "echo " >> config_${i}_${j}_${k}thread.slurm

			echo "./mydiskbenchmark disk-${i}-${j}-${k}thread.dat output_disk_latency.dat" >> config_${i}_${j}_${k}thread.slurm
			
			echo 
		done
	done
done
