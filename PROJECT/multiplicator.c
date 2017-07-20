/*This is adder.c. Processor for multiplication.*/

#include "HEADER.h"

int main(int argc, char* argv[])
{
	int read_FD;//read file descriptor for pipe between server and processor.(multiplicator)
	int write_FD;//wite file descriptor for pipe between server and processor.(multiplicator)
	int count_R;//bytes read from pipe.
	struct request R;//request from server.
	int result;//to calculate result.
	char ans[4];
	int count_W;
	printf("File Name : %s\n", __FILE__);
	if(argc != 3)
	{
		printf("Insufficient Arguments... || File Name : %s\n", __FILE__);
		exit(0);
	}
	else
	{
		printf("Arguments Received : \n");
	        printf("Argument 1 : %s || Filename : %s\n", argv[0], __FILE__);
        	printf("Argument 2 : %s || Filename : %s\n", argv[1], __FILE__);
        	printf("Argument 3 : %s || Filename : %s\n", argv[2], __FILE__);
		read_FD = atoi(argv[1]);
		write_FD = atoi(argv[2]);
		count_R = read(read_FD, &R, sizeof(struct request));
		if(count_R == -1)
		{
			printf("Error while reading from pipe created by server... || File Name : %s\n", __FILE__);
			exit(0);	
		}
		else
		{
			printf("Successfully read %d bytes from pipe. || File Name : %s || File Descriptor : %d || Read Request : %c %d %d\n", count_R, __FILE__, read_FD, R.sign, R.operand_1, R.operand_2);
			printf("Calculating Result... || File Name : %s\n", __FILE__);
			result = R.operand_1 * R.operand_2;
			printf("Result is : %d || File Name : %s\n", result, __FILE__);
			//sprintf(ans, "%d", result);
			count_W = write(write_FD, &result, sizeof(result));
			if(count_W == -1)
			{
				printf("Error while writing in pipe. || File Name : %s\n", __FILE__);
			}				
			else
			{
				printf("Successfully written %d bytes in pipe. File Name : %s\n", count_W, __FILE__);
			}
		}
	}
	return 0;
}
