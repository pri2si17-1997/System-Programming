#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>//for signals
#include<unistd.h>//for access
#include<fcntl.h>//for open, read, write
#include<sys/types.h>//for fifo
#include<sys/stat.h>//for fifo
#include<stdbool.h>//for boolean operation

#define FIFONAME "./myFifo"
