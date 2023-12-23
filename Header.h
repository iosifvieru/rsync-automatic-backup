#ifndef __HEADER_H_ 
#define __HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void usage_error();

int readConfig(const char *fileName, char** source, char** destination, char** user, char** ip);

char* createArray(int __size);
void handle_interrupt(int signo);

#endif