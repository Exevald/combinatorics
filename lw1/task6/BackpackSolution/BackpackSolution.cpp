#include <iostream>
#include <fstream>
#include <vector>
#include <set>

const int countOfItems = 3;
const int maxCapacity = 4;

int FindMax(std::vector<int>(&w), std::vector<int>(&c), std::vector<char>(&it))
{
	int backpackCost[maxCapacity + 1][maxCapacity + 1];
	std::set<int>itemsSet;

	for (int i = 0; i <= w.size(); i++)
	{
		for (int j = 0; j <= maxCapacity; j++)
		{
			if ((i == 0) || (j == 0))
			{
				backpackCost[i][j] = 0;
			}
			else
			{
				if (w[i - 1] > j)
				{
					backpackCost[i][j] = backpackCost[i - 1][j];
				}
				else
				{
					int prevMax = backpackCost[i - 1][j];
					int currentCost = c[i - 1] + backpackCost[i - 1][j - w[i - 1]];
					if (currentCost <= prevMax) {
						itemsSet.insert(i - 1);
					}
					backpackCost[i][j] = std::max(prevMax, currentCost);
				}
			}
		}
	}
	for (auto item: itemsSet)
	{
		std::cout << it[item] << " ";
	}
	return backpackCost[countOfItems][maxCapacity];
}

void InitVectors(std::vector<int>(&w), std::vector<int>(&c), std::vector<char>(&it), std::ifstream& input)
{
	char ch;
	int value;
	for (int i = 0; i < countOfItems; i++)
	{
		input >> ch;
		it.push_back(ch);
	}
	for (int i = 0; i < countOfItems; i++)
	{
		input >> value;
		w.push_back(value);
	}
	for (int i = 0; i < countOfItems; i++)
	{
		input >> value;
		c.push_back(value);
	}
}

int main()
{
	setlocale(LC_ALL, "rus");

	std::vector<char>items;
	std::vector<int> weights;
	std::vector<int> costs;
	std::ifstream inputFile("input.txt");
	int result;

	if (!inputFile.is_open())
	{
		puts("Не удалось открыть файл для чтения");
		exit(1);
	}
	InitVectors(weights, costs, items, inputFile);
	for (int i = 0; i < countOfItems; i++)
	{
		std::cout << items[i] << " " << weights[i] << " " << costs[i] << std::endl;
	}
	std::cout << std::endl;
	result = FindMax(weights, costs, items);
	std::cout << std::endl << result;

	return 0;
}
