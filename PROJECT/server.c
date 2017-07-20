/*Serevr for receiving request.*/
#include "HEADER.h"

int main(int argc, char* argv[])
{
	pid_t p_id;//for fork between server and operator.
	int r_fd;
	int read_FD;//read file descriptor for client-server pipe communication.
	int write_FD;//write file descriptor for client-server pipe communication.
	struct request rec;
	int response_operator;
	int pipe_operator[2];
	int pipe_fd;
	char fdR[4];
	char fdW[4];
	int count_W;//to count no of bytes written in pipe for operstor.
	int count_R;//to count no of bytes read from pipe for operator.
	printf("File Name : %s\n", __FILE__);
	if(argc != 3)
	{
		printf("Insufficient arguments.\n");
		exit(0);
	}
	printf("Arguments Received : \n");
	printf("Argument 1 : %s || Filename : %s\n", argv[0], __FILE__);
        printf("Argument 2 : %s || Filename : %s\n", argv[1], __FILE__);
        printf("Argument 3 : %s || Filename : %s\n", argv[2], __FILE__);
	printf("Going to read throgh pipe..\n");
	read_FD = atoi(argv[1]);
	write_FD = atoi(argv[2]);
	r_fd = read(read_FD, &rec, sizeof(struct request));
	if(r_fd == -1)
	{
		printf("Error while reading from pipe. || File Name : %s\n", __FILE__);
		exit(0);
	}
	else
	{
		printf("Successfully read request... || File Name : %s\n", __FILE__);
		printf("%c %d %d\n", rec.sign, rec.operand_1, rec.operand_2);
		printf("Going to send request to operator..");
		pipe_fd = pipe(pipe_operator);
		if(pipe_fd == 0)
		{
			printf("Successfully created pipe.. || File Name : %s\n", __FILE__);
			sprintf(fdR, "%d", pipe_operator[0]);
                        sprintf(fdW, "%d", pipe_operator[1]);
		}
		else
		{
			printf("Error while creating file... || File Name : %s\n", __FILE__);
			exit(0);
		}
		p_id = fork();
		switch(p_id)
		{
			case 0 : printf("I am child process with id : %d & parents id : %d & File Name : %s\n", getpid(), getppid(), __FILE__);
				 printf("Passing Arguments to processor.... || File Name : %s\n", __FILE__);
				 count_W = write(pipe_operator[1], &rec, sizeof(struct request));
				 if(count_W == -1) 
				 {
					printf("Error while writing in pipe.. || File Name : %s", __FILE__);
					exit(0);
  				 }
				 else 
				 {
					printf("Successfully written %d bytes in pipe with file descriptor %d || File Name : %s\n", count_W, pipe_operator[1], __FILE__);
				 }
				 if(rec.sign == '+')
				 {
					execl("./adder", "adder", fdR, fdW, NULL );
				 }
				 else if(rec.sign == '-')
                                 {
                                        execl("./subtractor", "subtractor", fdR, fdW, NULL );
                                 }
				 else if(rec.sign == '*')
                                 {
                                        execl("./multiplicator", "multiplicator", fdR, fdW, NULL );
                                 }
				 printf("If correct info provided i will not get executed else i will.. || File Name : %s\n", __FILE__);
				 break;
			
			case -1: printf("Error while forking.. || File Name : %s\n", __FILE__);
    				 exit(0);
			
			default: printf("I am parent process with id : %d & parents id : %d & File Name : %s\n", getpid(), getppid(), __FILE__);
				 wait();
				 printf("I am parent still here. File Name : %s\n", __FILE__);
				 count_R = read(pipe_operator[0], &response_operator, sizeof(response_operator));
				 if(count_R != -1)
				 {
					printf("Successfully read %d bytes ||  File Name : %s || File Descriptor : %d\n", count_R, __FILE__, pipe_operator[0]);
					printf("Read Result is : %d\n", response_operator);
					printf("Going to write result in client pipe... || File Name : %s", __FILE__);
					count_W = write(write_FD, &response_operator, sizeof(response_operator));
					if(count_W != -1)
					{
						printf("Successfully written %d bytes. Result is %d. File Name : %s\n", count_W, response_operator, __FILE__);
					}
					
				 } 
				 else
				 {
					printf("Error while reading from pipe. File name : %s\n", __FILE__);
				 	exit(0);
				 }
		}
		return 0;
	}
	return 0;
}
