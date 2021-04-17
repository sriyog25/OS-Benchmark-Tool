#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>

#define BYTE 1
#define KILOBYTE 1024
#define MEGABYTE 1024*1024
#define MAX_BYTE 10000000
#define MAX_KB 100000
#define MAX_MB 10


double latency;

char * bufferData;

//Read Kilo Byte Block Size Sequentially
void *readKiloByteSequential()
{
	FILE *myfile;
	int i;
	myfile = fopen("Test.txt", "r+");
	fseek(myfile, 0, SEEK_SET);
    	for(i=0;i<MAX_KB;i++)
    	{
		fread(bufferData,1,KILOBYTE,myfile);
    	}
    	fclose(myfile);
}

//Write Kilo Byte Block Size Sequentially
void *writeKiloByteSequential(){
	double cpu_time_used;
	int i;
	FILE *myfile;
	myfile=fopen("Test.txt","a+");
	fseek(myfile,0,SEEK_SET);
	for ( i=0;i<MAX_KB; i++)
	{
		fwrite(bufferData, 1, KILOBYTE, myfile);
	}
	fclose(myfile);
}

//Write Byte Block Size Sequentially
void *writeToFile(){
	int i;
	char c='a';
	FILE *myfile;
	myfile=fopen("Test.txt","w+");

	for ( i=0;i<MAX_BYTE; i++)
	{
		fputc(c,myfile);
	}
	fclose(myfile);
}

//Read Byte Block Size Sequentially
void *readToFile(){
	int i;
	FILE *myfile;
	myfile=fopen("Test.txt","r+");
	fseek(myfile,0,SEEK_SET);
	for ( i=0; i<MAX_BYTE; i++)
	{
		fread(bufferData,1,BYTE,myfile);
	}
	fclose(myfile);
}

//Write Byte Block Size Randomly
void *writeRandomsToFile(){
	int i,s;
	char c='c';
	double cpu_time_used;
	FILE *myfile;
	myfile=fopen("TestRandom.txt","wb");
	for ( i=0; i<MAX_BYTE; i++)
	{
		s=rand()%3000;
		fseek(myfile,s,SEEK_SET);
		fputc(c,myfile);
	}
	fclose(myfile);
}

//Read Byte Block Size Randomly
void *readRandomsToFile(){
	int i,s;
	char buffer[1024*1024];
	FILE *myfile;
	myfile=fopen("TestRandom.txt","r+");
	for ( i=0; i<MAX_BYTE; i++)
	{
		s=rand()%3000;
		fseek(myfile,s,SEEK_SET);
		fread(buffer,1,BYTE,myfile);
	}
	fclose(myfile);
}

//Write Kilo Byte Block Size Randomly
void *writeKiloByteRandom()
{
	FILE *myfile;
	int i,j;
	myfile = fopen("file.txt", "w+");
    	for(i=0;i<MAX_KB;i++)
    	{
    		int r=rand()%KILOBYTE;
	    	fseek(myfile,r,SEEK_SET);
    		fwrite(bufferData, 1, KILOBYTE, myfile);
    	}
    	fclose(myfile);
}

//Write Mega Byte Block Size Sequentially
void *writeMegaByteSequential()
{
	FILE *myfile;
	int i,j;
	myfile = fopen("Test.txt", "w+");
    	for(i=0;i<MAX_MB;i++)
    	{
    		fwrite(bufferData, 1, MEGABYTE, myfile);
    	}
    	fclose(myfile);
}

//Read Mega Byte Block Size Randomly
void *readMegaByteRandom()
{
	FILE *myfile;
	int i;
	myfile = fopen("Test.txt", "r+");
    	for(i=0;i<MAX_MB;i++)
    	{
    		int r=rand()%MEGABYTE;
	    	fseek(myfile,r,SEEK_SET);
    		fread(bufferData, 1,MEGABYTE, myfile);
    	}
    	fclose(myfile);
}

//Read Kilo Byte Block Size Randomly
void *readKiloByteRandom()
{
	FILE *myfile;
	int i;
	myfile = fopen("Test.txt", "r+");
    	for(i=0;i<MAX_KB;i++)
    	{
    		int r=rand()%KILOBYTE;
	    	fseek(myfile,r,SEEK_SET);
    		fread(bufferData,1, KILOBYTE,myfile);
    	}
    	fclose(myfile);
}

//Write Mega Byte Block Size Sequentially
void *readMegaByteSequential()
{
	FILE *myfile;
	int i;
	myfile = fopen("Test.txt", "r+");
    	for(i=0;i<MAX_MB;i++)
    	{
    		fread(bufferData, 1,MEGABYTE, myfile);
    	}
    	fclose(myfile);
}

//Write Mega Byte Block Size Randomly
void *writeMegaByteRandom()
{
	FILE *myfile;
	int i,j;
	myfile = fopen("file.txt", "w+");
    	for(i=0;i<MAX_MB;i++)
    	{
    		int r=rand()%MEGABYTE;
	    	fseek(myfile,r,SEEK_SET);
    		fwrite(bufferData, 1, MEGABYTE, myfile);
    	}
    	fclose(myfile);
}
