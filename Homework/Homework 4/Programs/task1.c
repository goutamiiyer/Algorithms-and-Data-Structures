#include <stdio.h>

int increasing(int * A, int N)
{
	int i;
	//for an empty array it returns 1
	//for an array with 1 element it returns 1.
	if (N == 0 || N == 1)
	{
		return 1;
	}
	for(i = 0; i < N; i++)
	{
		printf("A[%d]: %d\t", i, A[i]);	
	}

	//returns 1 if the elements in the array are in increasing order and 0 otherwise.
	//if all the array elements are equal it should return 1.

	for(i = N-1; i > 0; i--)
	{
		if(A[i] >= A[i-1])
		{
			printf("increasing(A,%d)\n", i);
			increasing(A,i);
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

int main()
{
	int A[100];
	int N,i;

	//In main (or another function that will be called in main),
	//repeatedly read arrays (first the array size and then that many elements) and
	//call this function, until the user gives -1 for the array size.
	scanf("%d", &N);
	while (N != -1)
	{
		for(i = 0; i < N; i++)
		{
			scanf("%d", &A[i]);	
		}
		int task1Result;
		task1Result = increasing(A, N);
		// printf("task1Result: %d\n", task1Result);
		printf(task1Result"\n");
		scanf("%d", &N);
	}
}
