/*This is server program intended to read request and send the request to processor */
#include "HEADER.h"
#define MSG_SIZE 2048

/*Structure for request.*/
struct request
{
	char sign;
	int operand1;
	int operand2;	
};

/*Structure for message queue.*/

struct message_queue
{
        long int type;
        struct request R;
};

struct request R;//To read the structure object.
struct message_queue mq;//To read from message queue.
//struct request* Req;

/*Declared global variables so that thread can use it.*/

key_t key_receive = 1234;//key value to get message queue of same id.
int kernelKey;//return value of shmget.
int bytesRead;//no of bytes read from message queue.
	
void *receive_request(void *arg)
{
	pthread_t id = pthread_self();
	char msg[MSG_SIZE];
	printf("File Name : %s || Function Name : %s || Process Id : %d || Parent Process Id : %d.\n", __FILE__, __func__, getpid(), getppid());
	printf("Successfully created thread with id : %lu\n.", id);
	printf("Going to read Requests ... \n");
	bytesRead = msgrcv(kernelKey, (void* )&mq, sizeof(struct request), 0, 0);//Receiving message. 0 for both read and write permission and to read data of all types.
	if(bytesRead < 0)
	{
		printf("Failed to read request..\n");
		perror(msgrcv);
	}
	else
	{
		printf("Successfully read %d bytes from message queue. || File Name : %s\n", bytesRead, __FILE__);
	}
	printf("%ld\n", mq.type);
	//Req = &mq.R;
	printf("Request is : %c %d %d.\n", mq.R.sign, mq.R.operand1, mq.R.operand2);
	strcpy(msg, "Hello I have successfully executed.");
	pthread_exit((void*)msg);
}

int main()
{
	//mq.R = (struct request*)malloc(sizeof(struct request));
	pthread_t thread_id[10];
	int thread_ret;
	int i;
	void *received_arg;
	printf("File Name : %s || Function Name : %s || Process Id : %d || Parent Process Id : %d.\n", __FILE__, __func__, getpid(), getppid());
	/*Creating Message Queue.*/
	printf("Going to create Message Queue.\n");
	kernelKey = msgget(key_receive, 0666|IPC_CREAT);//creating mesage queue;
	if(kernelKey < 0)
	{
		printf("Error while creating message queue.\n");
                perror("msgget");
                exit(EXIT_FAILURE);
	}
	else
	{
		printf("Successfully created message queue with kernel key : %d || File Name : %s.\n", kernelKey, __FILE__);
	}
	printf("Going to create thread..\n");
	/*Creating thread to read request*/
	for(i = 0; i<1; i++)
	{
		thread_ret = pthread_create(&thread_id[i], NULL, receive_request, &i);
		if(thread_ret != 0)
		{
			printf("Failed to create thrread. File Name : %s || Function Name : %s || Process Id : %d || Parent Process Id : %d.\n", __FILE__, __func__, getpid(), getppid());
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
		printf("Created thread %d.\n", i);
	}	
	printf("Joining Threads .....\n");
	for(i = 0; i<1; i++)
	{
		pthread_join(thread_id[i], &received_arg);
		printf("Received Request : %s\n", (char*)received_arg);
	}
	return 0;
}

