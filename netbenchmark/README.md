##### Compile #####

make all

########### Memory Benchmark Input ###########

<benchmark_type (RWS RWR)>
<block size (1B, 1KB, 1MB, 10MB)> # in bytes
<number of threads (1,2,4)>


1.Use Makefile to compile  MynetbenchTCP.c and MynetbenchUDP.c name output file mynetbenchtcp and netbenchudp.
2.Once compiled there are three scripts run1.sh, run2.sh, run3.sh  can be used to post jobs on slurm parallelly. Run ach script individually one at a time to run TCP and UDP both operations.
3.Run3.sh can be used to trigger jobs for measuring latency on 1B data.
4.These scripts use sbatch command to run config files.
5.The is individual config file for each operations and for corresponding thread. E.g config_TCP_1000_1thread.slurm this can be created using TCP-config-creator.sh and UDP-config-creator.sh.
6.Each config file uses tcp-run.sh and udp-run.sh to execute the executables. 
7.Each config file has #SBATCH argument and runs the executable. 
8.Dat file and output_net_throughput.dat  are used as input to the executable, Dat files has entry for each operation .
9.After the execution output is written into output_net_throughput.dat in formated way.
10.After the execution output is written into output_mem_benchmark.dat in formated way.

