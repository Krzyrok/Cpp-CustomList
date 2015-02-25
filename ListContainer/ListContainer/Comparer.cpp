#include "Comparer.h"

void Comparer::Execute(void)
{
	vector<string> dictionary = FileReader::ReadWordsIntoVector("english.dic.txt");
	random_shuffle(dictionary.begin(), dictionary.end());

	TestClassicListForDictionary(dictionary);
	TestOneWayListForDictionary(dictionary);
	TestCyclicListForDictionary(dictionary);

}

void Comparer::TestClassicListForDictionary(vector<string> dictionary)
{
	list<string> testingList;
	clock_t executionTime;

	executionTime = clock() - executionTime;
}

void Comparer::TestOneWayListForDictionary(vector<string> dictionary)
{

}

void Comparer::TestCyclicListForDictionary(vector<string> dictionary)
{

}