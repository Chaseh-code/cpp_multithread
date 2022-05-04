#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

using namespace std;

//void *PrintHello(void *);
void *wait(void *);

#define NUM_THREADS 5

/*struct thread_data {
    int thread_id;
    char *message;
};*/

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    int rc;
    void *status;

    // Initialize and set thread joinable
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for(int i = 0; i < NUM_THREADS; i++){
        cout << "main(): creating thread, " << i << endl;
        rc = pthread_create(&threads[i], &attr, wait, (void *)i);

        if(rc){
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
        }
    }

    // free attribute and wait for the other threads
    pthread_attr_destroy(&attr);
    for(int i = 0; i < NUM_THREADS; i++){
        rc = pthread_join(threads[i], &status);
        if(rc){
        cout << "Error: unable to join thread, " << rc << endl;
        exit(-1);
        }
        cout << "Main: completed thread id: " << i;
        cout << " exiting with status: " << status << endl;
    }

    cout << "Main: program exiting." << endl;
    pthread_exit(NULL);
    return 0;
}

/*void *PrintHello(void *threadarg){
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;

    cout << "Thread ID: " << my_data->thread_id;
    cout << " Message: " << my_data->message << endl;
    pthread_exit(NULL);
}*/

void *wait(void *t){
    int i;
    long tid;
    tid = long(t);

    sleep(1);
    cout << "Sleepin in thread " << endl;
    cout << "Thread with id: " << tid << " ...exiting " << endl;
    pthread_exit(NULL);
}