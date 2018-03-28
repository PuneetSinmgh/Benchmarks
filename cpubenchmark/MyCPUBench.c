#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<time.h>
#include<pthread.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<immintrin.h>

int * workload_QP(void* nthred){

	char A='a', B='b';
//	char X;
	int *p = (int*)nthred;
//	printf("%s\n","threads running");
//	for(long double var = 0; var < (1000*1000*1000/ *p ); ++var) {
//			A=A+1;
//			B=B+1;
//			X= A+B;
//			C=3*X;
//		}
	__m256i a = _mm256_set1_epi8(A);
	__m256i b = _mm256_set1_epi8(B);

	long long int itr = 7812500000LL;

	for (long long int i=0;i<(itr/ *p);i++){

	  __m256i c = _mm256_add_epi8(a,b);
	  __m256i d = _mm256_add_epi8(a,b);
	  __m256i e = _mm256_add_epi8(a,b);
	  __m256i f = _mm256_add_epi8(a,b);
	}

	return 0;
}

int * workload_HP(void* nthred){

	short A=1, B=2;
//	short int X;
	int *p = (int*)nthred;
//	printf("%s\n","threads running");
//	for(long double var = 0; var < (1000*1000*1000/ *p ); ++var) {
//			A=A+1;
//			B=B+1;
//			X= A+B;
//			C=3*X;
//		}

	__m256i a = _mm256_set1_epi16(A);
	__m256i b = _mm256_set1_epi16(B);

	long long int itr = 15625000000LL;

	for (long long int i=0;i<(itr/ *p);i++){

	  __m256i c = _mm256_add_epi16(a,b);
	  __m256i d = _mm256_add_epi16(a,b);
	  __m256i e = _mm256_add_epi16(a,b);
	  __m256i f = _mm256_add_epi16(a,b);
	}
	return 0;
}

int * workload_SP(void* nthred){

//	int A=1, B=2, C;
//	int X;
	int *p = (int*)nthred;
//	printf("%s\n","threads running");
//	for(long double var = 0; var < (1000*1000*1000/ *p ); ++var) {
//			A=A+1;
//			B=B+1;
//			X= A+B;
//			C=3*X;

	__m256 a = _mm256_set_ps(1.0,1.0,2.0,2.0,3.0,3.0,4.0,4.0);
	__m256 b = _mm256_set_ps(5.0,5.0,6.0,6.0,7.0,7.0,8.0,8.0);
	__m256 c = _mm256_set_ps(3.0,6.0,6.0,2.0,7.0,5.0,8.0,9.0);

	long long int itr = 31500000000LL;

	for (long long int i=0;i<(itr/ *p);i++){

	  __m256 d = _mm256_fmadd_ps(a,b,c);
	  __m256 e = _mm256_fmadd_ps(a,b,c);
	}

	return 0;
}

int * workload_DP(void* nthred){

//	double A=0, B=1,C;
	//double X;
	int *p = (int*)nthred;
	//printf("%s\n","threads running_DP");
	//for(long double var = 0; var < (1000*1000*1000/ *p ); ++var) {
		///A=A+1;
	//	B=B+1;
	//	X= A+B;
	//	C=3*X;
//	}

	//__m256d a , b, c;

	__m256d a = _mm256_set_pd(1.1,2.2,3.3,4.4);
	__m256d b = _mm256_set_pd(5.5,6.6,7.7,8.8);
	__m256d c = _mm256_set_pd(3.6,6.2,7.5,8.9);

	long long int itr = 62500000000LL;

	for (long long int i=0;i<(itr/ *p);i++){

	  __m256d d = _mm256_fmadd_pd(a,b,c);
	  __m256d e = _mm256_fmadd_pd(a,b,d);
	}

	return 0;
}


int main(int argc, char *argv[]){


	//char type[5];
	int num_thread;

	pthread_t ptrs[5];
	FILE * file, *fout;
	char c[2] ;
	int rc,i;
	struct timeval start,end;
	//float t;


	   if((file = fopen(argv[1],"r")) != NULL ){
		   fscanf(file, "%s",c);
		   printf("%s\n", c);
		   fscanf(file, "%d", &num_thread);
		   printf("%d\n", num_thread);
	    }
	   else
		   printf("%s\n","cannot open the file");

	   gettimeofday(&start,NULL);


		if (strcmp(c,"QP")==0){
			for(i=0; i<num_thread;i++){
			   printf("create thread");
			   rc=pthread_create( &ptrs[i],NULL,workload_QP,(void*) &num_thread);
			   printf("%s%d\n","thread:",i);
			   if (rc)
					printf("%s\n", "could not create thread");
			}
		}
		else if (strcmp(c,"HP")==0) {
			for(i=0; i<num_thread;i++){
				printf("create thread");
				rc=pthread_create( &ptrs[i],NULL,workload_HP,(void*) &num_thread);
				printf("%s%d\n","thread:",i);
				if (rc)
					printf("%s\n", "could not create thread");
			}
		}
		else if (strcmp(c,"SP")==0) {
			for(i=0; i<num_thread;i++){
				printf("create thread");
				rc=pthread_create( &ptrs[i],NULL,workload_SP,(void*) &num_thread);
				printf("%s%d\n","thread:",i);
				if (rc)
					printf("%s\n", "could not create thread");
			}
		}
		else if (strcmp(c,"DP")==0) {
			for(i=0; i<num_thread;i++){
			   printf("create thread");
			   rc=pthread_create( &ptrs[i],NULL,workload_DP,(void*) &num_thread);
			   printf("%s%d\n","thread:",i);
			   if (rc)
					printf("%s\n", "could not create thread");
				}
		}

		else {
			printf("invalid input");
		}

		for(i=0; i<num_thread;i++){

			rc=pthread_join(ptrs[i],NULL);
			if (rc)
				printf("%s\n", "could not join thread");
		}
		gettimeofday(&end,NULL);

		float t = (float)(end.tv_sec-start.tv_sec)+(float)(end.tv_usec-start.tv_usec)/100000 ;
		printf("time elapsed:%f",t);

		int noofprocessors =2;
		int flopspercycle;
		int clockfrequency = 2.1;
		float actualperformance;
		long long int Giga = 1000000000LL;
		float theoriticalperformance;
		long long int workload = 1000000000000LL;
		if (strcmp(c, "QP")){
			flopspercycle = 128;
			theoriticalperformance = noofprocessors*flopspercycle*clockfrequency;

			actualperformance = (workload/Giga)/t;
		}
		else if (strcmp(c,"HP")) {
			flopspercycle = 64;
			theoriticalperformance = noofprocessors*flopspercycle*clockfrequency;
			actualperformance = (workload/Giga)/t;
		}

		else if (strcmp(c,"SP")) {
			flopspercycle = 32;
			theoriticalperformance = noofprocessors*flopspercycle*clockfrequency;

			actualperformance = (workload/Giga)/t;
		}

		else if (strcmp(c,"DP")) {
			flopspercycle = 16;
			theoriticalperformance = noofprocessors*flopspercycle*clockfrequency;

			actualperformance = (workload/Giga)/t;
		}


		printf("theoritical performance:%f\n actual:%f",theoriticalperformance,actualperformance);
		 if((fout = fopen(argv[2],"a")) != NULL ){
			 	 	printf("writing in file");
			 	 	//fprintf("%s","");
			 	 	//long long int workload = 1000*1000*1000;
			 	 	fprintf(fout,"\n%lli\t%s\t%d\t%f\t%f\t%f",workload,c,num_thread,actualperformance,theoriticalperformance,(actualperformance/theoriticalperformance) );
			    }
			   else
				   printf("%s\n","cannot open the file");


}

