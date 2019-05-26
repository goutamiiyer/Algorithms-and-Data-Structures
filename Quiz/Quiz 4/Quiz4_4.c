#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

struct point {  
    int x;      
    int y;      
    int z;     
};

void mem_7(){        
    struct point * p;   
    p = (struct point *)malloc( sizeof(struct point *) );   
    x = 3;       
    y = 7;       
    z = 0;      
    free(p);   
}

int main() 
{
	mem_7();
	printf("p = %d\n", p);
}
