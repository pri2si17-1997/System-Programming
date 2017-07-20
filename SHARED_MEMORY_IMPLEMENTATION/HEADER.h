#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>//for signals
#include<unistd.h>//for access
#include<fcntl.h>//for open, read, write
#include<sys/types.h>//for fifo
#include<sys/stat.h>//for fifo
#include<stdbool.h>//for boolean operation
#include<sys/shm.h>//for shared memory

#define MESSAGE_SIZE 2048
#define SHARED_MEMORY_SIZE 1024//1024 byte for shared memory.
struct struct_shared_mem
{
	int write_flag;
	char message[MESSAGE_SIZE];
};

