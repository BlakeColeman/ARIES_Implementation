#include "queue.h"
//--------------------------------------------------------------------
void enqueue(const struct logEntry newDataItem, struct Queue* queue)
{
	struct QueueNode *p = calloc(1,sizeof(struct QueueNode));
	p->dataItem = newDataItem;
	
	if (queue->front == NULL)
	{
		queue->front = p;//If there are no nodes, set the front to be this new node
		queue->rear = p;//and set the end to be this new node
	}
	else
	{
		queue->rear->next=p;
		queue->rear = p;//Otherwise, add the new node only to the end
	}
}
//--------------------------------------------------------------------

// Removes the least recently (front) element from a queue and
// returns it.
// If the list was empty, throws a logic error.
struct logEntry dequeue(struct Queue* queue)
{
	//printf("\nDequeuing");
	struct QueueNode* p = malloc(sizeof(struct QueueNode));   // Pointer to dequeued node
	struct logEntry temp;            // Temporarily stores dequeued element
						// Requires that the queue is not empty
	copyEntry(&temp,queue->front->dataItem);
	if (queue->front->next != NULL)
	{
		p = queue->front;
		queue->front = queue->front->next;
	}
	else
	{
		p = queue->front;
		queue->front = NULL;
		queue->rear = NULL;
	}
	free(p);
	return temp;
}

struct logEntry	getFront(struct Queue queue)
{
	return queue.front->dataItem;
}
//--------------------------------------------------------------------

// Removes all the elements from a queue.
void clearQueue(struct Queue* queue)
{
	struct QueueNode *p,       // Points to successive nodes
		*nextP;   // Stores pointer to next node
	p = queue->front;
	while (p != 0)
	{
		printf("\nClearing");
		printLogEntry(p->dataItem);
		nextP = p->next;
		free(p);
		p = nextP;
	}

	queue->front = 0;
	queue->rear = 0;
	return;
}

//--------------------------------------------------------------------

void copyQueue(struct Queue *dest, struct Queue source)
{
	while(!isEmpty(source))
		{
			enqueue(dequeue(&source),dest);
		}
}

// Returns true if a queue is empty. Otherwise, returns false.
bool isEmpty(struct Queue queue)
{
	return (queue.front == 0);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------

void showStructure(struct Queue queue)
{
	struct QueueNode *p;   // Iterates through the queue
	p = queue.front;

	if (queue.front == 0)
		printf("Empty queue\n");
	else
	{
		while(p!=NULL)
		{
			printLogEntry(p->dataItem);
			p = p->next;
		}
	}
}

void initializeQueue(struct Queue* queue)
{
	queue->front = NULL;
	queue->rear = NULL;
}