#include "HEADER.h"

void *thread_function(void *arg)
{
	char *msg;
	char buffer[2048];
	printf("I am thread. Executing parlally with main thread. File Name : %s || Pid : %d || Parents id : %d\n", __FILE__, getpid(), getppid());
	msg = (char* )arg;
	printf("Received Arguments : %s\n", msg);
	strcpy(buffer, "I am sending result.");
	printf("Calling execl..\n");
	execl("./test_file", "test_file", "saumya", "priyanshu", NULL);
	print("Thread created is exiting.\n");	
	pthread_exit((void*) buffer);
}

int main()
{
	pthread_t id = 1024;
	void* ret_val;
	int thread_ret;
	printf("This is main thread. With pid : %d & Parent's Pid : %d & File Name : %s\n", getpid(), getppid(), __FILE__);
	thread_ret = pthread_create(&id, NULL, thread_function, "Hello, I am sending u argument");
	if(thread_ret != 0)
	{
		printf("Error while creating thread. || File Name : %s\n", __FILE__);
	}
	else
	{
		printf("Successfulluy created thread.\n");
		sleep(5);
		printf("Receiving return value......\n");
		pthread_join(id, &ret_val);
		printf("Returned Value is : %s\n", (char*)ret_val);
	}
	return 0;
	
}
