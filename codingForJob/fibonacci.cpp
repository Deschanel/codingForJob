#include "pch.h"
#include "fibonacci.h"

fibonacci::fibonacci()
{
}



fibonacci::~fibonacci()
{
}

long int fibonacci::getFib(int n)   //这个里面不包括0，是从1开始的：1 1 2 3 5 .....
{
	fibVector.clear();
	fibVector.resize(n, 1);
	int next = 1, previous = 1;
	int oldn = n;
	if (n == 1 || n == 2)
	{
		return fibVector[n-1];
	}
	int index = 2;
	while (n > 2)
	{
		next = next + previous;
		previous = next - previous;
		fibVector[index++] = next;
		n--;
	}
	return fibVector[oldn-1];
}
