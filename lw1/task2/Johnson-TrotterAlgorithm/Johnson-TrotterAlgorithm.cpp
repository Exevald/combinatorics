#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <boost/timer.hpp>
#define count 10

void TimeCount(int initialCount, double duration, std::ofstream& output)
{
	long double dur = duration;
	for (int i = initialCount + 1; i <= 15; i++)
	{
		dur *= i;
	}
	dur /= 3600;
	output << "N = 15: " << dur << " hours" << std::endl;

	for (int i = 16; i <= 20; i++)
	{
		dur *= i;
	}
	dur /= 24;
	output << "N = 20: " << dur << " days" << std::endl;

	for (int i = 21; i <= 50; i++)
	{
		dur *= i;
	}
	dur /= 365;
	output << "N = 50: " << dur << " years" << std::endl;

	for (int i = 51; i <= 100; i++)
	{
		dur *= i;
	}
	output << "N = 100: " << dur << " years" << std::endl;
}

double GeneratePermutations(std::vector<int> cur, std::vector<int> rev, std::vector<int> dir)
{
	int m = 0;
	int n = 0;
	boost::timer t;
	t.restart();

	cur.resize(count + 2);
	rev.resize(count + 2);
	dir.resize(count + 2);

	for (int i = 1; i <= count; i++)
	{
		cur[i] = i;
		rev[i] = i;
		dir[i] = -1;
	}
	cur[0] = count + 1;
	cur[count + 1] = count + 1;
	dir[0] = 0;
	while (m != 1)
	{
		m = count;
		while ((cur[rev[m] + dir[m]] > m) && (m > 1))
		{
			dir[m] = -dir[m];
			m = m - 1;
		}
		std::swap(cur[rev[m]], cur[rev[m] + dir[m]]);
		std::swap(rev[cur[rev[m]]], rev[cur[rev[m] + dir[m]]]);
	}
	double duration = t.elapsed();
	return duration;
}

int main()
{
	setlocale(LC_ALL, "rus");
	double duration;
	std::vector<int> cur;
	std::vector<int> rev;
	std::vector<int> dir;
	std::ofstream outputFile("results.txt");

	if (!outputFile.is_open())
	{
		puts("Не удалось открыть файл для записи");
		exit(1);
	}
	duration = GeneratePermutations(cur, rev, dir);
	outputFile << "N = " << count << ": " << duration << " seconds" << std::endl;
	TimeCount(count, duration, outputFile);
	return 0;
}