#include "HEADER.h"

int main(int argc, char* argv[])
{
	int rFD;
	int wFD;
	int read_desc;
	int write_desc;
	char msg[160];
	char buff[160];
	int length;
	char wrt_fd[4];
	char rd_fd[4];
	printf("I got called through execl. File Name : %s\n", __FILE__);
	if(argc != 3)
	{
		printf("Insufficient Arguments.... || File Name : %s\n", __FILE__);
		exit(0);
	}
	printf("Argument 1 : %s || Filename : %s\n", argv[0], __FILE__);
	printf("Argument 2 : %s || Filename : %s\n", argv[1], __FILE__);
	printf("Argument 3 : %s || Filename : %s\n", argv[2], __FILE__);
	read_desc = atoi(argv[1]);
	write_desc = atoi(argv[2]);
	rFD = read(read_desc, msg, 160);
	if(rFD == -1)
	{
		printf("Error while reading.\n");
	}
	else
	{
		msg[rFD] = '\0';
		printf("Successfully read %d bytes from pipe. Message : %s || File Name : %s\n", rFD, msg, __FILE__);
	}
	printf("File Name : %s || Going to write in same pipe. Enter Message : \n", __FILE__);
	fgets(buff, 160, stdin);
	length = strlen(buff);
	wFD = write(write_desc, buff, length);
	if(wFD == -1)
	{
		printf("Writing Error!!! || File Name : %s\n", __FILE__);
	}
	else
	{
		printf("Wriitten %d bytes successfully in pipe with file descriptor %d. File Name : %s\n", wFD, write_desc,  __FILE__);
	}
	printf("Going to call main Program.... || File Name : %s\n", __FILE__);
	return 0;
	
}
