##### Compile ######

make all

########### Disk Benchmark Input ###########

1.Use Makefile to compile  MyMemBenchmark.c and name output file mymembenchmark.

2.Once compiled there are two scripts run1.sh, run2.sh and run3.sh can be used to post jobs on slurm parallelly. Run ach script individually one at a time for RR and RS.These scripts use sbatch command to run config files.

3.The is individual config file for each operations and for corresponding thread. E.g config_RWR_1000_1thread.slurm this can be created usinf mem-config-creator.sh

4.ach config file has #SBATCH argument and runs the executable. 

5.Dat file and output_mem_benchmark.dat  are used as input to the executable, Dat files has entry for each operation .

6.After the execution output is written into output_mem_benchmark.dat in formated way.

