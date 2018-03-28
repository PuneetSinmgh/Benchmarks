#!/bin/bash

touch output_mem_throughput.dat
chmod 775 output_mem_throughput.dat
echo "Workload type Concurrency BlockSize MyMemBenchvalue Theoreticalvalue Efficiency" >> output_mem_throughput.dat

for i in RWR RWS
do
	for j in 1 1000 1000000 10000000
	do
		for k in 1 2 4
		do
		
			touch config_${i}_${j}_${k}thread.slurm
					
			echo "#!/bin/bash" >> config_${i}_${j}_${k}thread.slurm
		
			echo "#SBATCH --nodes=1" >> config_${i}_${j}_${k}thread.slurm
			echo "#SBATCH --output=main.out" >> config_${i}_${j}_${k}thread.slurm
			echo "#SBATCH --wait-all-nodes=1" >> config_${i}_${j}_${k}thread.slurm

			echo "echo " >> config_${i}_${j}_${k}thread.slurm

			echo "./mymembenchmark memory-${i}-${j}-${k}thread.dat output_mem_throughput.dat" >> config_${i}_${j}_${k}thread.slurm
		done
	done
done
