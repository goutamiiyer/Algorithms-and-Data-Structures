#include<stdio.h>

int fact_2halves(int st, int ed)
{

    int p,ans;

    //printf("(%d,%d),", st,ed);

    printf("    (st,ed) = (%d,%d),", st,ed);

    if (st==ed) return st;

    p = (st+ed)/2;

    ans = fact_2halves(st, p)*fact_2halves(p+1,ed);
    return ans;

}

int main()
{
	int res;
	res = fact_2halves(1, 7);
	printf("fact_2halves(4, 7): %d", res);

}