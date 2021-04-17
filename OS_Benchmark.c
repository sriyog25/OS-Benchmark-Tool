#ifdef _unix_
#include <unistd.h>
#elif defined _WIN32
#include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif

#include "CPUBenchmark.c"
#include "MemoryBenchmark.c"
#include "RAMBenchmark.c"
#include <stdio.h>

int main()
{
    printf("----------------Welcome To OS Benchmark-------------\n");
    while(1)
    {
        int c;
        char flag;
        printf("\nDo you want to run a Complete Benchmark (Y/N) ");
        scanf("%s",&flag);
        if(flag=='N')
        {
        printf("\n\n-------Field Of Comparison---------\n");
        printf("1.CPU Benchmarking \n");
        printf("2.Memory Benchmarking \n");
        printf("3.RAM benchmarking \n");
        printf("4.EXIT \n");
        printf("Enter the choice ");
        scanf("%d",&c);
        }
        else
        {
            c=1;
        }
        switch(c)
        {
            case 1: printf("------CPU Benchmarking------\n");
                    while(1){
                    int numberOfThreads;

                        printf("\nEnter the no of threads to be used:(1/2/4) or (Enter 8 for 600 seconds test or 0 Exit: ");
                        scanf("%d",&numberOfThreads);

                        if(numberOfThreads!=1 && numberOfThreads!=2 && numberOfThreads!=4 && numberOfThreads!=0 && numberOfThreads!=8)
                        {
                        printf("\nInvalid choice..Please enter again");
                        }
                    else if(numberOfThreads==8)
                        {
                        flops(4);
                        iops(4);
                        }
                        else if(numberOfThreads==0)
                        {
                        break;
                        }
                        else
                        {
                        flopsCal(numberOfThreads);
                        iopsCal(numberOfThreads);
                        }
                    }
                    if(flag=='N')
                    {
                      break;
                    }
            case 2:printf("\n-----Memory Benchmarking-----\n");
                    clock_t start, end;
                double latency,throughput,total_mb;
                double time;
                pthread_t th[10];
                int i;
                int ch,nthread;
                while(1)
                {
                printf("\n\n1.BYTE\n2.KILOBYTE\n3.MEGABYTE\n4.EXIT\nEnter the Block size\n");
                scanf("%d",&ch);
                if(ch==4)
                {
                    break;
                    printf("\n");
                }
                printf("\nEnter the number of threads(1/2) :\n");
                scanf("%d",&nthread);
                switch (ch)
                {
                    case 1:
                         // Sequential Memory Read+Write
                    printf("\nByte Read+Write for %d thread",nthread);
                    printf("\n--Sequential Read+Write--\n");
                    printf("-------------------------------------");
                    start = clock();
                    for(i=0;i<nthread;i++)
                    {
                        pthread_create(&th[i],NULL,block_Byte,NULL);
                        pthread_join(th[i], NULL);
                    }

                    end=clock();
                    total_mb=(nthread * BLOCK_SIZE * MAX_BYTE)/1000000;
                    time=((double) (end-start))/ CLOCKS_PER_SEC;
                    latency= (time*1000)/total_mb;
                        printf("\nLatency : %f ms",latency);
                        throughput=total_mb/time;
                        printf("\nThroughput:%f MB/s",throughput);

                    // Random Memory Read+Write

                    printf("\n\n--Random Read+Write--\n");
                    printf("-------------------------------------");
                    start=clock();
                    for(i=0;i<nthread;i++)
                    {
                        pthread_create(&th[i],NULL,block_Byte_random,NULL);
                        pthread_join(th[i], NULL);
                    }
                    end=clock();
                    total_mb=(nthread * BLOCK_SIZE * MAX_BYTE)/1000000;
                    time=((double) (end-start))/ CLOCKS_PER_SEC;
                    latency= (time*1000)/total_mb;
                        printf("\nLatency : %f ms",latency);
                        throughput=total_mb/time;
                        printf("\nThroughput:%f MB/s",throughput);
                    break;

                    case 2:
                    //Sequential Memory Read+Write for KB block

                    printf("\n\nKiloByte Read+Write for %d thread ",nthread);
                    printf("\n--Sequential Read+Write--\n");
                    printf("-------------------------------------");
                    start = clock();
                    for(i=0;i<nthread;i++)
                    {
                        pthread_create(&th[i],NULL,block_Kbyte,NULL);
                        pthread_join(th[i], NULL);
                    }
                    end=clock();
                    total_mb=(nthread * BLOCK_SIZE_KB * MAX_KB)/1000000;
                    time=((double) (end-start))/ CLOCKS_PER_SEC;
                    latency= (time*1000)/total_mb;
                        printf("\nLatency : %f ms",latency);
                        throughput=total_mb/time;
                        printf("\nThroughput:%f MB/s",throughput);


                    //Random Memory Read+Write for KB block

                    printf("\n\n--Random Read+Write--\n");
                    printf("-------------------------------------");
                    start= clock();
                    for(i=0;i<nthread;i++)
                    {

                        pthread_create(&th[i],NULL,block_KByte_random,NULL);
                        pthread_join(th[i], NULL);
                    }
                    end=clock();
                    total_mb=(nthread * BLOCK_SIZE_KB * MAX_KB)/1000000;
                    time=((double) (end-start))/ CLOCKS_PER_SEC;
                    latency= (time*1000)/total_mb;
                        printf("\nLatency : %f ms",latency);
                        throughput=total_mb/time;
                        printf("\nThroughput:%f MB/s",throughput);
                    break;

                    case 3:

                    //Sequential Memory Read+Write

                    printf("\nMegaByte read+write for %d thread",nthread);
                    printf("\n--Sequential Read+Write--\n");
                    printf("-------------------------------------");
                    start = clock();
                    for(i=0;i<nthread;i++)
                    {
                        pthread_create(&th[i],NULL,block_Mbyte,NULL);
                        pthread_join(th[i], NULL);
                    }

                    end=clock();
                    total_mb=(nthread * BLOCK_SIZE_MB * MAX_MB)/1000000;
                    time=((double) (end-start))/ CLOCKS_PER_SEC;
                    latency= (time*1000)/total_mb;
                        printf("\nLatency : %f ms",latency);
                        throughput=total_mb/time;
                        printf("\nThroughput:%f MB/s",throughput);


                    //Random Memory Read+Write

                    printf("\n\n--Random read+write--\n");
                    printf("-------------------------------------");
                    start = clock();
                    for(i=0;i<nthread;i++)
                    {
                        pthread_create(&th[i],NULL,block_MByte_random,NULL);
                        pthread_join(th[i], NULL);
                    }
                    end=clock();
                    total_mb=(nthread * BLOCK_SIZE_MB * MAX_MB)/1000000;
                    time=((double) (end-start))/ CLOCKS_PER_SEC;
                    latency= (time*1000)/total_mb;
                        printf("\nLatency : %f ms",latency);
                        throughput=total_mb/time;
                        printf("\nThroughput:%f MB/s",throughput);

                    break;
                    default:printf("\nPlease enter a valid option..\n");
                }
            }
            if(flag=='N')
                    {
                      break;
                    }

            case 3:printf("-----RAM Benchmarking-----\n");
                    int nthread1, j,k;
                    int chr;
                    bufferData= (char *)malloc(1024*1024);
                    clock_t start1, end1;
                    double time1;
                    double l, l1, throughput1;
                    double total_mb1;
                    for(k=0;k<(1024*1024);k++)
                    {
                    bufferData[k]='S';
                    }
                    pthread_t th1[4];
                    while(1)
                    {

                    printf("\n\n-------Block Size--------\n");
                    printf("1.Byte\n");
                    printf("2.Kilo Byte\n");
                    printf("3.Mega Byte\n");
                    printf("4.EXIT\n");
                    printf("\nEnter your choice :");
                    scanf("%d",&chr);
                    if(chr==4)
                        {
                            break;
                        }
                    switch(chr)
                    {
			case 1 : printf("\n\nBlock size selected is 1 Byte");
					printf("\n\nEnter the number of threads(1/2) :\n");
					scanf("%d",&nthread1);
					start1=clock();
					for(j=0;j<nthread1;j++)
						{
							pthread_create(&th1[j],NULL,writeToFile,NULL);
							pthread_join(th1[j], NULL);
						}
					end1=clock();
					time1=((double) (end1-start1))/ CLOCKS_PER_SEC;
					total_mb1=(nthread1 * MAX_BYTE * BYTE)/1000000;
					throughput1=total_mb1/time1;
					printf("\n\nSEQUENTIAL WRITE");
					printf("\nThroughput:%f MB/s",throughput1);
					l= (time1)*1000/total_mb1;
					printf("\nLatency : %f ms",l);

    					start1=clock();
					for(j=0;j<nthread1;j++)
						{
							pthread_create(&th1[j],NULL,readToFile,NULL);
							pthread_join(th1[j], NULL);
						}
					end1=clock();
					time1=((double) (end1-start1))/ CLOCKS_PER_SEC;
					total_mb1=(nthread1 * BYTE * MAX_BYTE)/1000000;
					throughput1=total_mb1/time1;
					printf("\n\nSEQUENTIAL READ");
					printf("\nThroughput:%f MB/s",throughput1);
					l1= (time1)*1000/total_mb1;
					printf("\nLatency : %f ms",l1);

					start1=clock();
					for(j=0;j<nthread1;j++)
						{
							pthread_create(&th1[j],NULL,writeRandomsToFile,NULL);
							pthread_join(th1[j], NULL);
						}
					end1=clock();
					time1=((double) (end1-start1))/ CLOCKS_PER_SEC;
					total_mb1=(nthread1 * BYTE * MAX_BYTE)/1000000;
					throughput1=total_mb1/time1;
					printf("\n\nRANDOM WRITE");
					printf("\nThroughput:%f MB/s",throughput1);
					l= (time1)*1000/total_mb1;
					printf("\nLatency : %f ms",l);

					start1=clock();
					for(j=0;j<nthread1;j++)
						{
							pthread_create(&th1[j],NULL,readRandomsToFile,NULL);
							pthread_join(th1[j], NULL);
						}
					end1=clock();
					time1=((double) (end1-start1))/ CLOCKS_PER_SEC;
					total_mb1=(nthread1 * BYTE * MAX_BYTE)/1000000;
					throughput1=total_mb1/time1;
					printf("\n\nRANDOM READ");
					printf("\nThroughput:%f MB/s",throughput1);
					l1= (time1)*1000/total_mb1;
					printf("\nLatency : %f ms",l1);

						break;

		case 2: printf("\n\nBlock size selected is KILOBYTE");

					printf("\n\nEnter the number of threads(1/2) :\n");
					scanf("%d",&nthread1);
					start1=clock();
					for(j=0;j<nthread1;j++)
						{
							pthread_create(&th1[j],NULL,writeKiloByteSequential,NULL);
							pthread_join(th1[j], NULL);
						}
					end1=clock();
					time1=((double) (end1-start1))/ CLOCKS_PER_SEC;

					total_mb1=(nthread1 * KILOBYTE * MAX_KB)/1000000;
					throughput1=total_mb1/time1;
					printf("\n\nSEQUENTIAL WRITE 1KB");
					printf("\nThroughput:%f MB/s",throughput1);
					l= (time1)*1000/total_mb1;
					printf("\nLatency : %f ms",l);

    					start1=clock();
					for(j=0;j<nthread1;j++)
						{
							pthread_create(&th1[j],NULL,readKiloByteSequential,NULL);
							pthread_join(th1[j], NULL);
						}
					end1=clock();
					time1=((double) (end1-start1))/ CLOCKS_PER_SEC;
					total_mb1=(nthread1 * KILOBYTE * MAX_KB)/1000000;
					throughput1=total_mb1/time1;
					printf("\n\nSEQUENTIAL READ");
					printf("\nThroughput:%f MB/s",throughput1);
					l1= (time1)*1000/total_mb1;
					printf("\nLatency : %f ms",l1);
					start1=clock();
					for(j=0;j<nthread1;j++)
						{
							pthread_create(&th1[j],NULL,writeKiloByteRandom,NULL);
							pthread_join(th1[j], NULL);
						}
					end1=clock();
					total_mb1=(nthread1 * KILOBYTE * MAX_KB)/1000000;
					time1=((double) (end1-start1))/ CLOCKS_PER_SEC;

					printf("\n\nRANDOM WRITE 1KB");
					throughput1=total_mb1/time1;
					printf("\nThroughput:%f MB/s",throughput1);
					l= (time1*1000)/total_mb1;
					printf("\nLatency : %f ms",l);

					start1=clock();
					for(j=0;j<nthread1;j++)
						{
							pthread_create(&th1[j],NULL,readKiloByteRandom,NULL);
							pthread_join(th1[j], NULL);
						}
					end1=clock();
					total_mb1=(nthread1 * KILOBYTE * MAX_KB)/1000000;
					time1=((double) (end1-start1))/ CLOCKS_PER_SEC;
					l1= (time1*1000)/total_mb1;
					printf("\n\nRANDOM READ");
					throughput1=total_mb1/time1;
					printf("\nThroughput:%f MB/s",throughput1);
					printf("\nLatency : %f ms",l1);
						break;

		case 3: printf("\n\nBlock size selected is MEGABYTE");
					printf("\n\nEnter the number of threads(1/2) :\n");
					scanf("%d",&nthread1);
					start1=clock();
					for(j=0;j<nthread1;j++)
						{
							pthread_create(&th1[j],NULL,writeMegaByteSequential,NULL);
							pthread_join(th1[j], NULL);
						}
					end1=clock();
					total_mb1=(nthread1 * MEGABYTE * MAX_MB)/1000000;
					time1=((double) (end1-start1))/ CLOCKS_PER_SEC;
					l= (time1*1000)/total_mb1;
					printf("\n\nSEQUENTIAL WRITE 1MB");

					throughput1=total_mb1/time1;
					printf("\nThroughput:%f MB/s",throughput1);
					printf("\nLatency : %f ms",l);
					start1=clock();
					for(j=0;j<nthread1;j++)
						{
							pthread_create(&th1[j],NULL,readMegaByteSequential,NULL);
							pthread_join(th1[j], NULL);
						}
					end1=clock();
					total_mb1=(nthread1 * MEGABYTE * MAX_MB)/1000000;
					time1=((double) (end1-start1))/ CLOCKS_PER_SEC;
					l1= (time1*1000)/total_mb1;
					printf("\n\nSEQUENTIAL READ");
					throughput1=total_mb1/time1;
					printf("\nThroughput:%f MB/s",throughput1);
					printf("\nLatency : %f ms",l1);
					start1=clock();
					for(j=0;j<nthread1;j++)
						{
							pthread_create(&th1[j],NULL,writeMegaByteRandom,NULL);
							pthread_join(th1[j], NULL);
						}
					end1=clock();
					total_mb1=(nthread1 * MEGABYTE * MAX_MB)/1000000;
					time1=((double) (end1-start1))/ CLOCKS_PER_SEC;
					l= (time1*1000)/total_mb1;
					printf("\n\nRANDOM WRITE 1MB");
					throughput1=total_mb1/time1;
					printf("\nThroughput:%f MB/s",throughput1);
					printf("\nLatency : %f ms",l);
					start1=clock();
					for(j=0;j<nthread1;j++)
						{
							pthread_create(&th1[j],NULL,readMegaByteRandom,NULL);
							pthread_join(th1[j], NULL);
						}
					end1=clock();
					total_mb1=(nthread1 * MEGABYTE * MAX_MB)/1000000;
					time1=((double) (end1-start1))/ CLOCKS_PER_SEC;
					l= (time1*1000)/total_mb1;
					printf("\n\nRANDOM READ 1MB");
					throughput1=total_mb1/time1;
					printf("\nThroughput:%f MB/s",throughput1);
					printf("\nLatency : %f ms",l);
					break;

                    }
                }
                break;
                case 4:exit(0);
            }

        }
    return 0;
}
