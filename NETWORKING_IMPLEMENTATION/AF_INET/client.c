#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<netinet/in.h>

struct request 
{
	char sign;
	int operand1;
	int operand2;
};

int main()
{
	int sock_client_fd;
	struct sockaddr_in client_address;
	size_t client_add_len;
	struct request R;
	int result;  
	//char ch = 'P';
	int connectRet;
	sock_client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_client_fd < 0)
	{
		printf("Error while creating socket. || FIle : %s \n", __FILE__);
		perror("socket");
	}
	else
	{
		printf("Successfully created socket. || File Descriptor : %d || File : %s\n", sock_client_fd, __FILE__);
	}
	//unlink("Server_Socket");
	client_address.sin_family = AF_INET;
	client_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	client_address.sin_port = htons(7777);
	//strcpy(client_address.sun_path, "Server_Socket");
	client_add_len = sizeof(struct sockaddr_in);
	connectRet = connect(sock_client_fd, (struct sockaddr *)&client_address, client_add_len);
	if(connectRet < 0)
	{
		printf("Error whie connecting... || File : %s\n", __FILE__);
		perror("connect");
		exit(EXIT_FAILURE);	
	}
	else
	{
		printf("Successfully connected with file descriptor : %d || FILE : %s\n", connectRet, __FILE__);
	}
	R.sign = '-';
	R.operand1 = 98;
	R.operand2 = 175;
	write(sock_client_fd, &R, sizeof(struct request));
	read(sock_client_fd, &result, sizeof(int));
	printf("Received request from server : %d || File : %s\n", result, __FILE__);
	return 0;
	
}
