#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int* mem_3(){         // line 1
    int *p = 25;      // line 2
    printf("p = %d\n", *p);    // line 3
    return p;          // line 4
}

int main() 
{
	mem_3();
}
