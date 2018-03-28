#include <stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>


struct inputs {
	int num_thread;
	int block_size;
	char *A, *B;
	int offset[8];
	int threadid;
	long int sizeperthread;
	int serv_socket[8], * client_socket[8];
};

int *send_data(void* val) {

	struct inputs * input_values = (struct inputs*) val;
		int nthreads = input_values->num_thread;
		int blocksize = input_values->block_size;
		int k,rand;
		printf("values%d,%d", nthreads, blocksize);
		int server_sock = input_values->serv_socket[input_values->threadid];
		long long int i;
		char *send_buff = (char *)malloc(blocksize);
		memset(send_buff,'a',blocksize);
		int noofblocks = input_values->sizeperthread/input_values->block_size;

		for (int j = 1; j <= 100; j++) {

			for (i =input_values->offset[input_values->threadid]; i < input_values->offset[input_values->threadid]+input_values->sizeperthread ; i=i+blocksize ) {

				send (server_sock,send_buff, blocksize,0);
			}
			//printf("\n%d",i*blocksize);
		}

}

int *recv_data(void* val) {

	struct inputs * input_values = (struct inputs*) val;
		int nthreads = input_values->num_thread;
		int blocksize = input_values->block_size;
		int k,rand;
		printf("values%d,%d", nthreads, blocksize);
		//int client_sock = *input_values->client_socket[input_values->threadid];
		char *recv_buff = (char *)malloc(blocksize);
		int noofblocks = input_values->sizeperthread/input_values->block_size;
		long long int i;
		for (int j = 1; j <= 100; j++) {

			for ( i =input_values->offset[input_values->threadid]; i < input_values->offset[input_values->threadid]+input_values->sizeperthread ; i=i+blocksize ) {


				recv(*input_values->client_socket[input_values->threadid],recv_buff,blocksize,0);
			}
			//printf("\n%d",i*blocksize);

		}
}

int * server_ping(void * val){

//	char *send_buff = (char *)malloc(1);
	char *recv_buff = (char *)malloc(1);
	struct inputs * input_values = (struct inputs*) val;
	//memset(send_buff,'a',1);
	long int itr= (1000000)/input_values->num_thread;
	int i=0;
	printf("server ping");
	while(i<itr){

		recv(*input_values->client_socket[input_values->threadid],recv_buff,sizeof(char),0);

		send(*input_values->client_socket[input_values->threadid],recv_buff,sizeof(char),0);
		i++;
	}

	printf("value of itr:%d",i);
	return 0;
}

int * client_pong(void * val){

	char *send_buff = (char *)malloc(1);
	//char *recv_buff = (char *)malloc(1);
	struct inputs * input_values = (struct inputs*) val;
	memset(send_buff,'a',1);
	int server_sock = input_values->serv_socket[input_values->threadid];
	long int itr= (1000000)/input_values->num_thread;
	int i=0;
	printf("client pong");
	while(i<itr){

		send(server_sock,send_buff,sizeof(char),0);

		recv(server_sock,send_buff,sizeof(char),0);
		i++;
	}
	printf("value of itr:%d",i);
	return 0;


//	return 0;
}

void tcp_server(char * s){

	char buffer[1024];
	struct sockaddr_in server_sock_add, client;

	pthread_t ptrs[8];
			FILE * file, *fout;
			char c[3] ;
			int rc,i;
			struct timeval start,end;
			struct inputs val;

			if((file = fopen(s,"r")) != NULL ){
					   fscanf(file, "%s",c);
					   printf("%s\n", c);
					   fscanf(file, "%d",&val.block_size);
					   printf("%d\n", val.block_size);
					   fscanf(file, "%d", &val.num_thread);
					   printf("%d\n", val.num_thread);
				    }
				   else
					   printf("%s\n","cannot open the file");

			long long int G = 1000000000LL;

		 	 val.sizeperthread = G/val.num_thread;


			val.B = (char *) malloc(G);
			if (val.B==NULL){
				printf ("cannot assigned");
			}

	int serv_socket = socket(AF_INET,SOCK_STREAM,0);
	if (serv_socket!=0){
		printf("server socket successfully created\n");
	}

	memset(&server_sock_add,'0',sizeof(server_sock_add));
	//memset(buffer, 0, 1024);

	server_sock_add.sin_family = AF_INET;					// define domain used ipv4 or ipv6
	server_sock_add.sin_addr.s_addr = htonl(INADDR_ANY);    // permit any incoming address
	server_sock_add.sin_port = htons(5000);

	if(bind(serv_socket,(struct sockaddr*)&server_sock_add,sizeof(server_sock_add))<0){     //bind the socket to address specified in server_sock_add and port no specified
		printf("\n could not bind socket:");
		close(serv_socket);
		//return 0;
	}

	if(listen(serv_socket,10)==-1){
		printf("failed to listen");
		close(serv_socket);
		//return -1;
	}


	gettimeofday(&start,NULL);

int client_socket;

	for (i = 0; i < val.num_thread; i++) {
		client_socket = accept(serv_socket,(struct sockaddr*)NULL,NULL);
			if(client_socket<0){
				printf("could not accept");
			}
				printf("client accepted:%d",i);
				val.client_socket[i] = (int *)malloc(1);
				*val.client_socket[i]= client_socket;
			   			printf("create thread");
			   			val.threadid=i;					//thread id
			   			val.offset[i]=val.sizeperthread*i;


			   			if (val.block_size==1){
			   				rc = pthread_create(&ptrs[i], NULL, (void *)&server_ping,(void*) &val);
			   				printf("%s%d\n", "thread:", i);
			   				if (rc)
			    				printf("%s\n", "could not create thread");
			   			}
			   			else{

			   			rc = pthread_create(&ptrs[i], NULL, (void *)&recv_data,(void*) &val);
			   			printf("%s%d\n", "thread:", i);
			   			if (rc)
			   				printf("%s\n", "could not create thread");
			   		}
				}
			   for (i = 0; i < val.num_thread; i++) {
					   		rc = pthread_join(ptrs[i], NULL);
					   		if (rc)
					   			printf("%s\n", "could not join thread");
					   	}

			   printf("data received from client");
	close(val.serv_socket);
	for (i = 0; i < val.num_thread; i++) {
	close(*val.client_socket[i]);
	}
	free(val.B);

	}


void tcp_client(char * server,char *s,char * out){

	int new_con;
	char buffer[1024];
	struct sockaddr_in server_sock_add;

	int num_thread;

		pthread_t ptrs[8];
		FILE * file, *fout;
		char c[3] ;
		int rc,i;
		struct timeval start,end;
		struct inputs val;

		if((file = fopen(s,"r")) != NULL ){
				   fscanf(file, "%s",c);
				   printf("%s\n", c);
				   fscanf(file, "%d",&val.block_size);
				   printf("%d\n", val.block_size);
				   fscanf(file, "%d", &val.num_thread);
				   printf("%d\n", val.num_thread);
			    }
			   else
				   printf("%s\n","cannot open the file");

		long long int G = 1000000000LL;

	 	val.sizeperthread = G/val.num_thread;

		val.A = (char *) malloc(G);
		if (val.A==NULL){
			printf ("cannot assigned");
		}


	memset(buffer, 0, 1024);
	memset(val.A,'A',G);

	// hostname of server is in server string passed extract IP using gethostbyname

	struct hostent *server_info = gethostbyname(server);
	struct in_addr **addresses = (struct in_addr **)server_info->h_addr_list;
	char ip[16];

	for(int i=0; addresses[i]!=NULL;i++){

	strcpy(ip,inet_ntoa(*addresses[i]));
		printf("%s", ip);
		break;
	}


	server_sock_add.sin_family = AF_INET;					// define domain used ipv4 or ipv6
	server_sock_add.sin_addr.s_addr = inet_addr(ip);    // use localhost as server ip // how to identify
	server_sock_add.sin_port = htons(5000);



  for (i = 0; i < val.num_thread; i++) {


	val.serv_socket[i] = socket(AF_INET,SOCK_STREAM,0);
	if (val.serv_socket[i]>0){
		printf("client socket successfully created\n");
	}
  }
	gettimeofday(&start,NULL);

	for (i = 0; i < val.num_thread; i++) {
	new_con = connect(val.serv_socket[i],(struct sockaddr*)&server_sock_add,sizeof(server_sock_add));
	if(new_con<0){
		printf("could not connect to server");
	}
					printf("\nconnected to client:%d",i);
		  		   	printf("\ncreate thread");
		   			val.threadid=i;					//thread id
		   			val.offset[i]=val.sizeperthread*i;

		   			if(val.block_size==1){

		   				rc = pthread_create(&ptrs[i], NULL, (void *)&client_pong,(void*) &val);
		   	  			printf("%s%d\n", "thread:", i);
		   	   			if (rc)
		   	   				printf("%s\n", "could not create thread");
		   			}
		   			else{

		   			rc = pthread_create(&ptrs[i], NULL, (void *)&send_data,(void*) &val);
		   			printf("%s%d\n", "thread:", i);
		   			if (rc)
		   				printf("%s\n", "could not create thread");
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
		   			float latency = (t*1000)/1000000; // in milli secs
		   			printf("\n latency:%f",latency);
		   			printf("\n time elapsed:%f",t);
		   			float latencytheortcl = 0.0007; // in milisecs
		   			if((fout = fopen(out,"a")) != NULL ){
		   				//printf("writing in file");
		   				//fprintf(fout,"%s\n","Protocol Concurrency BlockSize MyNETBenchValue TheoreticalValue MyNETBenchEfficiency");
		   						fprintf(fout,"\n%s\t%d\t%d\t%f\t%f\t%f",c,val.num_thread,val.block_size,latency,latencytheortcl,(latency/latencytheortcl) );	    }
		   		   else
		   			   printf("%s\n","cannot open the file");


		   		}
		   		else{

		   			float throuput = ((800*G)/(1000000*t)); // in Gbps gigabits persecs
		   					   	printf("time elapsed:%f",t);
		   					   	printf("throughput:%f",throuput);
		   					   	float thrpttheoritical = 56000; //
		   			if((fout = fopen(out,"a")) != NULL ){
		   							 	 	//printf("writing in file");
		   				//fprintf(fout,"%s\n","Workload Concurrency BlockSize MyRAMBenchValue TheoreticalValue MyRAMBenchEfficiency");
		   				fprintf(fout,"\n%s\t%d\t%d\t%f\t%f\t%f",c,val.num_thread,val.block_size,throuput,thrpttheoritical,(throuput/thrpttheoritical) );
		   				 }
		   				   else
		   					   printf("%s\n","cannot open the file");
		   		}




	close(val.serv_socket);
	close(new_con);
	free(val.A);

}


int main(int argc, char *args[]) {

		if (strcmp(args[1],"s")==0){
			tcp_server(args[2]);
		}
		else
			tcp_client(args[2],args[3],args[4]);

	return EXIT_SUCCESS;
}
