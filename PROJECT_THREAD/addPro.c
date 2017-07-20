/*Processor to write in shared memory*/
#include "HEADER.h"

struct request
{
	char sign;
	int operand1;
	int operand2;
};

struct shared_memory
{
	int writeFlag;
	struct request* Req;	
};


struct request R;

int main()
{
	key_t key = 1210;//key to create shared memory.
	bool flag = true;
	void *shared_memory = (void *)0;//NULL
	int shmKernelKey;//get the shared memory id.
	struct shared_memory *shared_stuffs;
	shmKernelKey = shmget(key, SHARED_MEMORY_SIZE, 0666|IPC_CREAT);
	printf("File Name : %s\n", __FILE__);
	if(shmKernelKey == -1)
	{
		printf("Error while creating shared memory.");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Successfully created shared memory with kernel key : %d || File Name : %s\n", shmKernelKey, __FILE__);
	}
	shared_memory = shmat(shmKernelKey, (void* )0, 0);
	if(shared_memory == (void *)-1)
	{
		printf("Error while attaching shared memory. || File Name : %s\n", __FILE__);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Successfully attached at memory location : %X || File Name : %s\n", (int)shared_memory, __FILE__);
	}
	return 0;
}
