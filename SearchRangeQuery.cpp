// CPP code to determine if the element
// exists for different range queries
#include <bits/stdc++.h>

using namespace std;

// Variable to represent block size.
// This is made global, so compare()
// of sort can use it.
int block;

// Structure to represent a query range
struct Query
{
	int L, R, X;
};

// Function used to sort all queries so
// that all queries of same block are
// arranged together and within a block,
// queries are sorted in increasing order
// of R values.
bool compare(Query x, Query y)
{
	// Different blocks, sort by block.
	if (x.L / block != y.L / block)
		return x.L / block < y.L / block;

	// Same block, sort by R value
	return x.R < y.R;
}

// Determines if the element is present for all
// query ranges. m is number of queries
// n is size of array a[].
void queryResults(int a[], int n, Query q[], int m)
{
	// Find block size
	block = (int)sqrt(n);

	// Sort all queries so that queries of same
	// blocks are arranged together.
	sort(q, q + m, compare);

	// Initialize current L, current R
	int currL = 0, currR = 0;

	// To store the frequencies of
	// elements of the given range
	map<int, int> mp;

	// Traverse through all queries
	for (int i = 0; i < m; i++) {
		
		// L and R values of current range
		int L = q[i].L, R = q[i].R, X = q[i].X;

		// Decrement frequencies of extra elements
		// of previous range. For example if previous
		// range is [0, 3] and current range is [2, 5],
		// then the frequencies of a[0] and a[1] are decremented
		while (currL < L)
		{
			mp[a[currL]]--;
			currL++;
		}

		// Increment frequencies of elements of current Range
		while (currL > L)
		{
			mp[a[currL - 1]]++;
			currL--;
		}
		while (currR <= R)
		{
			mp[a[currR]]++;
			currR++;
		}

		// Decrement frequencies of elements of previous
		// range. For example when previous range is [0, 10]
		// and current range is [3, 8], then frequencies of
		// a[9] and a[10] are decremented
		while (currR > R + 1)
		{
			mp[a[currR - 1]]--;
			currR--;
		}

		// Print if X exists or not
		if (mp[X] != 0)
			cout << X << " exists between [" << L
				<< ", " << R << "] " << endl;
		else
			cout << X << " does not exist between ["
				<< L << ", " << R << "] " << endl;
	}
}

// Driver program
int main()
{
	int a[] = { 1, 1, 5, 4, 5 };
	int n = sizeof(a) / sizeof(a[0]);
	Query q[] = { { 0, 2, 2 }, { 1, 4, 1 }, { 2, 4, 5 } };
	int m = sizeof(q) / sizeof(q[0]);
	queryResults(a, n, q, m);
	return 0;
}
