#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int * mem_1_in(int x){  // line 1
    x = x + 2;          // line 2
    return &x;          // line 3
}

void mem_1(){           // line 4
    int x = 10;         // line 5
    int * p = mem_1_in(x);        // line 6
    printf("*p = %d\n\n", *p);    // line 7
}

int main(){
	mem_1();
}
