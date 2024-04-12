#include "logEntry.h"

struct logEntry createLogEntry(char* myString) 
{
	int i = 1;
	int j = 0;
	int temp = 0;
	char temps[100] = "";
	struct logEntry entry;

	clearLogEntry(&entry);
	
	// Get the log entries LNS
	while (myString[i] != ',') {
		temps[i] = myString[i];
		i++;
	}
	j = i - 1;
	while (j >= 1)
	{
		temp = temp + (temps[j] - '0') * pow(10, (i - j - 1));
		j--;
	}
	entry.LNS = temp;
	i++;

	// Get the log entries Status
	while (myString[i] != ',') 
	{
		entry.status = myString[i];
		i++;
		j++;
	}
	i++;

	// Get the log entries SQL	
	j = 0;
	while (myString[i] != '}') 
	{
		entry.SQL[j] = myString[i];
		i++;
		j++;
	}

	return entry;
}

void printLogEntry(struct logEntry entry) 
{
	printf("\nLNS: %d  \tStatus: %c \t\n", entry.LNS, entry.status);
}

void clearLogEntry(struct logEntry* entry)
{
	entry->LNS = 0;
	entry->status = ' ';
	memset(entry->SQL,0, sizeof(entry->SQL));
}
void copyEntry(struct logEntry* dest, struct logEntry source)
{
	memset(dest->SQL,0,sizeof(dest->SQL));
	dest->LNS=0;
	dest->status=' ';
	dest->LNS = source.LNS;
	dest->status = source.status;
	strcpy(dest->SQL,source.SQL);
}