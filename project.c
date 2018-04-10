#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
int Shared_Buffer[500];
void * produce()
{
printf("produce");
}
void * consume()
{
printf("consume);
}
void main(){
{
int i;
int No_of_Producers;
int No_of_Consumers;
printf("Enter the number of producers");
printf("Enter number of consumers");
scanf("%d",&No_of_Producers);
scanf("%d",&No_of_Consumers);
for(i=0;i<No_of_Producers;i++){
}
}
