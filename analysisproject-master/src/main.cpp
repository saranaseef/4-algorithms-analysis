#include <iostream>
#include <string>
#include <iomanip>
#include "../headers/Functions.h"

int main()
{
	std::cout << "Do you want to do a performance comparison or do a plagarism test?";
	std::cout << "1 for performance comparison\n2 for plagarism check\n";
	int options = 0;
	do
	{
		std::cin >> options;
	} while (options != 1 && options != 2);
	if (options == 1)
	{
		freopen("output.txt", "w", stdout);
		for (int i = 500; i <= 3000; i += 500)
		{
			std::cout << "n/m,Boyer Morre,Rapin Karp,Bruteforce,KMP\n";
			for (int j = 2; j < 6; j++)
			{
				std::cout << i << '/' << j << ',';
				TestComparisons(i, j);
			}
			std::cout << std::setfill('-') << std::setw(40) << "" << std::endl;
			std::cout << "\n";
		}
	}
	else
	{
		TestPlagarism();
	}
	return 0;
}
