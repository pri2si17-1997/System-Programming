#include "HEADER.h"

int main()
{
	int fifo_ret;//return value of mkfifo()
	int r_fd;//return value of open. write file descriptor
	int length;//length of msg read
	char msg[160];
	printf("Filename : %s\n", __FILE__);
	printf("FIFO Name : %s\n", FIFONAME);
	if(access(FIFONAME, F_OK) == -1)
	{
		fifo_ret = mkfifo(FIFONAME, 666);
		if(fifo_ret == -1)
		{	
			printf("Error in creating FIFO aka Named Pipe..\n");
			exit(0);
		}
		printf("Successfully Created FIFO aka Named Pipe...File Name : %s\n", __FILE__);
	}
	r_fd = open(FIFONAME, O_RDONLY);
	if(r_fd == -1)
		printf("Error while opening..\n");
	else
		printf("Successfully opened FIFO... File Name : %s || File Descriptor : %d\n", __FILE__, r_fd);
	while(1)
        {
                length = read(r_fd, msg, 160);
		msg[length] = '\0';
                printf("Filename : %s || read %s of %d bytes.\n", __FILE__, msg,  length);
                if(strncmp(msg, "end", 3) == 0)
			break;
        }
	return 0;
}
