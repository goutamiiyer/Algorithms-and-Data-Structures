#include <stdio.h>

//**Task 1
int increasing(int * A, int N)
{
	int i;
	//for an empty array it returns 1
	//for an array with 1 element it returns 1.
	if (N == 0 || N == 1)
	{
		return 1;
	}

	//returns 1 if the elements in the array are in increasing order and 0 otherwise.
	//if all the array elements are equal it should return 1.

	for(i = N-1; i > 0; i--)
	{
		if(A[i] >= A[i-1])
		{
			increasing(A,i);
		}
		else
		{
			return 0;
		}
	}
	return 1;
}
//**End of Task 1

//**Task 2
int min_rec_1(int* A, int N, int* base_ct, int* rec_ct)
{
	int temp;

	if (N==1)
	{
		*base_ct = *base_ct + 1;
		return A[0];
	}

	temp = min_rec_1(A,N-1,base_ct,rec_ct);
	*rec_ct = *rec_ct + 1;

	if (temp < A[N-1])
	{
		return temp;
	}
	else 
	{
		return A[N-1];	
	}
}

int min_rec_2(int* A, int N, int* base_ct, int* rec_ct)
{
	if (N==1)
	{
		*base_ct = *base_ct + 1;
		return A[0];	
	}
	if (min_rec_2(A,N-1,base_ct, rec_ct) < A[N-1])
	{
		*rec_ct = *rec_ct + 1;
		return min_rec_2(A,N-1,base_ct, rec_ct);
	}
	else
	{
		*rec_ct = *rec_ct + 1;
		return A[N-1];	
	}
}

int min_rec_tail(int* A, int N, int* base_ct, int* rec_ct, int min)
{
	*rec_ct += 1;
	if(N == 1)
	{
		*base_ct = *base_ct + 1;
		return A[0];
	}
	N -= 1;
	if(A[0] > A[N]) 
	{
		min = min_rec_tail(A+1, N, base_ct, rec_ct, min);
		//A+1, 3, 0, 2
	}
	else
	{
		min = min_rec_tail(A, N, base_ct, rec_ct, min);
		//A, 4, 0, 1
		//A+1, 2, 0, 3
		//A+1, 1, 0, 4
	}
	return min;
}

int min_rec_wrapper(int* A, int N, int* base_ct, int* rec_ct)
{
	if(N == 1)
	{
		*base_ct = *base_ct + 1;
		return A[0];
	}
	int min;
	return min_rec_tail(A,N,base_ct,rec_ct,min);
}
//**End of Task 2

int main()
{
	int A[100];
	int N1,N2,i;
	//Task 2
	int rec_ct = 0;
	int base_ct = 0;
	// Task 3
	char s[100];
	int decomp_ct = 0;

//**Task 1
	printf("Enter size of array. (Stop with -1.) ");
	scanf("%d", &N1);
	while (N1 != -1)
	{
		printf("Enter array elements separated by spaces: ");
		for(i = 0; i < N1; i++)
		{
			scanf("%d", &A[i]);	
		}
		int task1Result;
		task1Result = increasing(A, N1);
		printf("increasing: %d\n", task1Result);
		printf("Enter size of array. (Stop with -1.) ");
		scanf("%d", &N1);
	}
//**End of Task 1

	printf("\n\n");

//**Task 2
	printf("Enter size of array. (Stop with -1.) ");
	scanf("%d", &N2);
	while(N2 != -1 && N1 == -1)
	{
		printf("Enter array elements separated by spaces: ");
		for(i = 0; i < N2; i++)
		{
			scanf("%d", &A[i]);	
		}
		int rec_1;
		rec_1 = min_rec_1(A,N2,&base_ct,&rec_ct);
		printf("\nsmallest_1:		smallest = %d, base_ct = %d, rec_ct = %d\n", rec_1, base_ct, rec_ct);
		base_ct = 0; rec_ct = 0;
		int rec_2;
		rec_2 = min_rec_2(A,N2,&base_ct,&rec_ct);
		printf("smallest_2:		smallest = %d, base_ct = %d, rec_ct = %d\n", rec_2, base_ct, rec_ct);
		base_ct = 0; rec_ct = 0;
		int rec_3;
		rec_3 = min_rec_wrapper(A,N2, &base_ct, &rec_ct);
		printf("smallest_tail:		smallest = %d, base_ct = %d, rec_ct = %d\n", rec_3, base_ct, rec_ct);
		base_ct = 0; rec_ct = 0;

		printf("Enter size of array. (Stop with -1.) ");
		scanf("%d", &N2);
	}
//**End of Task 2

	printf("\n\n");
}
