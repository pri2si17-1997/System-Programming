/*--------------------------------------------------------------------------------------*/
/*|Hyper threaded server to take request from client and send it to processing client on| 
  |same machine and then write the result back to client.				|*/
/*--------------------------------------------------------------------------------------*/

#include "HEADER.h"

/*Max thread number to be created by server.*/
#define MAX_THREAD 10000

/*Global Variables. To be used by main thread and thread function.*/
int server_fd;//file descriptor of server socket.
int processor_fd;//file descriptor for processor.

/*Function to make AF_UNIX connection between server and processing client.*/
void getProcessorConnection()
{
	int sock_server_fd;
        struct sockaddr_un socket_address;
        struct sockaddr_un client_address;
        size_t server_add_len;
        size_t client_add_len;
        socklen_t clientLength;
        int bindRet;
        int acceptRet;
	clientLength = sizeof(client_address);
	printf("clientLength : %d\n", clientLength);
        sock_server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
        if(sock_server_fd < 0)
        {
                printf("Error while creating socket. || FIle : %s || Function : %s\n", __FILE__, __func__);
                perror("socket");
		exit(EXIT_FAILURE);
        }
        else
        {
                printf("Successfully created socket. || File Descriptor : %d || File : %s || Function : %s\n", sock_server_fd, __FILE__, __func__);
        }
        unlink("Server_Socket");
        socket_address.sun_family = AF_UNIX;
        strcpy(socket_address.sun_path, "Server_Socket");
        server_add_len = sizeof(struct sockaddr_un);
        bindRet = bind(sock_server_fd, (struct sockaddr *)&socket_address, server_add_len);
        if(bindRet < 0)
        {
                printf("Error while binding... || FIle : %s || Function : %s\n", __FILE__, __func__);
                perror("bind");
		exit(EXIT_FAILURE);
        }
        else
        {
                printf("Successfully bound socket.. | File : %s || Function : %s\n", __FILE__, __func__);
        }
        //printf("Waiting for processor. || File : %s || Function : %s\n", __FILE__, __func__);
	if(listen(sock_server_fd, 5) == -1)
	{
		printf("Error while listening.. || File : %s || Function : %s\n", __FILE__, __func__);
		perror("listen");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Successfully listened.... || File : %s || Function : %s\n", __FILE__, __func__);
	}
	printf("Waiting for processor. || File : %s || Function : %s\n", __FILE__, __func__);
        processor_fd = accept(sock_server_fd, (struct sockaddr *)&client_address, &clientLength);
        if(processor_fd == -1)
        {
        	printf("Error while accepting request... || File : %s || Function : %s\n", __FILE__, __func__);
                perror("accept");
                exit(EXIT_FAILURE);
        }
        else
        {
              	printf("Successfully accepted request with file descriptor : %d || File : %s || Function : %s\n", processor_fd, __FILE__, __func__);
        }
} 

/*Thread Fuction.*/
void *fetch_request(void *arg)
{
	struct sockaddr_in client_address;
	socklen_t clientLength = sizeof(client_address);
	printf("clientLength : %d\n", clientLength);
	int acceptRet;//Retun value of accept call i.e. file descriptor of client
	struct request R;//to get the structure object.
	int result;
	pid_t threadId;
	/*Print thread number.*/
	threadId = syscall(SYS_gettid);
	printf("Created thread with id : %d. || File Name : %s || Function : %s\n", threadId, __FILE__, __func__);
	
	/*Making accept call.*/
	printf("Waiting for client..|| File Name : %s || Function : %s\n", __FILE__, __func__);
	acceptRet = accept(server_fd, (struct sockaddr *)&client_address, &clientLength);
	//acceptRet = accept(server_fd, (struct sockaddr*)&client_address, &clientLength);
	if(acceptRet < 0)
	{
		printf("Error while accepting request.. || File : %s || Function : %s\n", __FILE__, __func__);
		perror("accept");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Accept Successful.. || File Descriptor : %d || File : %s || Function : %s\n", acceptRet, __FILE__, __func__);
		read(acceptRet, &R, sizeof(struct request));
		printf("Request is : %c %d %d. || File Name : %s || Function : %s\n", R.sign, R.operand1, R.operand2, __FILE__, __func__);
		
		/*Now going to write result to processor*/
		write(processor_fd, &R, sizeof(struct request));
		read(processor_fd, &result, sizeof(int));
		printf("Received Result from processor : %d || File Name : %s || Function Name : %s\n", result, __FILE__, __func__);
		
		/*Now going to write result to client*/
		write(acceptRet, &result, sizeof(int));
	}
	pthread_exit("SUCCESSFULLY EXECUTED....");
}

int main()
{
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	size_t server_address_length;
	size_t client_address_length;
	size_t clientLength;
	int bindRet;//Return value of bind call for server and client
	int i;//counter
	pthread_t thread_id[MAX_THREAD];
	int threadRet;//return value of created thread.
	void *receivedArg;//Arguments received from server
	
	/*Creating Socket for server*/
	server_fd = socket(AF_INET, SOCK_STREAM, 0);//creating socket of AF_INET type.
	if(server_fd < 0)
	{
		printf("Error while creating server socket for server-client communication. File Name : %s || Function Name : %s\n", __FILE__, __func__);
		perror("socket");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Successfully created socket. File Descriptor : %d || File : %s || Function : %s\n", server_fd, __FILE__, __func__);
	}
	
	/*Configuring socket for AF_INET*/
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);//to accept request from any ip. Server must be designed to accept request from all clients.
	server_address.sin_port = htons(7777);
	
	server_address_length = sizeof(struct sockaddr_in);
	
	/*Binding socket*/
	bindRet = bind(server_fd, (struct sockaddr *)&server_address, server_address_length);
	if(bindRet < 0)
	{
		printf("Error while binding socket.. || File : %s || Function : %s\n", __FILE__, __func__);
		perror("bind");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Successfully bound socket.. || File : %s || Function : %s\n", __FILE__, __func__);
	}

	/*Listening For Request.*/
	printf("Now Listening for request... || File : %s || Function : %s\n", __FILE__, __func__);
	if(listen(server_fd, 5) == -1)
	{
		printf("Error while listening... || FILE : %s || Function : %s\n", __FILE__, __func__);
		perror("listen");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Successfully Listened for %d Request in queue. || File : %s || Function : %s\n", 5, __FILE__, __func__);
	}

	/*Making connection between server and processor.*/
	getProcessorConnection();

	/*Making server to run in infinite while loop*/
	i = 0;
	while(1)
	{
		threadRet = pthread_create(&thread_id[i], NULL, fetch_request, NULL);
		if(threadRet < 0)
		{
			printf("Error while creating thread. || File : %s || Function : %s\n", __FILE__, __func__);
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("Successfully created thread : %d || File : %s || Function : %s\n", i, __FILE__, __func__);
			pthread_join(thread_id[i], &receivedArg);
			printf("Received from thread %d. || File : %s || Function : %s || Returned Value : %s\n", i, __FILE__, __func__, (char*)receivedArg);
		}
	}
	return 0;
}
