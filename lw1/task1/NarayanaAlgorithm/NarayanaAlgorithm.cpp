#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <boost/timer.hpp>

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

std::vector<size_t> GenerateVector(int& countOfItems, std::ifstream& input)
{
	std::vector<size_t> vector;

	size_t value;

	input >> countOfItems;
	do
	{
		input >> value;
		vector.push_back(value);
	} while (!input.eof());
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
	int countOfItems = 0;
	std::ifstream inputFile("input.txt");
	std::ofstream outputFile("results.txt");

	if (!inputFile.is_open())
	{
		puts("Не удалось открыть файл для чтения");
		exit(1);
	}
	if (!outputFile.is_open())
	{
		puts("Не удалось открыть файл для записи");
		exit(1);
	}
	std::vector<size_t> vector = GenerateVector(countOfItems, inputFile);
	duration = GeneratePermutations(vector);
	outputFile << "N = " << countOfItems << ": " << duration << " seconds" << std::endl;
	TimeCount(countOfItems, duration, outputFile);
}