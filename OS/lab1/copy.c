#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#define SIZE 4

int main(int argc, char** argv)
{
	int src = open(argv[1], O_RDONLY);
    if(src < 0)
    {
    	printf("error to open file\n");
    	exit(-1);
    }
    
    int desc = open(argv[2],O_CREAT| O_APPEND |O_RDWR, 0777);
    if(desc < 0)
    {
    	printf("An error occurred when creating file\n");
    	exit(-1);
    }
    
    char buf[SIZE]; 
    int num = SIZE;
    while(num>=SIZE)
    {
		if((num = read(src, buf, SIZE)) < 0)
		{
			printf("An error occurred in the read.\n");
			exit(-1);
		}
		if(write(desc, buf, num) < 0)
		{
			printf("An error occurred in the write.\n");
			exit(-1);
		}
   	}
   	close(src);
   	close(desc);
	return 0;
}
