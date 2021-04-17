#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

#define ITERATION 1000000000

struct arg_struct {
	int thread_id;
};

double b[4];
double c[4];

//thread function for multiple operations
void *threadFunctionIopsCal(void *arg)
{
	volatile int i;
	int a=5;
	for(i = 0; i < ITERATION; i++)
    	{
        	a =0+2+3+5+6+3+1+1+7+5+1+2+2+3+6+8+1+2+9+1+6+1+9;
    	}
	return NULL;
}

//thread function for multiple operations
void *threadFunctionFlopCal(void *arg)
{
	volatile int i;
	double a;
	for(i = 0; i < ITERATION; i++)
    	{
        	a =0.5+2+3+5+6+3+1+1+7+5+1+2+2+3+6+8+1+2+9+1+6+1+9;
    	}
	return NULL;
}

// thread function to calculate Flops
void *threadFunctionFlop(void *arg)
{
	int index= *(int *)arg;
	double a;
	while(1)
    	{
		a =0.5+2+3+5+6+3+1+1+7+5+1+2+2+3+6+8+1+2+9+1+6+1+9;
		b[index]=b[index]+23;
	}
	return NULL;
}

// thread function to calculate Iops
void *threadFunctionIops(void *arg)
{
	int index= *(int *)arg;
	int a;
	while(1)
    	{
		a =0+2+3+5+6+3+1+1+7+5+1+2+2+3+6+8+1+2+9+1+6+1+9;
		c[index]=c[index]+23;
	}

	return NULL;
}

//Calculates the GIOPS
void *iopsCal(int numberOfThreads)
{
	volatile int i;
	int a;
	clock_t start, end;
	struct arg_struct args;
	pthread_t th[10];
	printf("\nFinding GIOPS for %d threads",numberOfThreads);
	double cpu_time_used, time_in_sec;
	start = clock();
	for(i=0;i<numberOfThreads;i++)
	{
		pthread_create(&th[i],NULL,threadFunctionIopsCal,(void *)&args);
		pthread_join(th[i], NULL);
	}
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\nTime taken in: %f seconds\n",cpu_time_used);
	double count=23;
	double Iops=(double)( numberOfThreads * count *(ITERATION/cpu_time_used));
    	double gIops=(double)Iops/1000000000;
	printf("GIOPS : %f\n",gIops);
	return NULL;
}

//Calculates 600 GFLOPS per second and stores in CPU_Log.txt
void flops(int numberOfThreads)
{
	FILE *fp;
	fp= fopen("CPU_Log.txt","a+");
	int i=0;
    	pthread_t th[10];
	struct arg_struct args;
  	int a[4];
	for(i=0;i<4;i++)
	{
		b[i]=0;
		a[i]=i;
	}
	printf("\nFinding 600 sec samples for GFLOPS %d threads",numberOfThreads);
	for(i=0;i<numberOfThreads;i++)
	{
		pthread_create(&th[i],NULL,threadFunctionFlop,&a[i]);
	}
	for(i=0;i<600;i++)
	{
		sleep(1);
		fprintf(fp,"%lf\n",((double)(b[0]+b[1]+b[2]+b[3]))/1000000000);
		b[0]=b[1]=b[2]=b[3]=0;
	}
	fclose(fp);
	for(i=0;i<numberOfThreads;i++)
	{
		pthread_kill(&th[i],1);//kills the thread
	}
	printf("600 Samples Experiment for GFLOPS Done");
}

//calculates the GFLOPS
void flopsCal(int numberOfThreads)
{
	clock_t start, end;
	double cpu_time_used;
	volatile int i;
    	struct arg_struct args;
    	pthread_t th[10];
	printf("\nFinding GFLOPS for %d threads",numberOfThreads);
	start = clock();
	for(i=0;i<numberOfThreads;i++)
	{
		pthread_create(&th[i],NULL,threadFunctionFlopCal,(void *)&args);
		pthread_join(th[i], NULL);
	}
    	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	double count=23;
    	printf("\nTime: %f sec\n",cpu_time_used);
    	double Flops=(double)( numberOfThreads * count *(ITERATION/cpu_time_used));
    	double gFlops=(double)Flops/1000000000;
    	printf("GFLOPS : %lf\n",gFlops);
}

//Calculates 600 GIOPS per second and stores in CPU_IOPS.txt
void iops(int numberOfThreads)
{

	FILE *fp;
	fp= fopen("CPU_IOPS.txt","a+");
	int i=0;
	struct arg_struct args;
    	pthread_t th[10];
	int a[4];
	for(i=0;i<4;i++)
	{
		c[i]=0;
		a[i]=i;
	}
	printf("\nProgram to find IOPS for %d threads",numberOfThreads);
	for(i=0;i<numberOfThreads;i++)
	{
		pthread_create(&th[i],NULL,threadFunctionIops,&a[i]);
	}
	for(i=0;i<600;i++)
	{
		sleep(1);
		fprintf(fp,"%lf\n",((double)(c[0]+c[1]+c[2]+c[3]))/1000000000);
		c[0]=c[1]=c[2]=c[3]=0;
	}
	fclose(fp);
	for(i=0;i<numberOfThreads;i++)
	{
		pthread_kill(&th[i],1);
	}
	printf("600 Samples Experiment for GIOPS Done");
}


