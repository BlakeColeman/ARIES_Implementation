///Modified from when I took the CS210 lab
#include "logEntry.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#pragma once

// Forward declaration of the Stack class 
struct Queue
{
	// Data members
	struct QueueNode *front;
	struct QueueNode *rear;
};
// Queue manipulation operations
void copyQueue(struct Queue* dest, struct Queue source);
void enqueue(const struct logEntry newData,struct Queue*);       // Enqueue data element
struct logEntry dequeue(struct Queue*);                          // Dequeue data element
struct logEntry getFront(struct Queue queue);
void clearQueue(struct Queue*);                            // Clear queue
void initializeQueue(struct Queue*);
// Queue status operations
bool isEmpty();                    // Queue is empty
bool isFull();                     // Queue is full
// Output the queue structure -- used in testing/debugging
void showStructure();
struct QueueNode              // Facilitator class for the Queue class
{
	// Data members
	struct logEntry dataItem;         // Queue data item
	struct QueueNode *next;     // Pointer to the next element
};


