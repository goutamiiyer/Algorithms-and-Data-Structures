#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

struct point
{
	int x,y;
};

int main() 
{
	struct point temp1;
	printf("sizeof(temp1) = %d\n", sizeof(temp1));
	struct point *temp2;
	printf("sizeof(temp2) = %d\n", sizeof(*temp2));
}
