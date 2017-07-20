#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>

int main()
{
	int sock_server_fd, sock_client_fd;
	struct sockaddr_un socket_address;
	struct sockaddr_un client_address;
	size_t server_add_len;
	size_t client_add_len;
	size_t clientLength;
	int bindRet;
	int acceptRet;
	char ch;
	sock_server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
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
	socket_address.sun_family = AF_UNIX;
	strcpy(socket_address.sun_path, "Server_Socket");
	server_add_len = sizeof(struct sockaddr_un);
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
	

	while(1)
	{
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
			read(acceptRet, &ch, 1);
			ch++;
			write(acceptRet, &ch, 1);	
		}
	}
	return 0;
	
}
