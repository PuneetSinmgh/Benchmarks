C=gcc
CFLAGS=-g -Wall -mavx -mfma -O0 -lpthread -pthread -std=c99

all:
        $(CC) $(CFLAGS) -o mybenchmark MyCpuBench.c

clean:
        $(RM) *.o mybenchmark
