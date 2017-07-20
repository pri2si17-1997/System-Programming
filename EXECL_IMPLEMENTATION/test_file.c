/* A simple program which is called by execl in child process of other program and command line argumemnts is passed.*/

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	int i;
	printf("File Name : %s || I am being called by execl.\n", __FILE__);
	if(argc != 3)
	{
		printf("Insufficient Arguments!!\n");
		exit(0);
	}
	else
	{
		for(i = 0; i < argc; i++)
		{
			printf("Filename : %s || %d argument is %s.\n", __FILE__, i, argv[i]);
		}
	}
	return 0;
}
