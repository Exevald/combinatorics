#include <iostream>
#include <vector>
#include <algorithm>

std::vector<size_t> original, composed;
size_t n;


size_t FindMin()
{
	for (size_t i = 1; i < original.size(); i++)
	{
		if (original[0] > original[i] && i != original.size() - 1)
		{
			return i;
		}
	}
	return 0;
}

void GeneratePermutations(std::vector<size_t> original)
{
	sort(original.begin(), original.end());
	do
	{
		copy(original.begin(), original.end(), std::ostream_iterator<size_t>(std::cout, " "));
		std::cout << std::endl;
	} while (next_permutation(original.begin(), original.end()));
}

size_t main()
{
	setlocale(LC_ALL, "rus");
	std::cout << "¬ведите число, дл€ вывода его композиций: ";
	std::cin >> n;

	for (size_t i = 0; i < n; i++)
	{
		original.push_back(1);
	}

	copy(original.begin(), original.end(), std::ostream_iterator<size_t>(std::cout, " "));
	std::cout << std::endl;

	while (original[0] != n)
	{
		size_t i = FindMin();
		original[i] += 1;
		original[original.size() - 1] -= 1;

		if (original[original.size() - 1] == 0)
		{
			original.pop_back();
		}

		composed = original;
		GeneratePermutations(composed);
	}

	return 0;
}