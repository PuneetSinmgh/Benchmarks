
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<time.h>
#include<pthread.h>
#include<sys/time.h>
#include<sys/resource.h>

struct inputs {
	int num_thread;
	long int block_size;
	char * A , *B;
	long int offset[128];
	int threadid;
	long int sizeperthread;
};

int *rs_operation(void* val) {

	struct inputs * input_values = (struct inputs*) val;
	int nthreads = input_values->num_thread;
	int noofblocks = input_values->sizeperthread/input_values->block_size;
	FILE * fp;
	int i;
	if ((fp = fopen(input_values->A, "r+")) != NULL) {

			} else
				printf("%s\n", "cannot open the file2");


	char* arr= (char*)malloc(input_values->block_size);
	//system("echo 3 | sudo tee /proc/sys/vm/drop_caches");
	//int endofmemory = input_values->offset[input_values->threadid]+input_values->sizeperthread;

	fseek(fp,input_values->offset[input_values->threadid],SEEK_SET);
		for (i = 0; i < noofblocks; ++i) {
			//memcpy(input_values->B+(i/4), input_values->A+(i/4), blocksize);
			fread(arr,sizeof(char),input_values->block_size,fp);
			//fseek(fp,input_values->block_size,SEEK_CUR);
		}
		free(arr);
		fclose(fp);
	return 0;
}

int *rr_operation(void* val) {

	struct inputs * input_values = (struct inputs*) val;
		//int nthreads = input_values->num_thread;
		//int blocksize = input_values->block_size;
		int rand, i;
		FILE * fp;
		if ((fp = fopen(input_values->A, "r+")) != NULL) {

		} else
		printf("%s\n", "cannot open the file2");


		int noofblocks = input_values->sizeperthread/input_values->block_size;

		char* arr= (char*)malloc(input_values->block_size);
		//system("echo 3 | sudo tee /proc/sys/vm/drop_caches");
			for ( i =0; i < noofblocks ; ++i ) {
				rand = (random()%noofblocks)*input_values->block_size;
				fread(arr,sizeof(char),input_values->block_size,fp);
				fseek(fp,input_values->offset[input_values->threadid]+rand,SEEK_SET);

			}

			printf("file complete : %d",i);
			free(arr);
			fclose(fp);
			return 0;
}

int *ws_operation(void* val) {

	struct inputs * input_values = (struct inputs*) val;
		//int nthreads = input_values->num_thread;
		//int blocksize = input_values->block_size;
		int  i;
		FILE * fp;
		if ((fp = fopen(input_values->A, "r+")) != NULL) {

		} else
		printf("%s\n", "cannot open the file2");


		int noofblocks = input_values->sizeperthread/input_values->block_size;

		//char* arr= (char*)malloc(input_values->block_size);
		//system("echo 3 | sudo tee /proc/sys/vm/drop_caches");
		fseek(fp,input_values->offset[input_values->threadid],SEEK_SET);
				for ( i = 0; i < noofblocks; ++i) {
					//memcpy(input_values->B+(i/4), input_values->A+(i/4), blocksize);
					fwrite(input_values->B,sizeof(char),input_values->block_size,fp);
					//fseek(fp,input_values->block_size,SEEK_CUR);
				}

				printf("file complete : %d",i);
			//free(arr);
			fclose(fp);
			return 0;
}

int *wr_operation(void* val) {

	struct inputs * input_values = (struct inputs*) val;
		//int nthreads = input_values->num_thread;
		//int blocksize = input_values->block_size;
		int rand, i;
		FILE * fp;
		if ((fp = fopen(input_values->A, "r+")) != NULL) {

		} else
		printf("%s\n", "cannot open the file2");


		int noofblocks = input_values->sizeperthread/input_values->block_size;

		//char* arr= (char*)malloc(input_values->block_size);
		//system("echo 3 | sudo tee /proc/sys/vm/drop_caches");
			for ( i =0; i < noofblocks ; ++i ) {
				rand = (random()%noofblocks)*input_values->block_size;
				fwrite(input_values->B,sizeof(char),input_values->block_size,fp);
				fseek(fp,input_values->offset[input_values->threadid]+rand,SEEK_SET);

			}
			printf("file complete : %d",i);
			//free(arr);
			fclose(fp);
			return 0;
}

void main(int argc, char *argv[]) {

	//int num_thread,block_size;

	pthread_t ptrs[128];
	FILE * file,*fout,*fp;
	char c[3];
	int rc, i;
	struct timeval start, end;
	//float t;
	struct inputs val, create_file ;
	long long int  filesize;
	if ((file = fopen(argv[1], "r")) != NULL) {
		fscanf(file, "%s", c);
		printf("%s\n", c);
		fscanf(file, "%d", &val.block_size);
		printf("%d\n", val.block_size);
		fscanf(file, "%d", &val.num_thread);
		printf("%d\n", val.num_thread);
	} else
		printf("%s\n", "cannot open the file1");

// File creation

			printf("creating 10g file");
			create_file.A =  "/tmp/sample.dat";
			if ((fp = fopen(create_file.A, "w+")) != NULL) {
				printf("%s\n", "sample.dat created");
					} else
					printf("%s\n", "cannot create sample.dat");


			filesize = 10000000000LL;
			create_file.sizeperthread=filesize/8;
			create_file.block_size = 1000;

			create_file.B = (char *) malloc(create_file.block_size);
			memset(create_file.B,"A",create_file.block_size);
			//system("chmod 775 /home/puneet/workspace/sample.dat");
			printf("\n writing file");
			for (i = 0; i < 8; i++) {
						printf("\n create thread");

						create_file.threadid=i;					//thread id
						create_file.offset[i]=create_file.sizeperthread*i;
						rc = pthread_create(&ptrs[i], NULL, (void *) &ws_operation,
								(void*) &create_file);
						printf("%s%d\n", "thread:", i);
						if (rc)
							printf("%s\n", "could not create thread");
					}


			for (i = 0; i < 8; i++) {
				rc = pthread_join(ptrs[i], NULL);
				if (rc)
					printf("%s\n", "could not join thread");
			}

// End of file creation

			if(val.block_size==1){
				filesize = 1000000000LL;
				printf("file size set to 1G");
			}
		val.A = "/tmp/sample.dat";
	 	val.sizeperthread = filesize/val.num_thread;
	 	val.block_size=val.block_size*1000;

	 	val.B = (char *) malloc(val.block_size);
	 	if (val.B==NULL){
			printf ("cannot assigned buffer");
	 	}
	 	memset(val.B,"A",val.block_size);

	 	//system("echo 3 > /proc/sys/vm/drop_caches");
	 	gettimeofday(&start, NULL);

	if (strcmp(c, "RR") == 0) {
		for (i = 0; i < val.num_thread; i++) {
			printf("create thread");

			val.threadid=i;					//thread id
			val.offset[i]=val.sizeperthread*i;
			rc = pthread_create(&ptrs[i], NULL, (void *) &rr_operation,
					(void*) &val);
			printf("%s%d\n", "thread:", i);
			if (rc)
				printf("%s\n", "could not create thread");
		}
	} else if (strcmp(c, "RS") == 0) {
		for (i = 0; i < val.num_thread; i++) {
			printf("create thread");

			val.threadid=i;					//thread id
			val.offset[i]=val.sizeperthread*i; // offset for each thread

			rc = pthread_create(&ptrs[i], NULL, (void *) &rs_operation,
					(void*) &val);
			printf("%s%d\n", "thread:", i);
			if (rc)
				printf("%s\n", "could not create thread");
		}
	}
	 else if (strcmp(c, "WR") == 0) {
			for (i = 0; i < val.num_thread; i++) {
				printf("create thread");

				val.threadid=i;					//thread id
				val.offset[i]=val.sizeperthread*i; // offset for each thread

				rc = pthread_create(&ptrs[i], NULL, (void *) &wr_operation,
						(void*) &val);
				printf("%s%d\n", "thread:", i);
				if (rc)
					printf("%s\n", "could not create thread");
			}
		}
	 else if (strcmp(c, "WS") == 0) {
			for (i = 0; i < val.num_thread; i++) {
				printf("create thread");

				val.threadid=i;					//thread id
				val.offset[i]=val.sizeperthread*i; // offset for each thread

				rc = pthread_create(&ptrs[i], NULL, (void *) &ws_operation,
						(void*) &val);
				printf("%s%d\n", "thread:", i);
				if (rc)
					printf("%s\n", "could not create thread");
			}
		}
	else {

		printf("invalid input");
	}

	for (i = 0; i < val.num_thread; i++) {
		rc = pthread_join(ptrs[i], NULL);
		if (rc)
			printf("%s\n", "could not join thread");
	}

	gettimeofday(&end, NULL);

	float t =(float) (end.tv_sec - start.tv_sec)+ (float) (end.tv_usec - start.tv_usec) / 100000;
	if (val.block_size == 1000){
		float latency = ((t*1000)/1000000); // time taken transfer 1 KB data in  millisecs;
		float thrtcliops ;//  theoretical throughput / blocksize in MB
		float latencytheortcl;
		printf("\n latency:%f",latency);
		printf("\n time elapsed:%f",t);
		printf("\n IOPS calculation");
		float iops = (1000000)/t;
		printf("\n IOPS:%f",iops);// operations per sec total operations / t;

		if (strcmp(c,"RR")==0||strcmp(c,"RS")==0){
		 thrtcliops = 540*1000; //  theoretical throughput / blocksize in MB
		 latencytheortcl = .5; // in milisecs
		}
		else{
			 thrtcliops = 410*1000; //  theoretical throughput / blocksize in MB
			 latencytheortcl = .5; //in milisecs
		}
		printf("\n writing values to output file");// theoretical latency in milisecs
		if((fout = fopen(argv[2],"a")) != NULL ){
			//printf("writing in file");
			//fprintf(fout,"%s\n","Workload Concurrency BlockSize MyRAMBenchValue TheoreticalValue MyRAMBenchEfficiency");
					fprintf(fout,"\n%lli\t%s\t%d\t%d\t%f\t%f\t%f\t%f\t%f\t%f",filesize,c,val.num_thread,val.block_size/1000,latency,latencytheortcl,(latency/latencytheortcl),iops,thrtcliops,(iops/thrtcliops));
		}
	   else
		   printf("%s\n","cannot open the file");


	}
	else if (val.block_size==(1000*1000)){

		double throuput = (10000/t);
		float thrpttheoretical;// total file size in MB/total time
			printf("\n time elapsed:%f",t);
			printf("\n throughput:%f",throuput);
			//float thrtcliops = 75.98; // for 7.2K SAS drive 1/(((8.5+9.5)/2)/1000) + (4.16/1000)) =75.98.
				if (strcmp(c,"RR")==0||strcmp(c,"RS")==0){
					thrpttheoretical = 540; // theoritical value in MB/sec SATA 3.0 SSD
				}
				else{
					thrpttheoretical = 410; // theoritical value in MB/sec SATA 3.0 SSD
				}

		if((fout = fopen(argv[2],"a")) != NULL ){
						 	 	//printf("writing in file");
			//fprintf(fout,"%s\n","Workload Concurrency BlockSize MyRAMBenchValue TheoreticalValue MyRAMBenchEfficiency");
			fprintf(fout,"\n%lli\t%s\t%d\t%d\t%f\t%f\t%f",filesize,c,val.num_thread,val.block_size/1000,throuput,thrpttheoretical,(throuput/thrpttheoretical) );
			 }
			   else
				   printf("%s\n","cannot open the file");
	}
	else if (val.block_size==(10000*1000)) {

		double throuput = (10000/t);
		float thrpttheoretical;// total file size in MB/total time
					printf("\n time elapsed:%f",t);
					printf("\n throughput:%f",throuput);
					//float thrtcliops = 75.98; // for 7.2K SAS drive 1/(((8.5+9.5)/2)/1000) + (4.16/1000)) =75.98.
					if (strcmp(c,"RR")==0||strcmp(c,"RS")==0){
						thrpttheoretical = 540; // theoritical value in MB/sec SATA 3.0 SSD
					}
					else{
						thrpttheoretical = 410; // theoritical value in MB/sec SATA 3.0 SSD
					}
				if((fout = fopen(argv[2],"a")) != NULL ){
					fprintf(fout,"\n%lli\t%s\t%d\t%d\t%f\t%f\t%f",filesize,c,val.num_thread,val.block_size/1000,throuput,thrpttheoretical,(throuput/thrpttheoretical) );
							 }
					   else
						   printf("%s\n","cannot open the file");
	}
	else if (val.block_size == (100000*1000)) {

		double throuput = (10000/t);
		float thrpttheoretical;// total file size in MB/total time
					printf("\n time elapsed:%f",t);
					printf("\n throughput:%f",throuput);
					//float thrtcliops = 75.98; // for 7.2K SAS drive 1/(((8.5+9.5)/2)/1000) + (4.16/1000)) =75.98.
					if (strcmp(c,"RR")==0||strcmp(c,"RS")==0){
						thrpttheoretical = 540; // theoritical value in MB/sec SATA 3.0 SSD
					}
					else{
						 thrpttheoretical = 410; // theoritical value in MB/sec SATA 3.0 SSD
					}
				if((fout = fopen(argv[2],"a")) != NULL ){
					fprintf(fout,"\n%lli\t%s\t%d\t%d\t%f\t%f\t%f",filesize,c,val.num_thread,val.block_size/1000,throuput,thrpttheoretical,(throuput/thrpttheoretical) );
				 }
				else
				  printf("%s\n","cannot open the file");
	}


	free(val.B);
	fclose(file);
	fclose(fout);
	//return 0;
}

