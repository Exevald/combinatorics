#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <boost/timer.hpp>
#define N 10

int main()
{
	setlocale(LC_ALL, "rus");

	boost::timer t;
	t.restart();

	std::vector<int> cur;
	std::vector<int> rev;
	std::vector<int> dir;
	cur.resize(N + 2);
	rev.resize(N + 2);
	dir.resize(N + 2);

	for (int i = 1; i <= N; i++)
	{
		cur[i] = i;
		rev[i] = i;
		dir[i] = -1;
	}

	cur[0] = N + 1;
	cur[N + 1] = N + 1;
	dir[0] = 0;

	int m = 0;
	int n = 0;
	while (m != 1)
	{
		m = N;
		while ((cur[rev[m] + dir[m]] > m) && (m > 1))
		{
			dir[m] = -dir[m];
			m = m - 1;
		}
		std::swap(cur[rev[m]], cur[rev[m] + dir[m]]);
		std::swap(rev[cur[rev[m]]], rev[cur[rev[m] + dir[m]]]);
	}
	double duration = t.elapsed();

	std::cout << std::endl << duration << std::endl;
	return 0;
}