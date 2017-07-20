/*PIPE is a shared resource. It must not be created inside child process. Here child writes to pipe and parent reads it. Else parent will go on block on read.*/

#include "HEADER.h"

int main()
{
	pid_t p_id;//for process id
	int r_fd, w_fd;//read file descriptor and write file descriptor
	char msg[160];
	char buffer[161];//storing the read message.
	int arr[2];//file descriptor for pipe. 0th index for read and 1st index for write.
	int pipe_fd;//return value for pipe. 0 fr success and -1 for failure.
	int length;//length of message
	printf("File Name : %s || Before doing fork.\n", __FILE__);
	pipe_fd = pipe(arr);//creating pipe.
	if(pipe_fd == 0)
		printf("Successfully created pipe....now going to write something....\n");
	else
	{
		printf("Error while creating pipe...\n");
		exit(0);
	}
	p_id = fork();
	switch(p_id)
	{
		case 0 : printf("Child Process with pid : %d & parent's pid : %d & File Name : %s\n", getpid(), getppid(), __FILE__);
			 printf("Going to write into pipe...\n");
			 //pipe_fd = pipe(arr);
			 fgets(msg, 160, stdin);
			 length = strlen(msg);
			 w_fd = write(arr[1], msg, length);
			 if(w_fd == -1)
			 	printf("Error in writing..\n");
			 else 
			 	printf("Successfully written %d bytes to pipe. File Name : %s\n", w_fd, __FILE__);
			 break;

		case -1: printf("Error while forking...\n");
			 break;

		default: printf("Parent Process with pid : %d & parent's pid : %d & File Name : %s\n", getpid(), getppid(), __FILE__);
			 wait();//wait for child process to finish execution.
			 printf("Reading from the pipe written by child.\n");
			 r_fd = read(arr[0], buffer, 160);
			 buffer[r_fd] = '\0';
			 if(r_fd == -1)
				printf("Error while reading...\n");
			 else
				printf("Successfully read %d bytes from pipe. File Name : %s || Message Read : %s\n", r_fd, __FILE__, buffer);
	}
	return 0;
}
