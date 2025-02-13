#include <iostream>
#include <string>
#include <optional>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

struct Item
{
	int weight;
	int cost;
};

struct BackpackResult
{
	std::vector<size_t> combination;
	int totalWeight;
	int totalCost;
};

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

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid arguments count" << std::endl;
		std::cout << "Usage: BackpackSolution.exe <input file> <output file>" << std::endl;
		return std::nullopt;
	}
	return Args{ argv[1], argv[2] };
}

void OpenFiles(std::ifstream& inputFile, std::ofstream& outputFile, const std::string& inputFileName, const std::string& outputFileName)
{
	inputFile.open(inputFileName);
	outputFile.open(outputFileName);

	if (!inputFile || !outputFile)
	{
		throw std::runtime_error("Failed to open files for reading or writing");
	}
};

bool NextOccurrence(std::vector<size_t>& occurrence)
{
	size_t n = occurrence.size();
	for (size_t i = n; i-- > 0;)
	{
		if (occurrence[i] == 0)
		{
			occurrence[i] = 1;
			std::fill(occurrence.begin() + i + 1, occurrence.end(), 0);
			return true;
		}
	}
	return false;
}

BackpackResult FindBestCombination(const std::vector<Item>& items, int maxWeight, int minCost)
{
	int n = items.size();
	std::vector<size_t> combination(n, 0);
	BackpackResult bestResult{ {}, 0, 0 };

	do
	{
		int currentWeight = 0;
		int currentCost = 0;
		for (size_t i = 0; i < n; ++i)
		{
			currentWeight += combination[i] * items[i].weight;
			currentCost += combination[i] * items[i].cost;
		}

		if (currentWeight <= maxWeight && currentCost >= minCost && currentCost > bestResult.totalCost)
		{
			bestResult = { combination, currentWeight, currentCost };
		}
	} while (NextOccurrence(combination));

	return bestResult;
}

BackpackResult SolveBackpackProblem(std::ifstream& inputFile, std::ofstream& outputFile)
{
	int numItems, maxWeight, minCost;
	inputFile >> numItems >> maxWeight >> minCost;

	std::vector<Item> items(numItems);
	for (int i = 0; i < numItems; ++i)
	{
		inputFile >> items[i].weight >> items[i].cost;
	}

	BackpackResult result = FindBestCombination(items, maxWeight, minCost);

	if (result.totalCost == 0 && result.totalWeight == 0)
	{
		throw std::runtime_error("No valid combination found");
	}

	outputFile << "Best combination: ";
	for (size_t i = 0; i < result.combination.size(); ++i)
	{
		if (result.combination[i])
		{
			outputFile << i + 1 << " ";
		}
	}

	outputFile << std::endl;
	outputFile << "Total weight: " << result.totalWeight << std::endl;
	outputFile << "Total cost: " << result.totalCost << std::endl;

	return result;
}

int main(int argc, char* argv[])
{
	auto start = std::chrono::steady_clock::now();

	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}

	std::ifstream inputFile;
	std::ofstream outputFile;

	try
	{
		OpenFiles(inputFile, outputFile, args->inputFileName, args->outputFileName);
		auto result = SolveBackpackProblem(inputFile, outputFile);

		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed = end - start;
		outputFile << std::endl << "Time: " << elapsed.count() << std::endl;

		TimeCount(result.combination.size(), elapsed.count(), outputFile);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}