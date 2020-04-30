#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
/*author: 
Merging sort to simulate the process schedulor
*/

//globle variables
/* structure for passing data to threads */

typedef struct
{
    int *start;
    int end;
    int size;
} parameters;


int t = 1;
int *arr1, *arr2;
//for using quicksort
int comparator (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void *merge(void *params){
     //get data
   int *len = params;
    //SORT
    int start  = 0;
    int end = *len/2;
    int counter = end;
    int size =  *len;
    int index = 0;
    while (start < end && counter < size)
       {

          if (arr1[start] < arr1[counter])
          {

              arr2[index] = arr1[start];

            start ++;

          }
          else
          {


            arr2[index] = arr1[counter];

            counter ++;
         }
        index ++;
       }

       /* Copy the remaining elements , if there
       are any */

       while ( start < end)
       {

           arr2[index] = arr1[start];

          start ++;
          index ++;
       }

      /* Copy the remaining elements  , if there
       are any */
        while ( counter < size)
       {
          arr2[index] = arr1[counter];
          counter ++;
          index ++;
       }



}
void *sorting_thread(void *params){
    printf("Thread %d ......\n", t);
    t++;

    //get data
   parameters* data = (parameters *)params;
   //SORT

    int end = data->end;
    int size = data->size;


    //qsort
    qsort(data->start, end, sizeof(*data->start), comparator);
    printf("The array after sort : \n");
          for(int i = size - end; i < size; i ++){
               printf("arr1[%d]:%d, \n", i,arr1[i]);
         }
    printf("\n");
    pthread_exit(0);

}


void *merge_sort_thread(void *params){
    int *len = params;
    //varaible allocation for two sorting threads.
    parameters *data = (parameters *) malloc (sizeof(parameters));
    parameters *data1 = (parameters *) malloc (sizeof(parameters));
    if(data == NULL&& data1 == NULL){
      printf("Memory not allocated. \n");
      exit(0);
     }
     //value for data passing

         data->start= arr1;
         data->end = *len/2;
         data->size = *len/2;
         data1->start = arr1 + *len/2;
         data1->end = *len-*len/2;
         data1->size = *len;

    pthread_t left, right;/* the thread identifier */
     printf("Entering merge_Sorting..\n");

         /* create the sorting thread */

             pthread_create(&left, NULL, sorting_thread, data);

             pthread_create(&right, NULL, sorting_thread, data1);

          /* wait for the thread to exit */
             pthread_join(left, NULL);
             //free memory
             free(data);

             pthread_join(right, NULL);
        printf("Merging Thread %d ......\n", t);
         merge(len);
         printf("Process is done.\n");
         printf("The final output: \n");
         for(int i = 0; i < *len; i ++){
             if(i%10==0){
                 printf("\n");
             }
             printf("%d, ", arr2[i]);
         }
         printf("\n");
         //free memory
         free(data1);

         pthread_exit(0);

}



int main( int argc, char *argv[] )  {
    long len;
    int temp, c, j, k;
    char *ptr;

    //

   printf(" \nProject 1: \nThis program starts now....\n");
   //check if the right amount of argument
   if( argc == 2 ) {
      printf("The input array size is %s\n", argv[1]);


        //covert the user input to integer

      len = strtol(argv[1], &ptr, 10);

   //check if the input is valid.
       if(len == 0) {//if not, leave the program.
            printf("Please enter a proper number. Leaving the program...\n");
       }else{

     //dynamically allocate memory
     arr1 = (int*)malloc(len * sizeof(int));
     arr2 = (int*)malloc(len * sizeof(int));
     //check Memory
     if(arr1 == NULL && arr2 == NULL){
      printf("Memory not allocated. \n");
      exit(0);
     }

         printf("Memory allocated. \n");
         //decide the value of data.


         //generate random number to 100
         srand(time(0));

         printf("The array before sorting is:  \n");

         for(int i = 0; i < len; i ++){
             arr1[i] = rand() % 100;
             if(i%10==0){
                 printf("\n");
             }
             printf("%d, ", arr1[i]);
         }
         printf(" \n");
         //merge sort handle all the threads
         pthread_t tid;/* the thread identifier */

         /* create the parent sorting thread */
         pthread_create(&tid, NULL, merge_sort_thread, &len);
         //wait for children thread
         pthread_join(tid, NULL);
          //printout array after merging threading
         printf("\nThe program is finished. \n");
         //free memory space
         free(arr2);
         free(arr1);
      }

   }
   else if( argc > 2 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("One argument expected.\n");
   }

return 0;

}