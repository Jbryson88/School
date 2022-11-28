// Create the sleeping barber problem using semaphores
// Compile with: g++ -o barber barber.cpp -lpthread
// Run with: ./barber
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
using namespace std;

// Global variables
const int CHAIRS = 5; // Number of chairs in waiting room
const int CUSTOMERS = 10; // Number of customers
int waiting = 0; // Number of customers waiting
sem_t mutex; // Mutex lock for critical section
sem_t barber; // Barber semaphore
sem_t customer; // Customer semaphore

// Barber thread
void *barberThread(void *arg) {
    while (true) {
        // Wait for customer
        sem_wait(&customer);
        // Get mutex lock
        sem_wait(&mutex);
        // Decrement waiting
        waiting--;
        // Signal barber
        sem_post(&barber);
        // Release mutex lock
        sem_post(&mutex);
        // Cut hair
        cout << "Barber: Cutting hair" << endl;
        sleep(3);
    }
}

// Customer thread
void *customerThread(void *arg) {
    // Get mutex lock
    sem_wait(&mutex);
    // Check if waiting room is full
    if (waiting < CHAIRS) {
        // Increment waiting
        waiting++;
        // Release mutex lock
        sem_post(&mutex);
        // Wake up barber
        sem_post(&customer);
        // Wait for barber
        sem_wait(&barber);
        // Get hair cut
        cout << "Customer: Getting hair cut" << endl;
        sleep(3);
    } else {
        // Release mutex lock
        sem_post(&mutex);
        // Leave
        cout << "Customer: Leaving" << endl;
    }
    return 0; // This is only added to appease the C++ gods and fix the werun error that can sometimes come up.
}

int main() {
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&barber, 0, 0);
    sem_init(&customer, 0, 0);
    // Create barber thread
    pthread_t barberThreadID;
    pthread_create(&barberThreadID, NULL, barberThread, NULL);
    // Create customer threads
    pthread_t customerThreadID[CUSTOMERS];
    for (int i = 0; i < CUSTOMERS; i++) {
        pthread_create(&customerThreadID[i], NULL, customerThread, NULL);
        // Sleep for random amount of time
        sleep(rand() % 3);
    }
    // Join threads
    pthread_join(barberThreadID, NULL);
    for (int i = 0; i < CUSTOMERS; i++) {
        pthread_join(customerThreadID[i], NULL);
    }
    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&barber);
    sem_destroy(&customer);
    return 0;
}


