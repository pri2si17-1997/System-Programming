#include "HEADER.h"

int main()
{
	int client_fd;//file decriptor for client socket.
	struct sockaddr_in client_address;
        socklen_t client_address_len;
        struct request R;
        int result;
        int connectRet;//return value of connect call.
        client_fd = socket(AF_INET, SOCK_STREAM, 0);
        if(client_fd < 0)
        {
                printf("Error while creating socket. || FIle : %s \n", __FILE__);
                perror("socket");
		exit(EXIT_FAILURE);
        }
        else
        {
                printf("Successfully created socket. || File Descriptor : %d || File : %s\n", client_fd, __FILE__);
        }
        
	/*configuring client socket*/
        client_address.sin_family = AF_INET;
        client_address.sin_addr.s_addr = inet_addr("127.0.0.1");
        client_address.sin_port = htons(7777);
        
        client_address_len = sizeof(struct sockaddr_in);
        connectRet = connect(client_fd, (struct sockaddr *)&client_address, client_address_len);
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
        R.sign = '+';
        R.operand1 = 98;
        R.operand2 = 175;
        write(client_fd, &R, sizeof(struct request));
        read(client_fd, &result, sizeof(int));
        printf("Received response from server : %d || File : %s\n", result, __FILE__);
	return 0;
}
