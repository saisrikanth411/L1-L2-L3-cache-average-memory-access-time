#include <stdlib.h>
#include <stdio.h>
#include "fcyc2.h" 
#include "clock.h"
#include<time.h>
#include<stdint.h>
#define BILLION 1000000000L
#define MINBYTES (1 << 10)  // Working set size ranges from 1 KB 
#define MAXSTRIDE 64        // Strides range from 1 to 32 
#define STRIDESTRIDE 2      // increment stride by this amount each time 
 
int* data;//array we will be traversing



double run(int size, int stride, double Mhz);//run function to obtain the cycles 


int main()
{
int MAXBYTES;
printf("enter the size \n ");//enter the size of the cache
scanf("%d", &MAXBYTES);
if (MAXBYTES > (1 << 20))
	{
	    printf("%dm\t", MAXBYTES / (1 << 20));// if size greater than 1000k print as MB
	}
	else
	{
	    printf("%dk\t", MAXBYTES / 1024);//if size lesser than 1000k print kB
	}

int MAXELEMS = MAXBYTES/(sizeof(int));

data = (int*)malloc(MAXELEMS*sizeof(int));//allocate a data of MAXELEMS


    int size;        // Working set size (in bytes) 
    int stride;      // Stride (in array elements) 
    double Mhz;      // Clock frequency 
struct timespec start,end;
uint64_t diff;
    Mhz = mhz(0);              // Estimate the clock frequency 
void test(int elems, int stride);
    printf("Clock frequency is approx. %.1f MHz\n", Mhz);//print the clock frequency
    printf("\t");
    for (stride = 1; stride <= MAXSTRIDE; stride += STRIDESTRIDE)

 // begin memory mountain 
    for (size = MAXBYTES; size >= MINBYTES; size >>= 1) { //

	
	if (size > (1 << 20))
	    printf("%dm\t", size / (1 << 20));
	else
	    printf("%dk\t", size / 1024);
	

	clock_gettime(CLOCK_REALTIME,&start);//start timer to measure access time
	for (stride = 1; stride <= MAXSTRIDE; stride += STRIDESTRIDE) { // increase the stride by 2 as it traverses through the array
	run(size, stride, Mhz);//for constant clock and size stride through the array
	}
	clock_gettime(CLOCK_REALTIME,&end);//end the timer
	diff = ((end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec))/(sizeof(data)*1000);//obtain the difference in access time
	
	printf("\n \t %lu  ", diff);
	printf("\n");
    }
	
    exit(0);
}


void test(int elems, int stride) // The test function to read the array 
{
	
    int i, result = 0; 
    

    for (i = 0; i < elems; i += stride)
	result += data[i];//read the array
   
}


double run(int size, int stride, double Mhz)
{
    double cycles;
    int elems = size / sizeof(int); 

    test(elems, stride);                     // warm up the cache 
    cycles = fcyc2(test, elems, stride, 0);  // call test(elems,stride) 
	return cycles/size;
}



