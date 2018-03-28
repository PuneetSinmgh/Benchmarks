#!/bin/bash

for i in UDP
do
	for j in 1 1000 32000
	do
		for k in 1 2 4 8
		do
		
			touch config_${i}_${j}_${k}thread.slurm
					
			echo "#!/bin/bash" >> config_${i}_${j}_${k}thread.slurm
		
			echo "#SBATCH --nodes=2" >> config_${i}_${j}_${k}thread.slurm
			echo "#SBATCH --ntasks=2" >> config_${i}_${j}_${k}thread.slurm
			echo "#SBATCH --output=main.out" >> config_${i}_${j}_${k}thread.slurm
			echo "#SBATCH --wait-all-nodes=1" >> config_${i}_${j}_${k}thread.slurm

			echo "sbcast netbenchudp /tmp/netbenchudp" >> config_${i}_${j}_${k}thread.slurm
			echo "srun udp-run.sh \$SLURM_JOB_NODELIST /$(pwd)/network-${i}-${j}-${k}thread.dat /$(pwd)/output_net_throughput.dat" >> config_${i}_${j}_${k}thread.slurm
			
		done
	done
done
