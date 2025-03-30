#include "CGraphController.h"
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string inputFilePath;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count" << std::endl;
		std::cout << "Usage: branch_and_bound <input file>" << std::endl;
		return std::nullopt;
	}

	return Args{ .inputFilePath = argv[1] };
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}
	try
	{
		auto graphController = CGraphController();
		graphController.LoadFromFile(args->inputFilePath);
		auto [cost, path] = graphController.FindShortestHamiltonianCycle();

		std::cout << "COST: " << cost << std::endl;
		std::copy(path.begin(), path.end(), std::ostream_iterator<int>(std::cout));
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << "\n";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}