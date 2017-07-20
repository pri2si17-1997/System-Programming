#include "HEADER.h"

void sig_handler(int sig_no)
{
	printf("Received Signal with id : %d\n", sig_no);
	exit(EXIT_SUCCESS);
}

int main()
{
	int fifo_ret;//return value of mkfifo()
	int w_fd;//return value of open. write file descriptor
	int length;//length of message
	int msg[160];//msg to write
	signal(SIGPIPE, sig_handler);
	printf("Filename : %s\n", __FILE__);
	if(access(FIFONAME, F_OK) == -1)
	{
		fifo_ret = mkfifo(FIFONAME, 666);
		if(fifo_ret == -1)
		{	
			printf("Error in creating FIFO aka Named Pipe..\n");
			return -1;
		}
		printf("Successfully Created FIFO aka Named Pipe...File Name : %s\n", __FILE__);
	}
	w_fd = open(FIFONAME, O_WRONLY);
	if(w_fd == -1)
		printf("Error while opening!!\n");
	else
		printf("Successfully opened FIFO... File Name : %s || File Descriptor : %d\n", __FILE__, w_fd);
	while(1)
	{
		fgets(msg, 160, stdin);
		length = strlen(msg);
		write(w_fd, &msg, length);
		printf("Filename : %s || wrote %s of %d bytes.\n", __FILE__, msg, length);
		if(strncmp(msg, "end", 3) == 0)
			break;
	}
	return 0;
}
