#define __STDC_WANT_LIB_EXT1__ 1
#include "logEntry.h"
#include "queue.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int system(const char *command);

struct Queue analysis(struct logEntry mylogentry[100], int n, struct Queue logQueue,int commited[500],int *commitedEnd);
void redo(struct Queue logQueue,FILE* fptr);
void undo(struct Queue logQueue,int commited[500],int commitedEnd,FILE* fptr);

int main(void) {

  // const int x = 1000000;
  FILE *fptr = NULL;

  struct logEntry log[500];
	int commited[500];
	int commitedEnd;
	
  // Open a file in read mode
  fptr = fopen("filename.txt", "r");
  // Store the content of the file
  char myString[100000];
  struct logEntry temp;
  int n = 0;
	
  // Read the content
  while ((fgets(myString, 100000, fptr))) 
	{
    clearLogEntry(&temp);
    temp = createLogEntry(myString);
    copyEntry(&log[n], temp);
    n++;
  }
  // Close the file
  fclose(fptr);

  struct Queue logQueue;

	printf("\nStarting Analysis");
  copyQueue(&logQueue, analysis(log, n, logQueue,commited,&commitedEnd));
  printf("\nAnalysis complete");
	// Open a file in writing mode
	fptr = fopen("recover.txt", "w");
	redo(logQueue,fptr);
	undo(logQueue,commited,commitedEnd,fptr);
	// Close the file
	fclose(fptr);
	
	

	

  

  return 0;
}

// Get a complete list of all LNS that have been committed
struct Queue analysis(struct logEntry log[500], int n, struct Queue logQueue,int commited[500],int *commitedEnd) 
{
	FILE *fptr = NULL;
	fptr = fopen("get.txt", "w");
	int aborted[500];
  int logPlace = 0;
  int End = 0;
  int abortedEnd = 0;
  int temp = 0;
  struct Queue tempQueue;
  struct logEntry tempEntry;
  initializeQueue(&tempQueue);
	
  while (logPlace < n) {
    if (log[logPlace].status == 'c') 
		{
      commited[End] = log[logPlace].LNS;
      End++;
    } 
		else if (log[logPlace].status == 'a') 
		{
      aborted[abortedEnd] = log[logPlace].LNS;
      abortedEnd++;
    } 
		else 
		{
      enqueue(log[logPlace], &logQueue);
    }
    logPlace++;
    // Every 100 commits Check if the front of the queue has been aborted or finished
    if (End == 100) 
		{
      clearQueue(&tempQueue);
      printf("\nCheckpointing");
      while (!isEmpty(logQueue)) 
			{
        enqueue(dequeue(&logQueue), &tempQueue);
      }
			
      while (isEmpty(tempQueue) == false) {
        copyEntry(&tempEntry, dequeue(&tempQueue));
        int add = 1;
        for (int i = 0; i < End; i++) 
				{
          if (tempEntry.LNS == commited[i]) {
            commited[i] = 0;
						fprintf(fptr,"%s",tempEntry.SQL);
            add = 0;
          } else if (tempEntry.LNS == aborted[i]) {
            add = 0;
          }
        }
        if (add == 1) {
          enqueue(tempEntry, &logQueue);
        }
      }
      End = 0;
      printf("\nCheckpoint Finished");
    }
  }
	commitedEnd = &End;
	fclose(fptr);
  return logQueue;
	
}

void redo(struct Queue logQueue,FILE* fptr) 
{
  struct logEntry tempEntry;
	struct Queue tempQueue;
	initializeQueue(&tempQueue);
  char command[100000];
	printf("\nRedoing");
	char tempstr[100000];
	
	while (!isEmpty(logQueue)) 
	{
		enqueue(dequeue(&logQueue), &tempQueue);
	}
	strcpy(command,"BEGIN;\n");
	
  while(!isEmpty(tempQueue))
  {
  	copyEntry(&tempEntry, dequeue(&tempQueue));
		strcpy(tempstr,tempEntry.SQL);
  	strcat(command, tempstr);
  	strcat(command,"\n");
		enqueue(tempEntry, &logQueue);
  	clearLogEntry(&tempEntry);
  }
	// Write some text to the file
	fprintf(fptr,"%s",command);
}

void undo(struct Queue logQueue,int commited[500],int commitedEnd,FILE* fptr)
{
	printf("\nUndoing\n");
	struct Queue tempQueue;
	struct logEntry log[500];;
	char command[1000000];
	int n=0;
	struct logEntry temp;
	struct logEntry temp2;
	char tempstr[100000];
	int add=1;
	char Comcommand[100000];
	
	fprintf(fptr,"%s","Rollback;\n");
	while (!isEmpty(logQueue)) 
	{
		enqueue(dequeue(&logQueue), &tempQueue);
	}
	
	while(!isEmpty(tempQueue))
	{	
		add=1;
		clearLogEntry(&temp);
		temp = dequeue(&tempQueue);
		
		while(n<commitedEnd)
		{
			if (temp.LNS==commited[n])
			{
				strcpy(tempstr,temp.SQL);
				strcat(Comcommand,tempstr);
				strcat(Comcommand,"\n");
				add=0;
				n=0;
			}
			n++;
		}	
		if (add==1)
		{
			strcpy(tempstr,temp.SQL);
			strcat(tempstr,"\n");
			strcat(tempstr,command);
			strcpy(command,tempstr);
			enqueue(temp, &logQueue);
		}
		
		
	}
	// Write some text to the file
	fprintf(fptr,"%s",command);
	fprintf(fptr,"%s","Commit;\n");
	fprintf(fptr,"%s",Comcommand);
}