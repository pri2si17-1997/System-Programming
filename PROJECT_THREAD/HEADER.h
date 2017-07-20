#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<sys/msg.h>//For message queue
#include<sys/shm.h>//For shared memory
#include<pthread.h>//For thread library.

#define SHARED_MEMORY_SIZE 1024

