#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<pthread.h>
#include<sys/syscall.h>

#define MAX_THREAD_NUMBER 10000
int sock_server_fd;

struct request 
{
	char sign;
	int operand1;
	int operand2;
};


void *take_request(void *arg)
{
	struct sockaddr_in client_address;
        size_t clientLength;
	printf("clientLength : %d\n", clientLength);
	int acceptRet;
	struct request R;
	int result;
	pid_t thread_id = pthread_self();
	printf("Created thread with id : %d || File : %s\n", thread_id, __FILE__);
	printf("Waiting for client. || File : %s\n", __FILE__);
        acceptRet = accept(sock_server_fd, (struct sockaddr *)&client_address, &clientLength);
        if(acceptRet == -1)
        {
        	printf("Error while accepting request... || File : %s\n", __FILE__);
                perror("accept");
                exit(EXIT_FAILURE);
        }
        else
        {
        	printf("Successfully accepted request with file descriptor : %d\n", acceptRet);
                read(acceptRet, &R, sizeof(struct request));
                printf("Request is : %c %d %d. File Name : %s\n", R.sign, R.operand1, R.operand2, __FILE__);
                if(R.sign == '+')
                {
                	result = R.operand1 + R.operand2;
                }
                else if(R.sign == '-')
                {
                        result = R.operand1 - R.operand2;
                }
                else if(R.sign == '*')
                {
                        result = R.operand1 * R.operand2;
                }
                write(acceptRet, &result, sizeof(int));
        }
	printf("Going to terminate... || Function : %s\n", __func__);
	pthread_exit("EXECUTED SUCCESSFULLY....");
}

int main()
{
	int sock_client_fd;
	struct sockaddr_in socket_address;
	struct sockaddr_in client_address;
	size_t server_add_len;
	size_t client_add_len;
	size_t clientLength;
	int bindRet;
	int thread_ret;
	int acceptRet;
	int i;
	pthread_t t_id[MAX_THREAD_NUMBER];
	//char ch;
	int result = 0;
	struct request R;
	void *arg;
	sock_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_server_fd < 0)
	{
		printf("Error while creating socket. || FIle : %s \n", __FILE__);
		perror("socket");
	}
	else
	{
		printf("Successfully created socket. || File Descriptor : %d || File : %s\n", sock_server_fd, __FILE__);
	}
	unlink("Server_Socket");
	socket_address.sin_family = AF_INET;
	socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
	socket_address.sin_port = htons(7777);
	//strcpy(socket_address.sun_path, "Server_Socket");
	server_add_len = sizeof(struct sockaddr_in);
	bindRet = bind(sock_server_fd, (struct sockaddr *)&socket_address, server_add_len);
	if(bindRet < 0)
	{
		printf("Error while binding... || FIle : %s\n", __FILE__);
		perror("bind");
	}
	else
	{
		printf("Successfully bound socket.. | File : %s\n", __FILE__);
	}
	printf("Now Listening for request... | FILE : %s\n", __FILE__);
	if(listen(sock_server_fd, 5 ) == -1)
	{	
		printf("Error while listening.. || FIle : %s\n", __FILE__);	
	}
	else
	{
		printf("Successfully listened for %d requset in queue. || File : %s\n", 5,__FILE__);
	}
	
	i = 0;
	while(1)
	{
		/*printf("Waiting for client. || File : %s\n", __FILE__);
		acceptRet = accept(sock_server_fd, (struct sockaddr *)&client_address, &clientLength);
		if(acceptRet == -1)
		{
			printf("Error while accepting request... || File : %s\n", __FILE__);
			perror("accept");
			exit(EXIT_FAILURE);	
		}
		else
		{
			printf("Successfully accepted request with file descriptor : %d\n", acceptRet);
			read(acceptRet, &R, sizeof(struct request));
			printf("Request is : %c %d %d. File Name : %s\n", R.sign, R.operand1, R.operand2, __FILE__);
			if(R.sign == '+')
			{
				result = R.operand1 + R.operand2;	
			}
			else if(R.sign == '-')
			{
				result = R.operand1 - R.operand2;	
			}
			else if(R.sign == '*')
			{
				result = R.operand1 * R.operand2;
			}
			write(acceptRet, &result, sizeof(int));	
		}*/
		thread_ret = pthread_create(&t_id[i], NULL, take_request, NULL);
		if(thread_ret < 0)
		{	
			printf("Error while creating thread. || Func : %s\n", __func__);
			perror("pthread_create");
		}
		else
		{
			printf("Successfully created thread : %d || Function : %s\n", i, __func__);
			pthread_join(t_id[i], &arg);
			printf("Received from thread %d : Function : %s | Returned Value : %s\n", i, __func__, (char*)arg);	
		}
		i++;
	}
	return 0;
	
}
