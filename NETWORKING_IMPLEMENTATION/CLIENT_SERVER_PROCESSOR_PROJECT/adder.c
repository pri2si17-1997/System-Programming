#include "HEADER.h"

int main()
{
	int sock_client_fd;
	struct sockaddr_un client_address;
	size_t client_add_len;
	//char ch = 'P';
	struct request R;
	int connectRet;
	int result;
	sock_client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
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
	client_address.sun_family = AF_UNIX;
	strcpy(client_address.sun_path, "Server_Socket");
	client_add_len = sizeof(struct sockaddr_un);
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
	//write(sock_client_fd, &ch, 1);
	read(sock_client_fd, &R, sizeof(struct request));
	printf("Received request from server : %c %d %d || File : %s\n", R.sign, R.operand1, R.operand2, __FILE__);
	result = R.operand1 + R.operand2;
	write(sock_client_fd, &result, sizeof(int));
	return 0;
	
}
