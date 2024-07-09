/*
 * queue.h
 *
 *  Created on: Apr 16, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#include <stdio.h>
#include <stdint.h>

struct led_command_data {
  char command[10];
  uint16_t argument;
  uint16_t delay;
};

struct Queue {
  int front, rear, size;
  unsigned capacity;
  struct led_command_data *items;
};

/* Function prototypes */
struct Queue *createQueue(struct Queue *queue, unsigned capacity, struct led_command_data *command);
int isFull(struct Queue *queue);
int isEmpty(struct Queue *queue);
void enqueue(struct Queue *queue, struct led_command_data value);
struct led_command_data dequeue(struct Queue *queue);

/* Declare variables as extern */
extern struct Queue command_queue;
extern struct led_command_data commands[10];
extern struct led_command_data prev_cmd;
extern struct led_command_data command;


#endif /* INC_QUEUE_H_ */
