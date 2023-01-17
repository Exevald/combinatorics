#include <iostream>
#include <vector>
#define count 10

int RandomNumber(int from, int to) {
	if (to == from)
	{
		return to;
	}
	if (to < from)
	{
		return RandomNumber(to, from);
	}
	return from + rand() % (to - from + 1);
}

int main()
{
	std::vector<int> vector;
	int index;
	vector.resize(count);
	for (int i = 0; i < count; i++)
	{
		vector[i] = i + 1;
	};
	for (int i = 0; i < count; i++)
	{
		index = RandomNumber(1, count);
		std::swap(vector[i], vector[index - 1]);
	}
	for (int i = 0; i < count; i++)
	{
		std::cout << vector[i] << " ";
	};
	return 0;
}