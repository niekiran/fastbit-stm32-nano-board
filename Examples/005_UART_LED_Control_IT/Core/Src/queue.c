/*
 * queue.c
 *
 *  Created on: Apr 16, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "queue.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>


/* Function to initialize size of queue as 0 */
struct Queue *createQueue(struct Queue *queue, unsigned capacity, struct led_command_data *command){
  queue->capacity = capacity;
  queue->front = queue->size = 0;
  queue->rear = capacity - 1;  // This is important, see the enqueue
  queue->items = command;
  return queue;
}

/* Function to check if queue is full */
int isFull(struct Queue *queue) {
    return (queue->size == queue->capacity);
}

/* Function to check if queue is empty */
int isEmpty(struct Queue *queue) {
  return (queue->size == 0);
}

/* Function to add an item to the queue (enqueue) */
void enqueue(struct Queue *queue, struct led_command_data value) {
  if (isFull(queue)) {
      printf("Queue is full\n");
  }
  queue->rear = (queue->rear + 1) % queue->capacity;
  queue->items[queue->rear] = value;
  queue->size++;
}

/* Function to remove an item from the queue (dequeue) */
struct led_command_data dequeue(struct Queue *queue) {
  struct led_command_data data;
  if (isEmpty(queue)) {
    strcpy(data.command, ""); // Indicating empty data
    return data;
  } else {
    data = queue->items[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return data;
  }
}

/* Function to get front of queue */
struct led_command_data front(struct Queue* queue) {
  struct led_command_data emptyData;
  if (isEmpty(queue)) {
    printf("Queue is empty\n");
    emptyData.command[0] = '\0'; // Indicating empty data
    return emptyData;
  } else {
    return queue->items[queue->front];
  }
}

/* Function to get rear of queue */
struct led_command_data rear(struct Queue* queue) {
  struct led_command_data emptyData;
  if (isEmpty(queue)) {
    printf("Queue is empty\n");
    emptyData.command[0] = '\0'; // Indicating empty data
    return emptyData;
  } else {
    return queue->items[queue->rear];
  }
}


