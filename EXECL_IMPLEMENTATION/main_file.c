#include "HEADER.h"

int main()
{
	pid_t p_id;
	printf("File Name : %s || Just before forking, I will call another program to run..\n", __FILE__);
	p_id = fork();
	switch(p_id)
	{
		case 0 : printf("I am child process with pid : %d & Parent's pid : %d & File Name : %s\n", getpid(), getppid(), __FILE__);
			 printf("Going to execute execl..\n");
			 execl("./test_file", "test_file", "saumya", "priyanshu", NULL);
			 printf("This line will not execute.\n");
			 break;

		case -1 : printf("Forking Error!\n");
			  break;

		default : printf("I am parent process with pid : %d & Parent's pid : %d & File Name : %s\n", getpid(), getppid(), __FILE__);
			  printf("Waiting for child to do stuffs...\n");
			  wait();
			  printf("Child has done his stuffs...\n");
	}
	return 0;
}
