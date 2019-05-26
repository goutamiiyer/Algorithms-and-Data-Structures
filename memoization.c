int foo1(int N){
 if (N <= 3) return 2;
 int total = 0;
for(int r = 1; r < N; r++){
total = total + foo1(r);
}
return total;
}


//fool[0] ... fool[N]

int foo1_ans[N] = {-1};
int foo1_ans_solved[N] = {0};

int foo1(int N) {
	if(foo1_ans_solved[N] == 0) {
		// Not yet solved
		if (N <= 3) 
			foo1_ans[N] = 2;
		else {
			int total = 0;
			for(int r = 1; r < N; r++){
				total = total + foo1(r);
			}
			foo1_ans[N] = total;
		}	
		foo1_ans_solved[N] = 1;
	} 
	return foo1_ans[N];

}



/*declare array for answer
declare array for solved

func(N) {
	if(!solved[N]) {
		// go ahead and solve
		// store result in answer[N] 
		// mark solved[N] = 1 
	}
	return answer[N]
}





declare 2D array for answer
declare 2D array for solved

func(N,M) {
	if(!solved[N][M]) {
		// go ahead and solve
		// store result in answer[N][M] 
		// mark solved[N][M] = 1 
	}
	return answer[N][M]
}

*/



