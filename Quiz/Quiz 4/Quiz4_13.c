#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void mem_4(){   // line 1
    double d;   // line 2
    double *p;  // line 3
    p = &d;     // line 4
    *p = 7;     // line 5
} 

int main(){
	mem_4();
}  
