#!/bin/bash

touch output_disk_throughput.dat
echo "Workload type Concurrency BlockSize MyDiskBenchThroughput TheoreticalThroughput Efficiency" >> output_disk_throughput.dat

for i in RR RS WR WS
do
	for j in 1000 10000 100000
	do
		for k in 1 2 4
		do 
			touch config_${i}_${j}_${k}thread.slurm
			
			echo "#!/bin/bash" >> config_${i}_${j}_${k}thread.slurm
		
			echo "#SBATCH --nodes=1" >> config_${i}_${j}_${k}thread.slurm
			echo "#SBATCH --output=main.out" >> config_${i}_${j}_${k}thread.slurm
			echo "#SBATCH --wait-all-nodes=1" >> config_${i}_${j}_${k}thread.slurm
			
			echo "echo " >> config_${i}_${j}_${k}thread.slurm
			echo "./mydiskbenchmark disk-${i}-${j}-${k}thread.dat output_disk_throughput.dat" >> config_${i}_${j}_${k}thread.slurm
		done
	done
done
