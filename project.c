//header files//
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>

#define Size 5
//#define NoThreads 8
//#define ProducerLoops 10
int NoThreads=10;
int ProducerLoops=5;
int ConsumerLoops=2;
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
//method for producer to aquire critical section
void *producer(void *thread_n) {
    int threadNumber = *(int *)thread_n;
    buffer_t value;
    int i=0;
    while (i++ < ProducerLoops) {
       // sleep(rand() % 10);
        value = rand() % 100;
        sem_wait(&full_sem); /* possible race condition here. After this thread wakes up, another thread can aqcuire mutex before this one, and add to buffer. Then the buffer would be full again and when this thread will try to insert into buffer there would be a buffer overflow condition */
        pthread_mutex_lock(&buffer_mutex); //producer locks the buffer (critical section) to perform its operation
        insertInBuffer(value);
        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&empty_sem); // post increment emptybuffer semaphore after producing in the buffer
        printf("Producer %d produced %d in the buffer\n", threadNumber, value);
    }
    pthread_exit(0);
}
//Method for consumer to aquire critical section
void *consumer(void *thread_n) {
    int thread_numb = *(int *)thread_n;
    buffer_t value;
    int i=0;
    while (i++ < ConsumerLoops) {
        sem_wait(&empty_sem); /* there could be race condition here, that could cause buffer underflow error */
        pthread_mutex_lock(&buffer_mutex);
        value = deleteFromBuffer(value);
        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&full_sem); // post increment fullbuffer semaphore after consuming from the buffer
        printf("Consumer %d consumed %d from buffer\n", thread_numb, value);
   }
    pthread_exit(0);
}
//main method
void main(int argc, int **argv) {
    bufferIndex=0;
    pthread_mutex_init(&buffer_mutex, NULL);
    sem_init(&full_sem,0, Size); 
    sem_init(&empty_sem,0,0);
/* full_sem is initialized to buffer size because "Size" number of producers can add one element to buffer each. They will wait semaphore each time, which will decrement semaphore value.
empty_sem is initialized to 0, because initially buffer is empty and consumer cannot aquire critical section.They will have to wait until producer posts to that semaphore (increments semaphore value) after producing some item in the buffer*/
    pthread_t thread[NoThreads];
    int threadNumber[NoThreads];
    int i;
    for (i = 0; i < 1;i++) {
        threadNumber[i] = i;
        pthread_create(thread + i, NULL, producer, threadNumber + i);  
        
/* use this portion and comment the lloop section below to create consumer thread right after producer thread
		threadNumber[i] = i;
        pthread_create(&thread[i],NULL,consumer,&threadNumber[i]);  
        i++;
 */
    }
    for (i=0;i<NoThreads; i++){
    	threadNumber[i] = i;
    	pthread_create(&thread[i],NULL,consumer,&threadNumber[i]);
		i++;  
	}
    for (i = 0; i < NoThreads; i++)
        pthread_join(thread[i], NULL);
    //pthread_mutex_destroy(&buffer_mutex);
    //sem_destroy(&full_sem);
    //sem_destroy(&empty_sem);
    exit(0);
    return 0;
}
