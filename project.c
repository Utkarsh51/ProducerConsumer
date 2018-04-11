//header files//
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>

#define Size 5
#define NoThreads 8
#define ProducerLoops 10
//Buffer Definition//
typedef int buffer_t;
buffer_t buffer[Size];
int buffer_index;
//semaphores and mutex//
pthread_mutex_t buffer_mutex;
sem_t full_sem;  // will return 0 when buffer will be full  
sem_t empty_sem; // will return 0 when  buffer is empty works like index for the buffer */ 
//method to put produced items in buffer
void insertInBuffer(buffer_t value) {
    if (bufferIndex < Size) {
        buffer[bufferIndex++] = value;
    } else {
        printf("Buffer is Full can not produce\n");
    }
}
//method to remove consumed items from buffer
buffer_t deleteFromBuffer() {
    if (bufferIndex > 0) {
        return buffer[--bufferIndex]; 
    } else {
        printf("Buffer is empty Nothing to consume\n");
    }
    return 0;
}

