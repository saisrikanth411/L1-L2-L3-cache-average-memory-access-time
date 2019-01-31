#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include "clock.h"
#include<stdint.h>
#define BILLION 1000000000L

#define ITERATIONS 1000//no of iterations

//#define ARRAY_ELEMENTS  (16*1024)
#define POINTER_SIZE  (sizeof(void*))//size of pointer
#define LINE_SIZE  64//cache line size
#define POINTERS_PER_LINE (LINE_SIZE/POINTER_SIZE)//number of pointers per line

  

typedef struct _CacheLine//define an structure of pointers per line
{
	struct _CacheLine* ptrCacheLine[POINTERS_PER_LINE];
}CacheLine;



long int pointer_size = POINTER_SIZE;//initialize the pointer size,line size and pointers per line
long int line_size = LINE_SIZE;
long int pointers_per_line = POINTERS_PER_LINE;

CacheLine* array = NULL;

void swap(CacheLine* a,CacheLine* b)//swap function to swap any 2 CacheLine elements 
{
	CacheLine* temp = a;
	a = b;
	b = temp;
}


void randomize(CacheLine* arr,int n)//randomize function to generate a random sequence of the structure 
{
	srand(time(NULL));
	for(int i = n-1;i > 0;i--)
	{
		int j = rand() % (i+1);
		swap(&arr[i], &arr[j]);
	}
}

void test_loop(CacheLine* array)//pointer chasing loop to chase through the loop until it reaches NULL pointer 
{
  CacheLine* p ;
  for(p = array ; p != NULL ; p = p->ptrCacheLine[0]) ;
}



int main()
{
int iterations = ITERATIONS;

 double Mhz;
Mhz = mhz(0);
 printf("Clock frequency is approx. %.1f MHz\n", Mhz);//set constant clock frequency
double diff;
struct timespec start , end;
long int array_elements;
printf("enter the size \n ");//enter the number of elements
scanf("%li", &array_elements);
if (array_elements > (1 << 20))
	{
	    printf("%ldm\t", array_elements / (1 << 20));
	}
	else
	{
	    printf("%ldk\t", array_elements / 1024);
	}

long int steps;
	long int top;
	long int bottom;
	long int i;
	int j;
	
	
     if ((array = (CacheLine*) malloc(array_elements * line_size)) == NULL) {  //allocate memory for the array
    printf("Couldn't allocate test array\n") ;
    exit( EXIT_FAILURE ) ;
  }
	int n = sizeof(array)/sizeof(array[0]);//determine the size of the array
	randomize(array, n);


	for (i = 0 ; i < array_elements ; i++) {
    for (j = 0 ; j < pointers_per_line ; j++) {     //write all the elements to zero
      array[i].ptrCacheLine[j] = NULL ;
    }
  }


  steps = array_elements / 2 ;//divide the struct in half
  bottom = 0 ;
  top = steps ;


  for (i = 0 ; i < steps ; i++) {  //point the bottom arrays towards the top and top towards the bottom 
    array[bottom].ptrCacheLine[0] = &array[top] ;
    array[top].ptrCacheLine[0] = &array[bottom+1] ;
    top++ ;
    bottom++ ;
  }


array[(array_elements-1)].ptrCacheLine[0] = NULL ;//terminate the list



for(int i = iterations;i > 0; i--) // for a number of  iterations run the pointer chasing loop
{
clock_gettime(CLOCK_MONOTONIC , &start);
test_loop(array);
clock_gettime(CLOCK_MONOTONIC , &end);
diff = (double)( end.tv_nsec - start.tv_nsec)/(sizeof(array)*100);

}

printf("  %.1f nanoseconds ", diff);//print the difference
printf("random array elements \n");

printf("pointer chasing \n");
}

