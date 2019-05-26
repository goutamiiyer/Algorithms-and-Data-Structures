#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void mem_5(){   // line 1
    int * p;    // line 2
    p = (int*)malloc(sizeof(int));   // line 3
    p = 7;      // line 4
    free(p);    // line 5
}

int main(){
	mem_5();
}  
