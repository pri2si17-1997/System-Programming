/*client program to write request to server.*/

#include "HEADER.h"

#define BUFF_SIZE 1024

struct request 
{
	char sign;
	int operand1;
	int operand2;
};

struct message_queue
{
        long int type;
        struct request R;
};

struct request R;
//struct request *req;
struct message_queue mq;

int main()
{
	key_t key_create = 1234;//key to create message queue.
	int kernelKey;//kernel key to return after successfully creating message queue.
	int bytesWritten;//number of bytes written in message queue.
	printf("File Name : %s || Function Name : %s || Process Id : %d || Parent Process Id : %d.\n", __FILE__, __func__, getpid(), getppid());	 kernelKey = msgget(key_create, 0666|IPC_CREAT);
	if(kernelKey < 0)
	{
		printf("Error while creating message queue.\n");
                perror("msgget");
                exit(EXIT_FAILURE);
	}
	else
	{
		printf("Successfully created message queue with kernel key : %d || File Name : %s.\n", kernelKey, __FILE__);
		printf("Enter Request : .\n");
		printf("Enter Operation to be performed (+ --> Addition || - --> Subtraction || * --> Multiplication): ");
		scanf("%c", &R.sign);
		printf("Enter Operand 1 : ");
		scanf("%d", &R.operand1);
		printf("Enter Operand 2 : ");
                scanf("%d", &R.operand2);
		if(R.sign == '+')
			mq.type = 1;
		else if(R.sign == '-')
			mq.type = 2;
		else if(R.sign == '*')
			mq.type = 3;
		//req = &R;
		mq.R = R;
		printf("Successfully copied structure. Now printing data...\n");
		printf("Request is : %c %d %d. || Type : %ld.\n", mq.R.sign, mq.R.operand1, mq.R.operand2, mq.type);
		bytesWritten = msgsnd(kernelKey, (void* )&mq, sizeof(struct request), 0);//sending message. 0 for both read and write permissions. msgsnd() always returns 0.
		if(bytesWritten < 0)
		{
			printf("Error while writing request in message queue. || File Name : %s.\n", __FILE__);
			perror("msgsnd");
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("Successfully sent %d bytes data. || File Name : %s\n", bytesWritten, __FILE__);
		}
	}
	return 0;
}
