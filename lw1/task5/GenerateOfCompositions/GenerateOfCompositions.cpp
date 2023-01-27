#include <iostream>
#include <vector>
#include <algorithm>

size_t FindMin(std::vector<size_t> v)
{
	for (size_t i = 1; i < v.size(); i++)
	{
		if (v[0] > v[i] && i != v.size() - 1)
		{
			return i;
		}
	}
	return 0;
}

void GeneratePermutations(std::vector<size_t> v)
{
	sort(v.begin(), v.end());
	do
	{
		copy(v.begin(), v.end(), std::ostream_iterator<size_t>(std::cout, " "));
		std::cout << std::endl;
	} while (next_permutation(v.begin(), v.end()));
}

int main()
{
	std::vector<size_t> original, composed;
	size_t n;
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
		size_t i = FindMin(original);
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