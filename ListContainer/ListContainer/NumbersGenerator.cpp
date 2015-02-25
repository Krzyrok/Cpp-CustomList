#include "NumbersGenerator.h"

vector<int> NumbersGenerator::GenerateNumbersVector(int howMany)
{
	vector<int> result;
	for (int i = 0; i < howMany; i++)
	{
		int randomNumber = rand() % 1000;
		result.push_back(randomNumber);
	}

	return result;
}