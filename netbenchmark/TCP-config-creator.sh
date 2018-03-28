#!/bin/bash

touch output_net_throughput.dat
chmod 775 output_net_throughput.dat
echo "Protocol Concurrency BlockSize MyNETBenchValue TheoreticalValue MyNETBenchEfficiency" >> output_net_throughput.dat

for i in TCP
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
				
			echo "sbcast netbenchtcp /tmp/netbenchtcp" >> config_${i}_${j}_${k}thread.slurm 
			echo "srun tcp-run.sh \$SLURM_JOB_NODELIST /$(pwd)/network-${i}-${j}-${k}thread.dat /$(pwd)/output_net_throughput.dat" >> config_${i}_${j}_${k}thread.slurm
	
		done
	done
done
