#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>

#include <stdlib.h>
#include <pthread.h>

#include "prodcon.h"

using namespace std;


pthread_mutex_t work_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_cond  = PTHREAD_COND_INITIALIZER;

unsigned int work_count = 0;


extern "C" void Trans(int n);
extern "C" void Sleep(int n);

int main(int argc, char *argv[])
{
    const int nthreads = atoi(argv[1]);
    const int id = (argc <= 2) ? 0 : atoi(argv[2]);

    stringstream ss;
    ss << id;
    string out_fname = id == 0 ? "prodcon.log" : "prodcon." + ss.str() + ".log";

    string* work_queue = new string[2*nthreads];        // queue holds 2 * # of consumers amount of work

    unsigned int thread_ids[nthreads];
    for (unsigned int id=0; id<nthreads; id++)
        thread_ids[id] = id;

    pthread_t threads[nthreads]; 
    for (int i=0; i<nthreads; i++) {
        pthread_create(&threads[nthreads], nullptr, consumer, &thread_ids[i]);
    }

    while (true) {

        pthread_mutex_lock(&condition_mutex);
        if (work_count > 0) {
            pthread_cond_signal(&condition_cond);       // if there is at least one work in the queue, signal a thread.
        }
        pthread_mutex_unlock(&condition_mutex);

        string work;

        cin >> work;
        if (cin.eof())      // end of input 
            break;

        int n = stoi(work.substr(1));

        pthread_mutex_lock(&work_mutex);
        work_queue[work_count] = work;      // push work into the queue
        pthread_mutex_unlock(&work_mutex);

        print_action(0, (work[0] == 'T') ? "Work" : "Sleep", &n);

        pthread_mutex_lock(&count_mutex);
        work_count += 1;        
        pthread_mutex_unlock(&count_mutex);

    }

    for (int i=0; i<nthreads; i++) {
        pthread_join(threads[i], nullptr);     // wait for all threads;
    }

    delete[] work_queue;
}

void* consumer(void* args_p)
{
    int* id = (int *) args_p;

    pthread_mutex_lock(&condition_mutex);
    while (work_count == 0) {
        // wait if there is no work to do
        print_action(*id, "Ask", nullptr);
        pthread_cond_wait(&condition_cond, &condition_mutex);       // unlocks the mutex when goint to sleep
    }
    pthread_mutex_unlock(&condition_mutex);

    return nullptr;
}

void print_action(const unsigned int id, string action, int* n)
{
    char buffer[100];
    cout << "0.000" << " " << "ID= " << id << " ";
    if (action == "Ask") {
        cout << "     ";
    } else {
        pthread_mutex_lock(&count_mutex);
        cout << "Q= " << work_count << " ";            // TODO need mutex?
        pthread_mutex_unlock(&count_mutex);
    }

    sprintf(buffer, "%-15s", action.c_str());
    cout << buffer;

    if (action == "Ask") {
        cout << endl;
    } else {
        cout << *n << endl;
    }
}