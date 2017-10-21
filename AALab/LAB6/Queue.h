#include<stdio.h>
#include<stdlib.h>

struct QueueRecord;
typedef struct QueueRecord *Queue;

struct QueueRecord
{
	int capacity;
	int front;
	int rear;
	int size;
	char *Array;
};

Queue CreateQueue(int capacity);
int QIsEmpty(Queue queue);
static int Succ( int value, Queue queue);
int IsFull(Queue queue);
void Dequeue(Queue queue);
void Enqueue(Queue queue, int V);

Queue CreateQueue(int capacity)
{
    Queue queue;
    queue = (Queue)malloc(sizeof(Queue));
    if (queue == NULL)
    {
        printf("out of space!!!\n");
    }
	queue->Array = (char*)malloc(sizeof(char));
	queue->capacity = capacity;
    queue->size = 0;
    queue->rear = 0;
    queue->front = 1;
    return queue;
}
int QIsEmpty(Queue queue)
{
    return queue->size == 0;
}

static int Succ( int value, Queue queue)
{
    if(++value == queue->capacity)
        value = 0;
    return value;
}
int IsFull(Queue queue)
{
    return (queue->size >= queue->capacity);
}

void Dequeue(Queue queue)
{
    if(QIsEmpty(queue))
    {
        printf("Error!");
        exit(1);
    }
    else
    {
       // printf("Dequeue %d !\n", queue->Array[queue->front]);
        queue->front++;
        queue->size--;
   //     printf("size after Dequeue = %d\n ", queue->size);
    }

}

void Enqueue(Queue queue, int x)
{
    if(IsFull(queue))
    {
        printf("Error!");
        exit(1);
    }
        queue->size++;
        queue->rear++;
     //   printf("The Enqueue element is %c ", T->data);
        queue->Array[queue->rear] = x;

      //  printf("size after Enqueue = %d\n ", queue->size);
}
