#include "HEADER.h"

int main()
{
	int arr[2];//0th index will open for read and 1st index will open for write.Pipe is implemented as circular queue internally and is in RAM of 64K.
	int pipe_fd;
	pipe_fd = pipe(arr);
	if(pipe_fd == 0)
		printf("Filename : %s || Successfully created pipe.\n", __FILE__);
	else
		printf("Filename : %s || Error in creating pipe.\n", __FILE__);
	return 0;
}
