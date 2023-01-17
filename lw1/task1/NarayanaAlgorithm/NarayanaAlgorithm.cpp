#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <boost/timer.hpp>

void TimeCount(double duration, std::ofstream &output)
{
	long double dur = duration;
	for (int i = 11; i <= 15; i++)
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

std::vector<size_t> GenerateVector(std::string fileName)
{
	std::vector<size_t> vector;
	std::ifstream inputFile(fileName);
	size_t value;

	if (!inputFile.is_open())
	{
		puts("Не удалось открыть файл для чтения");
		exit(1);
	}
	else
	{
		do
		{
			inputFile >> value;
			vector.push_back(value);
		} while (!inputFile.eof());
	}
	return vector;
}

double GeneratePermutations(std::vector<size_t> vector)
{
	boost::timer t;
	t.restart();

	std::sort(vector.begin(), vector.end());
	do
	{
	} while (std::next_permutation(vector.begin(), vector.end()));
	double duration = t.elapsed();
	return duration;
}

int main()
{
	setlocale(LC_ALL, "rus");
	double duration;
	std::ofstream outputFile("results.txt");
	if (!outputFile.is_open())
	{
		puts("Не удалось открыть файл для чтения");
		exit(1);
	}
	std::vector<size_t> vector = GenerateVector("input.txt");
	duration = GeneratePermutations(vector);
	outputFile << "N = 10: " << duration << " seconds" << std::endl;
	TimeCount(duration, outputFile);
}