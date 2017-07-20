#include "HEADER.h"

int main()
{
	pid_t p_id;
	int write_fd;
	int read_fd;
	int pipe_fd;
	char file_desR[4];
	char file_desW[4];
	int arr[2];//Array for creating pipe.
	char msg[160];
	int length;
	printf("File Name : %s || Before forking.\n", __FILE__);
        pipe_fd = pipe(arr);
	p_id = fork();
	switch(p_id)
	{
		case 0 : printf("I am child process with pid : %d and parents pid : %d || File Name : %s\n", getpid(), getppid(), __FILE__);
			 printf("Going to make execl call.\n");
			 //pipe_fd = pipe(arr);
			 if(pipe_fd == 0)	
			 {
				printf("Successflly created pipe!! || File Name : %s\n", __FILE__);
				printf("Child is going to write in pipe. Enter Messag..... || File Name : %s\n", __FILE__);
				fgets(msg, 160, stdin);
				length = strlen(msg);			
				write_fd = write(arr[1], msg, length);
				if(write_fd == -1)
				{
					printf("Error while writing!! || File Name : %s\n", __FILE__);
				}		
				else
				{
					printf("Successfully written %d bytes in pipe with file descriptor %d || File Name : %s\n", write_fd, arr[1], __FILE__);
				}
				sprintf(file_desR, "%d", arr[0]);
				sprintf(file_desW, "%d", arr[1]);
				execl("./test_program", "test_program", file_desR, file_desW, NULL);
				printf("Now I will not get executed.\n");		
			 } 
			 else
			 {
				printf("Error while creating pipe.");
			 }
			 break;
		case -1: printf("Forking Error!\n");
			 perror(fork);
			 break;
		default : printf("I am parent process with pid : %d and parents pid : %d || File Name : %s\n", getpid(), getppid(), __FILE__);
			  wait();//parent is waiting for child to finish execution.
 			  printf("Parent is here. Test Program scope finishes. File Name : %s\n", __FILE__);
                          read_fd = read(arr[0], msg, 160);
			  if(read_fd != -1)	
			  {
				msg[read_fd] = '\0';
				printf("Successfully read %d bytes. Message is %s || File Name : %s\n", read_fd, msg, __FILE__);
			  }
			  else
				printf("Error while reading....\n");
	}
	return 0;
	
}
