#include <iostream>
#include <string>
#include <sstream>

#include <stdlib.h>
#include <pthread.h>

#include "prodcon.h"

using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


int main(int argc, char *argv[])
{
    const int nthreads = atoi(argv[1]);
    const int id = (argc <= 2) ? 0 : atoi(argv[2]);

    stringstream ss;
    ss << id;
    string out_fname = id == 0 ? "prodcon.log" : "prodcon." + ss.str() + ".log";

    pthread_t threads[nthreads]; 

}

void* thread_function(void* args_p)
{
    int* num = (int *) args_p;      // cast
}