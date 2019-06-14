#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_SIZE 100

int *list;

int *sorted;

int i ;

struct range {

   int start;

   int end;

};

void* sort(void* arg) {

   struct range* current = (struct range*) arg;

   int start = current->start;

   int end = current->end;


    ///Initial Condition
   if(start == end)         ///We're Finished when array have just one element
      pthread_exit(NULL);


   ///Splitting array into two halves from middle
   struct range lower;

   struct range upper;



   int middle = (start + end)/ 2;



   lower.start = start;

   lower.end = middle;



   upper.start = middle + 1;

   upper.end = end;


    /// Defining two threads
   pthread_t thread_low;

   pthread_t thread_high;


   ///Recursively Calling Sort() function once again using a Thread for upper half of array
   pthread_create(&thread_high, NULL, sort, (void*) &upper);



   ///Recursively Calling Sort() function once again using a Thread for lower half of array
   pthread_create(&thread_low, NULL, sort, (void*) &lower);



   pthread_join(thread_high, NULL);
   pthread_join(thread_low, NULL);



   int k = start, i = start, j = middle+1;

    ///-----------------------------------------Merging-----------------------------------------------

   	while (i<=middle && j<=end){

   		if (list[i] < list[j])
   			sorted[k++] = list[i++];

   		else
   			sorted[k++] = list[j++];
   	}


   	while(i<=middle)
   		sorted[k++] = list[i++];

   	while(j<=end)
   		sorted[k++] = list[j++];



   	for (i=start; i <= end; i++)
   		list[i] = sorted[i];



}



int main(void) {

   int number = 0;

   FILE * fptr;
   char ip_file_name[]="input.txt";
   char op_file_name[]="output.txt";

   fptr=fopen(ip_file_name,"r");

   if (fptr == NULL)
    {
        perror("Error while opening the file!\n");
        exit(EXIT_FAILURE);
    }

   fscanf(fptr,"%d",&number); ///Taking Number of element from input file


   list = (int*)malloc(sizeof(int)*number);

   sorted = (int*)malloc(sizeof(int)*number);


   for(i=0;i<number;i++){
    fscanf(fptr,"%d",&list[i]);
   }

    fclose(fptr);


   if (number <= 0) {   ///If List Is Empty or Numbers is -VE

      printf("There are no input numbers\n");
      exit(0);

   }

   else if (number == 1) { ///If There IS Only One Element

      printf("The List Sorted\n");

      printf("%d\n", list[0]);

      exit(0);

   }

   else {
            ///Loading Argument Struct with array limits
      struct range beginning;

      beginning.start = 0;

      beginning.end = number -  1;

      sort(&beginning); ///Sorting Recursive Function Invoked

   }

   printf("The List Sorted:\n");
    fopen(op_file_name,"w");
   for (i = 0; i < number; i++) {

      fprintf(fptr,"%d ",sorted[i]);
      printf("%d ", sorted[i]);

   }
    fclose(op_file_name);
   return 0;

}
