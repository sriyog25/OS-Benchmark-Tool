#include<stdio.h>
#include<sys/time.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>

#define BLOCK_SIZE 1
#define BLOCK_SIZE_KB 1024
#define BLOCK_SIZE_MB 1024*1024
#define MAX_BYTE 1000000
#define MAX_KB 100000
#define MAX_MB 100

void *block_Byte();
void *block_Kbyte();
void *block_Mbyte();
void *block_Byte_random();
void *block_KByte_random();
void *block_MByte_random();

//Sequential Read & Write for 1 Byte
void *block_Byte()
{
int i;
char *mem = (char *)malloc(MAX_BYTE);
char *mem1 =(char *)malloc(MAX_BYTE);
	for(i=0;i<MAX_BYTE;i++)
		{
		memcpy(mem1, mem, BLOCK_SIZE);
		mem1=mem1+BLOCK_SIZE;
		mem=mem+BLOCK_SIZE;
		}

}

//Random Read & Write for 1 Byte
void *block_Byte_random()
{
	int i,r;
	char *mem = (char *)malloc(MAX_BYTE);
	char *mem1 =(char *)malloc(MAX_BYTE);

	for(i=0;i<MAX_BYTE;i++)
	{
		r = rand()%((BLOCK_SIZE*MAX_BYTE)-BLOCK_SIZE);
		memcpy(&mem1[r],&mem[r],BLOCK_SIZE);
	}
}

//Sequential Read & Write for 1 KB
void *block_Kbyte()
{
	int i;
	char *mem = (char *)malloc(MAX_KB*BLOCK_SIZE_KB);
	char *mem1 =(char *)malloc(BLOCK_SIZE_KB*MAX_KB);
	for(i=0;i<MAX_KB;i++)
	{
	memcpy(mem1, mem, BLOCK_SIZE_KB);
	mem1=mem1+BLOCK_SIZE_KB;
	mem=mem+BLOCK_SIZE_KB;
	}
}

//Random Read & Write for 1 KB
void *block_KByte_random()
{
	int i,r;
	char *mem = malloc(MAX_KB*BLOCK_SIZE_KB);
	char *mem1= malloc(BLOCK_SIZE_KB*MAX_KB);

	for(i=0;i<MAX_KB;i++)
	{
		r = rand()%((MAX_KB*BLOCK_SIZE_KB)-BLOCK_SIZE_KB);
		memcpy(&mem1[r],&mem[r],BLOCK_SIZE_KB);
	}
}

//Sequential Read & Write for 1 MB
void *block_Mbyte()
{
	int i;
	char *mem = malloc(MAX_MB*BLOCK_SIZE_MB);
	char *mem1= malloc(BLOCK_SIZE_MB*MAX_MB);

	for(i=0;i<MAX_MB;i++)
	{
		memcpy(mem1, mem, BLOCK_SIZE_MB);
		mem1=mem1+BLOCK_SIZE_MB;
		mem=mem+BLOCK_SIZE_MB;
	}
}

//Random Read & Write for 1 MB
void *block_MByte_random()
{
	int i,r;
	char *mem = malloc(BLOCK_SIZE_MB*MAX_MB);
	char *mem1=malloc(BLOCK_SIZE_MB*MAX_MB);

	for(i=0;i<MAX_MB;i++)
	{
		r = rand()%((MAX_MB*BLOCK_SIZE_MB)-BLOCK_SIZE_MB);
		memcpy(&mem1[r],&mem[r],BLOCK_SIZE_MB);
	}
}

