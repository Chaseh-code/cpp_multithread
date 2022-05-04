#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

void *PrintHello(void *);

#define NUM_THREADS 5

struct thread_data {
    int thread_id;
    char *message;
};

int main() {
    pthread_t threads[NUM_THREADS];
    struct thread_data td[NUM_THREADS];
    int rc;

    for(int i = 0; i < NUM_THREADS; i++){
        cout << "main(): creating thread, " << i << endl;
        td[i].thread_id = i;
        td[i].message = "This is a great message man. Real good testing going on here :)";
        rc = pthread_create(&threads[i], NULL, PrintHello, (void *)&td[i]);

        if(rc){
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
        }
    }

    pthread_exit(NULL);
    return 0;
}

void *PrintHello(void *threadarg){
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;

    cout << "Thread ID: " << my_data->thread_id;
    cout << " Message: " << my_data->message << endl;
    pthread_exit(NULL);
}