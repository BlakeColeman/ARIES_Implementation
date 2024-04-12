#pragma once
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct logEntry {
	int LNS;
	char status;
	char SQL[10000];
};

struct logEntry createLogEntry(char* myString);
void printLogEntry(struct logEntry mylogentry);
void copyEntry(struct logEntry* dest, struct logEntry source);
void clearLogEntry(struct logEntry* entry);