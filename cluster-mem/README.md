##### Compile #####

make all

########### Memory Benchmark Input ###########

<benchmark_type (RWS RWR)>
<block size (1B, 1KB, 1MB, 10MB)> # in bytes
<number of threads (1,2,4)>

1.Use Makefile to compile  MyMemBenchmark.c and name output file mymembenchmark.
2.Once compiled there are two scripts run1.sh, run2.sh and run3.sh can be used to post jobs on slurm parallelly. Run ach script individually one at a time for RWRand RWS
3. These scripts use sbatch command to run config files.
4.The is individual config file for each operations and for corresponding thread. E.g config_RWR_1000_1thread.slurm this can be created usinf mem-config-creator.sh
5.Each config file has #SBATCH argument and runs the executable. 
6.Dat file and output_mem_benchmark.dat  are used as input to the executable, Dat files has entry for each operation .
7.After the execution output is written into output_mem_benchmark.dat in formated way.

