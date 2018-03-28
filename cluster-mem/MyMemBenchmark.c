/*
 ============================================================================
 Name        : MyMemBenchmark.cs
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<time.h>
#include<pthread.h>
#include<sys/time.h>
#include<sys/resource.h>

struct inputs {
	int num_thread;
	int block_size;
	char * A, *B;
	int offset[4];
	int threadid;
	long int sizeperthread;
};

void *rws_operation(void* val) {

	struct inputs * input_values = (struct inputs*) val;
	int nthreads = input_values->num_thread;
	int blocksize = input_values->block_size;

	printf("values%d,%d", nthreads, blocksize);

	input_values->B = (char *) malloc(blocksize);
	if (input_values->B==NULL){
				printf ("cannot assigned");
		}
		int endofmemory = input_values->offset[input_values->threadid]+input_values->sizeperthread;
	for (int j = 1; j <= 100; j++) {
		for (int i = input_values->offset[input_values->threadid]; i != endofmemory ;i+= blocksize) {
			memcpy(input_values->B, input_values->A+(i), blocksize);

		}
	}
}

void *rwr_operation(void* val) {

	struct inputs * input_values = (struct inputs*) val;
		int nthreads = input_values->num_thread;
		int blocksize = input_values->block_size;
		int i,k,rand;
		printf("values%d,%d", nthreads, blocksize);

		input_values->B = (char *) malloc(blocksize);
		if (input_values->B==NULL){
			printf ("cannot assigned");
		}

		int noofblocks = input_values->sizeperthread/input_values->block_size;
		for (int j = 1; j <= 100; j++) {
			for (k = input_values->offset[input_values->threadid], i =0; i < noofblocks ; ++i ) {
				rand = (random()%noofblocks)*blocksize;
				memcpy(input_values->B, input_values->A+(k+rand), blocksize);

			}
		}

}


void * calc_latency_rwr(void *val){
	struct inputs * input_values = (struct inputs*) val;
			int nthreads = input_values->num_thread;
			int blocksize = input_values->block_size;
			int i,k,rand;
			printf("values%d,%d", nthreads, blocksize);

			input_values->B = (char *) malloc(blocksize);
			if (input_values->B==NULL){
				printf ("cannot assigned");
			}

			int noofblocks = input_values->sizeperthread;

				for (k = input_values->offset[input_values->threadid], i =0; i < noofblocks ; ++i ) {
					rand = (random()%noofblocks)*blocksize;
					memcpy(input_values->B, input_values->A+(k+rand), blocksize);

				}
}

void * calc_latency_rws(void *val){


	struct inputs * input_values = (struct inputs*) val;
	int nthreads = input_values->num_thread;
	int blocksize = input_values->block_size;

	printf("values%d,%d", nthreads, blocksize);

	input_values->B = (char *) malloc(blocksize);
	if (input_values->B==NULL){
				printf ("cannot assigned");
		}
		int endofmemory = input_values->offset[input_values->threadid]+input_values->sizeperthread;

		for (int i = input_values->offset[input_values->threadid]; i != endofmemory ;i+= blocksize) {
			memcpy(input_values->B, input_values->A+(i), blocksize);

		}

}


void main(int argc, char *argv[]) {

	//int num_thread,block_size;

	pthread_t ptrs[5];
	FILE * file,*fout;
	char c[3];
	int rc, i;
	struct timeval start, end;
	//float t;
	struct inputs val;
	long int block, G;
	if ((file = fopen(argv[1], "r")) != NULL) {
		fscanf(file, "%s", c);
		printf("%s\n", c);
		fscanf(file, "%ld", &block);
		printf("%ld\n", block);
		fscanf(file, "%d", &val.num_thread);
		printf("%d\n", val.num_thread);
	} else
		printf("%s\n", "cannot open the file");

		G = 1000000000L;



	 	 val.block_size=block;

	 	 if (val.block_size == 1){
	 		 G=G/10;
	 		 val.sizeperthread = G/val.num_thread;
	 		val.A = (char *) malloc(G);
	 				if (val.A==NULL){
	 					printf ("cannot assigned");
	 				}
	 	 }
	 	 else{
	 		val.sizeperthread = G/val.num_thread;
	 		val.A = (char *) malloc(G);
	 				if (val.A==NULL){
	 					printf ("cannot assigned");
	 				}
	 	 }

		memset(val.A,'A',G);

	gettimeofday(&start, NULL);

	if (val.block_size==1){ // for latency

		printf("\nfor blocksize 1\n");

		if (strcmp(c, "RWR") == 0) {
				for (i = 0; i < val.num_thread; i++) {
					printf("create thread");

					val.threadid=i;					//thread id
					val.offset[i]=val.sizeperthread*i;
					rc = pthread_create(&ptrs[i], NULL, (void *) &calc_latency_rwr,
							(void*) &val);
					printf("%s%d\n", "thread:", i);
					if (rc)
						printf("%s\n", "could not create thread");
				}
			} else if (strcmp(c, "RWS") == 0) {
				for (i = 0; i < val.num_thread; i++) {
					printf("create thread");

					val.threadid=i;					//thread id
					val.offset[i]=val.sizeperthread*i; // offset for each thread

					rc = pthread_create(&ptrs[i], NULL, (void *) &calc_latency_rws,
							(void*) &val);
					printf("%s%d\n", "thread:", i);
					if (rc)
						printf("%s\n", "could not create thread");
				}
			} else {

				printf("invalid input");
			}

	}

	else{  // for rest of blocksize

	if (strcmp(c, "RWR") == 0) {
		for (i = 0; i < val.num_thread; i++) {
			printf("create thread");

			val.threadid=i;					//thread id
			val.offset[i]=val.sizeperthread*i;
			rc = pthread_create(&ptrs[i], NULL, (void *) &rwr_operation,
					(void*) &val);
			printf("%s%d\n", "thread:", i);
			if (rc)
				printf("%s\n", "could not create thread");
		}
	} else if (strcmp(c, "RWS") == 0) {
		for (i = 0; i < val.num_thread; i++) {
			printf("create thread");

			val.threadid=i;					//thread id
			val.offset[i]=val.sizeperthread*i; // offset for each thread

			rc = pthread_create(&ptrs[i], NULL, (void *) &rws_operation,
					(void*) &val);
			printf("%s%d\n", "thread:", i);
			if (rc)
				printf("%s\n", "could not create thread");
		}
	} else {

		printf("invalid input");
		}

	}



	for (i = 0; i < val.num_thread; i++) {
		rc = pthread_join(ptrs[i], NULL);
		if (rc)
			printf("%s\n", "could not join thread");
	}

	gettimeofday(&end, NULL);

	float t =(float) (end.tv_sec - start.tv_sec)+ (float) (end.tv_usec - start.tv_usec) / 100000;

	if (val.block_size == 1){
		float latency = (t*1000*1000)/G; // in microseconds
		printf("\n latency:%f",latency);
		printf("\n time elapsed:%f",t);
		float latencytheortcl = (1.07*13)/1000;
		if((fout = fopen(argv[2],"a")) != NULL ){
			//printf("writing in file");
			//fprintf(fout,"%s\n","Workload Concurrency BlockSize MyRAMBenchValue TheoreticalValue MyRAMBenchEfficiency");
					fprintf(fout,"\n%ld\t%s\t%d\t%d\t%f\t%f\t%f",G,c,val.num_thread,val.block_size,latency,latencytheortcl,(latency/latencytheortcl) );	    }
	   else
		   printf("%s\n","cannot open the file");


	}
	else{

		double throuput = (100/t);
			printf("\n time elapsed:%f",t);
			printf("\n throughput:%f",throuput);
			float thrpttheoritical = (166.6 * 3* 64 *2)/(8*1000);
		if((fout = fopen(argv[2],"a")) != NULL ){
						 	 	//printf("writing in file");
			//fprintf(fout,"%s\n","Workload Concurrency BlockSize MyRAMBenchValue TheoreticalValue MyRAMBenchEfficiency");
			fprintf(fout,"\n%ld\t%s\t%d\t%d\t%f\t%f\t%f",G,c,val.num_thread,val.block_size,throuput,thrpttheoritical,(throuput/thrpttheoritical) );
			 }
			   else
				   printf("%s\n","cannot open the file");
	}

	free(val.A);
	free(val.B);
}

