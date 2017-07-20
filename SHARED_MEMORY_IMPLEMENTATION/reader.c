/*Writer program for shared memory. Task is to write some content to shared memory segment*/
#include "HEADER.h"

#define BUFFER_SIZE 1024
int main()
{
	key_t key = 1210;//key to create shared memory.
	bool flag = true;
	void *shared_memory = (void *)0;//NULL
	int kernel_key;//get the shared memory id.
	struct struct_shared_mem *shared_stuffs;
	char msg_buffer[BUFFER_SIZE];
	kernel_key = shmget(key, SHARED_MEMORY_SIZE, 0666|IPC_CREAT);
	printf("File Name : %s\n", __FILE__);
	if(kernel_key == -1)
	{
		printf("Error while creating shared memory.");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Successfully created shared memory with kernel key : %d || File Name : %s\n", kernel_key, __FILE__);
	}
	shared_memory = shmat(kernel_key, (void* )0, 0);
	if(shared_memory == (void *)-1)
	{
		printf("Error while attaching shared memory. || File Name : %s\n", __FILE__);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Successfully attached at memory location : %X || File Name : %s\n", (int)shared_memory, __FILE__);
	}
	shared_stuffs = (struct struct_shared_mem* )shared_memory;
	shared_stuffs->write_flag = 0;
     	while(flag)
	{
		while(shared_stuffs->write_flag)
		{
			printf("Received Message : %s || File Name : %s\n", shared_stuffs->message, __FILE__);
			sleep(2);//make the writer to wait for some time.
			shared_stuffs->write_flag = 0;
			if(strncmp(shared_stuffs->message, "end", 3) == 0)
                	{
                        	flag = false;
                	}		
		}
	}	
	if(shmdt(shared_memory) == -1)//detaching shared memory
	{
		printf("Error while detaching memory. File Name : %s\n", __FILE__);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Successfully detached memory. File Name : %s\n", __FILE__);
	}
	return 0;
}
