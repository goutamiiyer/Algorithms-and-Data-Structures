#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void test1(int v)
{
	v = 20;
	printf("test 1: v = %d\n", v);
}

void test2(int * v1)
{
	*v1 = 10;
    printf("test 2: v1 = %d\n", *v1);
} 

void test3(int * v1)
{
	v1 = (int*)malloc(sizeof(int));
    *v1 = 15;
    printf("test 3: v1 = %d\n", *v1);
}

int main(int argc, char** argv) 
{
	int v = 0;
	printf("main, 1, v = %d\n", v);
	test1(v);
	printf("main, 2, v = %d\n", v);
	int* v1;
	v1 = (int*)malloc(sizeof(int));
	*v1 = 5;
	printf("--------------------\n");
	printf("main, 3, v1 = %d\n", *v1);
	printf("main, 4, v1 = %d\n", v1);
	printf("--------------------\n");
	test2(v1);
	printf("main, 5: v1 = %d\n", *v1);
	printf("--------------------\n");
	test3(v1);
	printf("main, 6: v1 = %d\n", *v1);
	free(v1);
	return 0;
}
