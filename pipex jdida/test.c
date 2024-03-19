#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
int main()
{
	int fd = open("test.txt", O_RDONLY);
	if(fd == -1)
	{
		printf("%d", errno);
		perror("");
	}
}