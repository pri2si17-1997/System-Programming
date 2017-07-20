/*This is client program. Client 1*/

#include "HEADER.h"

int main()
{
	int arr[2];//create pipe for communication between client server.
	struct request R;//to send request to server.
	int pipe_fd;//return value of pipe.
	pid_t p_id;
	int response;
	char operation;
	int operand_1;
	int operand_2;
	int w_fd;
	char read_fd[4];
	char write_fd[4];
	int read_FD;
	printf("File Name : %s || Going to send request to server using fork...\n", __FILE__);
	pipe_fd = pipe(arr);
	if(pipe_fd != 0)
	{
		printf("Error while creating pipe. || File Name : %s\n", __FILE__);
		exit(0);
	}
	p_id = fork();
	switch(p_id)
	{
		case 0 : printf("I am child process with id : %d & parents id : %d & Filename : %s\n", getpid(), getppid(), __FILE__);
			 printf("Going to call server through execl. || File Name : %s\n", __FILE__);
			 printf("Enter Request : \n");
			 printf("Enter Operation to be Performed : (+ --> Addition || - --> Subtraction || * --> Multiplication) : ");
			 scanf("%c", &operation);
			 printf("Enter 1st Operand : ");
			 scanf("%d", &operand_1);
			 printf("Enter 2nd Operand : ");
			 scanf("%d", &operand_2);
			 R.sign = operation;
			 R.operand_1 = operand_1;
			 R.operand_2 = operand_2;
	 		 printf("%c %d %d\n", R.sign, R.operand_1, R.operand_2);
			 w_fd = write(arr[1], &R, sizeof(struct request));
			 if(w_fd != -1)
			 {
				printf("Successfully written %d bytes in pipe with file_descritor : %d || File Name : %s\n", w_fd, arr[1], __FILE__);
				sprintf(read_fd, "%d", arr[0]);
				sprintf(write_fd, "%d", arr[1]);
				execl("./server", "server", read_fd, write_fd, NULL);
				printf("Now i've completed my task. I will not get executed furteher. Good Bye.. \n");				
			 }
			 else
			 {
 				printf("Error while writing in pipe.\n");
			 }
			 break;
		
		case -1: printf("Error while forking... || File Name : %s\n", __FILE__);
			 exit(0);
			 break;

		default: printf("I am parent process with id : %d & parents id : %d & Filename : %s\n", getpid(), getppid(), __FILE__);
			 wait();//waiting for child process to finish execution.
			 printf("I am parent || File Name : %s || I am still here.\n", __FILE__);
			 printf("Going to receive the result... || File Name : %s\n", __FILE__);
			 read_FD = read(arr[0], &response, sizeof(response));
			 if(read_FD != -1)
			 {
				printf("Successfully read result. Response is %d of %d bytes. || File Name : %s\n", response, read_FD, __FILE__);
			 }	 
			 else
			 {
				printf("Error while reading result. File Name : %s\n",__FILE__);
				exit(0);
			 }
	}
	return 0;
}
