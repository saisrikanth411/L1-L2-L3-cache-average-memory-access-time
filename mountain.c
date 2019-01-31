/* mountain.c - Generate the memory mountain. */

#include <stdlib.h>
#include <stdio.h>
#include "fcyc2.h" 
#include "clock.h"
#include<time.h>
#include<stdint.h>
#define BILLION 1000000000L
#define MINBYTES (1 << 10)  // Working set size ranges from 1 KB 
 #define MAXSTRIDE 64        // Strides range from 1 to 64 
#define STRIDESTRIDE 2      // increment stride by this amount each time 

int* data;


double run(int size, int stride, double Mhz);

/* $begin mountainmain */
int main()
{
int MAXBYTES;//max number of bytes
printf("enter the size \n ");//enter the maximum size of the cache
scanf("%d", &MAXBYTES);
if (MAXBYTES > (1 << 20))
	{
	    printf("%dm\t", MAXBYTES / (1 << 20));
	}
	else
	{
	    printf("%dk\t", MAXBYTES / 1024);
	}

int MAXELEMS = MAXBYTES/(sizeof(int));

data = (int*)malloc(MAXELEMS*sizeof(int));//allocate the memory of the array

void init_data(int *data, int n);
  

    int size;        // Working set size (in bytes) 
    int stride;      // Stride (in array elements) 
    double Mhz;      // Clock frequency 
struct timespec start,end;

double diff;
    init_data(data, MAXELEMS); // Initialize each element in data to 1 
    Mhz = mhz(0);              // Set constant clock frequency 
void test(int elems, int stride);
    printf("Clock frequency is approx. %.1f MHz\n", Mhz);//print the clock frequency
    //printf("\t");
    for (stride = 1; stride <= MAXSTRIDE; stride += STRIDESTRIDE)

 // begin memory mountain 
    for (size = MAXBYTES; size >= MINBYTES; size >>= 1) {

	
	if (size > (1 << 20))
	    printf("%dm\t", size / (1 << 20));//
	else
	    printf("%dk\t", size / 1024);
	
	clock_gettime(CLOCK_REALTIME,&start);//start the timer for measuring the access time
	for (stride = 1; stride <= MAXSTRIDE; stride += STRIDESTRIDE) {
	run(size, stride, Mhz);//run function to stride through the cache
	}
	clock_gettime(CLOCK_REALTIME,&end);//end the timer
	diff =(double) (end.tv_nsec - start.tv_nsec)/(sizeof(data)*1000);//compute the difference in the times 
	printf(" \t %.1f \n ", diff);
	
    }
	
    exit(0);
}


 //init_data - initializes the array 
void init_data(int *data, int n)
{
    int i;

    for (i = 0; i < n; i++)
	data[i] = 1;
}



void test(int elems, int stride) // The test function to warm up the cache 
{
	
    int i; 
    int result = 0;

    for (i = 0; i < elems; i += stride)
	//data[i] = 1;
	result += data[i];
   
}


double run(int size, int stride, double Mhz)//run to stride through an array of constant clock and size 
{
    double cycles;
    int elems = size / sizeof(int); 

    test(elems, stride);                     // warm up the cache 
    cycles = fcyc2(test, elems, stride, 0);  // call test(elems,stride) 
    
    return cycles/size;
}



