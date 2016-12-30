/*
 ============================================================================
 Name        : mSecSleep.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
	int time = atoi(argv[1]);
	struct timespec tim;
	tim.tv_sec = 0;
	tim.tv_nsec = time*1000000L;
	nanosleep(&tim, NULL);
}
