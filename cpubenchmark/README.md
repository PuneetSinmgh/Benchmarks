## Compile

make all

########### CPU Benchmark Input ###########

<workload type (QP, HP, SP, DP)>
<number of threads (1,2,4)>


1.Use Makefile to compile  MyCpuBenchmark.c and name output file mybenchmark.
2.Once compiled there are two scripts run1.sh and run2.sh can be used to post jobs on slurm parallelly. 
3.Run1.sh can be used for QP and HP operations and Run2.sh can be used for SP and DP operations. These scripts use sbatch command to run config files .
4.The is individual config file for each operations and for corresponding thread. E.g config_DP_4thread.slurm
5.Ech config file has #SBATCH argument and runas the executable. 
6.Dat file and output_cpu_benchmark.dat  are used as input to the executable, Dat files has entry for each operation .
7.After the execution output is written into output_cpu_benchmark.dat in formated way.

