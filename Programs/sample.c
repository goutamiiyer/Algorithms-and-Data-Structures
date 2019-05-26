#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
	double begin,end;
	begin = clock();
	runtime_increment(10);
	end = clock();
	double time_spent = (double)(end - begin);
	printf("Time spent: %d", &time_spent);
	printf("Main function completed");
	return 0;
}
// run for N = 10, N = 100, N = 1000
void runtime_increment(int N){
int i, k, t, res = 0;
for(i = 1; i <= N; i=i+1)
for(k = 1; k <= i; k++)
for(t = 1; t <= N; t++)
res = res + 1;
}
// run for N = 10, N = 100, N = 300, N = 1000
/*void runtime _print(int N){
int i, k, t;
for(i = 1; i <= N; i=i+1)
for(k = 1; k <= i; k++)
for(t = 1; t <= N; t++)
printf("A");
}
// run for N = 10, N = 15, N = 20, N = 25, N = 30
void runtime _pow(int N){
int i, res = 0;
for(i = 1; i <= pow(2.0, (double)N); i=i+1)
res = res + 1;
}*/
