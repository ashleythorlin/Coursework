#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <math.h>


using namespace std;

//declare our main variables for the program
int n, u, p;

//declare dynamic array
int *arr = NULL;

//declare constants
#define ARRAY_MAX n
#define THREAD_MAX p



int thread_num = 0;
//thread func
void* thread_func(void* arg)
{
  //define lower bound and higher bound of split
    int min = thread_num * p;
    int max = (thread_num + 1) * p;

  //iterate the number of threads
    thread_num++;

    cout << "Sorted " << floor(n/p) << " numbers:  ";

  //sorting from lower split to higher split
    sort(arr + min, arr + max);

  //printing out each splitted array
    for (int i = min; i < max; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;


  //pthread exit
    pthread_exit(0);

}

void* thread_merge(void* arg)
{
  //define lower bound and higher bound of split
    int min1 = thread_num * p;
    int max1 = (thread_num + 1) * p;

  //iterate the number of threads
    thread_num++;

    int min2 = thread_num * p;
    int max2 = (thread_num + 1) * p;

  //iterate the number of threads
    thread_num++;

    cout << "Merged " << floor(n/p) << " numbers:  ";

  //sorting from lower split to higher split
    merge(min1, min1, min2, max2, arr);

  //printing out each splitted array
    for (int i = min; i < max; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;


  //pthread exit
    pthread_exit(0);

}


//main function
int main(int argc, char** argv)
{
    //receive input for n u, and  p
    n = stoi(argv[1]);  //amountNums = ARRAY_MAX
    u = stoi(argv[2]);  //random numbers from 1 to u
    p = stoi(argv[3]);      //amount of splits, p = THREAD_MAX


    //declare threads array with THREAD_MAX (amount of p) as the array size
    pthread_t threads[THREAD_MAX];


    //instantiate array called arr
    arr = new int [ARRAY_MAX];

    //seed the rand() generator
    srand(time(NULL));

    //use ARRAY_MAX as the array size to fill arr
    for(int i = 0; i < ARRAY_MAX; i++)
    {
        //fill array with random numbers from 1 to u
        arr[i]= rand() % u + 1;
    }


    //print original array
    cout << "Original Array: " << endl;
    for(int i = 0; i < ARRAY_MAX; i++)
        cout << arr[i] << " ";
    cout << endl << endl;

    //create a thread for each split
    for(int i = 0; i < THREAD_MAX; i++)
    {
        //create threads
        pthread_create(&threads[i], NULL, thread_func, (void*)NULL);
    }

    //joining the threads
    for(int i = 0; i < THREAD_MAX; i++)
    {
        pthread_join(threads[i], NULL);
    }


    //array should get sorted using the threads above

    //display sorted array
    cout << "\nSorted Array:" << endl;
    for(int i = 0; i < ARRAY_MAX; i++)
        cout << arr[i] << " ";
    cout << endl << endl;

    thread_num = 0;

    //merge segments
    for(int i = 0; i < THREAD_MAX; i+2)
    {
        //create threads
        pthread_create(&threads[i], NULL, threads_merge, (void*)NULL);
    }

    //joining the threads
    for(int i = 0; i < THREAD_MAX; i++)
    {
        pthread_join(threads[i], NULL);
    }


    //array should get sorted using the threads above

    //display sorted array
    cout << "\Merged Array:" << endl;
    for(int i = 0; i < ARRAY_MAX; i++)
        cout << arr[i] << " ";
    cout << endl << endl;


    return 0;
}
