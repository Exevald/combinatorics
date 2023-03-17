#include <iostream>
#include <string>
#include <optional>
#include <fstream>
#include <vector>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

enum class ErrorCode : int
{
	OK = 0,
	ERROR = 1
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argumants count" << std::endl;
		std::cout << "Usage: BackpackSolution.exe <input file> <output file>" << std::endl;
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	return args;
}

bool IsExistingFiles(std::ifstream& inputFile, std::ofstream& outputFile)
{
	if (!inputFile || !outputFile)
	{
		std::cout << "Failed to open files for reading or writing. Please check filenames." << std::endl;
		return false;
	}
	else
	{
		return true;
	}
}

void GetResultCombination(
	int k, std::vector<int>& comb, int& allWeight, std::vector<int>& weights, int& allCost, std::vector<int>& costs,
	int limitWeight, int limitCost, int& resultCost, int& resultWeight, std::vector<int>& resultCombination)
{
	for (int j = 0; j < k; j++)
	{
		if (comb[j] == 1)
		{
			allWeight += weights[j];
			allCost += costs[j];
		}
	}
	if ((allWeight <= limitWeight) && (allCost >= limitCost))
	{
		if (allCost > resultCost)
		{
			resultCost = allCost;
			resultWeight = allWeight;
			resultCombination = comb;
		}
	}
	else
	{
		allWeight = 0;
		allCost = 0;
	}
}

ErrorCode CheckBackpack(int k, int limitWeight, int limitCost, std::vector<int> comb, std::vector<int> weights, std::vector<int> costs)
{
	int i = 0;
	int allWeight = 0, allCost = 0;
	std::vector<int> resultCombination;
	int resultWeight = 0;
	int resultCost = 0;

	while (comb[k] != 1)
	{
		GetResultCombination(k, comb, allWeight, weights, allCost, costs, limitWeight, limitCost, resultCost, resultWeight, resultCombination);
		i = 0;
		while (comb[i] == 1)
		{
			comb[i] = 0;
			i++;
		}
		comb[i] = 1;
	}
	if ((resultWeight == 0) && (resultCost == 0))
	{
		std::cout << "Wrong input" << std::endl;
		return ErrorCode::ERROR;
	}
	else
	{
		std::cout << "Result combination: ";
		copy(resultCombination.begin(), resultCombination.end() - 1, std::ostream_iterator<size_t>(std::cout, " "));
		std::cout << std::endl;
		std::cout << "Result weight: " << resultWeight << std::endl;
		std::cout << "Result cost: " << resultCost << std::endl;
		return ErrorCode::OK;
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	std::ifstream inputFile;
	std::ofstream outputFile;

	inputFile.open(args->inputFileName);
	outputFile.open(args->outputFileName);

	if (!IsExistingFiles(inputFile, outputFile))
	{
		return 1;
	}

	int n, T, S, weight, cost;
	inputFile >> n >> T >> S;

	std::vector<int> combinations(n + 1);
	std::vector<int> weights;
	std::vector<int> costs;

	for (int i = 0; i < n; i++)
	{
		inputFile >> weight >> cost;
		weights.push_back(weight);
		costs.push_back(cost);
	}

	CheckBackpack(n, T, S, combinations, weights, costs);
	return 0;
}
