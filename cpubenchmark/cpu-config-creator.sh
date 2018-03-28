#!/bin/bash

touch output_cpu_benchmark.dat
chmod 775 output_cpu_benchmark.dat
echo "Workload type Concurrency MyCpuPerformance Theoreticalperformance Efficiency" >> output_cpu_benchmark.dat


for i in QP HP SP DP
do
	for j in 1 2 4
	do
		touch config_${i}_${j}thread.slurm
				
		echo "#!/bin/bash" >> config_${i}_${j}thread.slurm
		
		echo "#SBATCH --nodes=1" >> config_${i}_${j}thread.slurm
		echo "#SBATCH --output=main.out" >> config_${i}_${j}thread.slurm
		echo "#SBATCH --wait-all-nodes=1" >> config_${i}_${j}thread.slurm

		echo "echo " >> config_${i}_${j}thread.slurm

		echo "./mybenchmark cpu_${i}_${j}thread.dat output_cpu_benchmark.dat" >> config_${i}_${j}thread.slurm
	done
done
