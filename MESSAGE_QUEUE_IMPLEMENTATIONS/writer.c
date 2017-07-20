#include "HEADER.h"

#define BUFF_SIZE 1024

struct mesg_qu
{
	long int type;
	char message[2048];
};

int main()
{
	int retMsgQId;//message queue created id.
	key_t key = 1210;//key for creating message queue.
	struct mesg_qu msg_to_snd;
	char buffer[BUFF_SIZE];
	int count_bytes;//No of bytes sent.
	printf("File Name : %s || Message : Creating Message Queue.", __FILE__);
	retMsgQId = msgget(key, 0666|IPC_CREAT);//creating mesage queue;
	if(retMsgQId < 0)
	{
		printf("Error while creating message queue.\n");
		perror("msgget");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Successfully created message queue with kernel key : %d\n", retMsgQId);
		msg_to_snd.type = 12;
		while(1)
		{
			printf("File Name : %s || Enter the message you want to send : ", __FILE__);
			fgets(buffer, BUFF_SIZE, stdin);		
			(void)strcpy(msg_to_snd.message, buffer);
			count_bytes = msgsnd(retMsgQId, &msg_to_snd, strlen(buffer), 0);//sending message. 0 for both read and write permissions
			if(count_bytes < 0)
			{
				printf("Error while sending message. || File Name: %s\n", __FILE__);
				perror("msgsnd");
				exit(EXIT_FAILURE);
			}
			else
			{
				printf("Successfully sent %d bytes data. || File Name : %s\n", count_bytes, __FILE__);
			}
			if(strncmp(buffer, "end", 3) == 0)
				break;	
		}
	}
	return 0;
}
