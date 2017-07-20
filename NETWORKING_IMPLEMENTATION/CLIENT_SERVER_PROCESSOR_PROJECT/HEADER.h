#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*Specific Header Files*/
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

/*Network Specific Header Files*/
#include<sys/socket.h>

/*For AF_INET Type*/
#include<netinet/in.h>
#include<arpa/inet.h>

/*For AF_UNIX type*/
#include<sys/un.h>

/*For pthread library. Only for server*/
#include<pthread.h>
#include<sys/syscall.h>//To get the thread id.

/*Structure of request*/
struct request
{
	char sign;
	int operand1;
	int operand2;
};
