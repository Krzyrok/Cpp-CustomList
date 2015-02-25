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
	TestInsertForClassicListForDictionary(dictionary);
	TestPushFrontForClassicListForDictionary(dictionary);
	TestPushBackForClassicListForDictionary(dictionary);
	TestAssignForClassicListForDictionary(dictionary);
	TestRemoveForClassicListForDictionary(dictionary);
	TestReverseForClassicListForDictionary(dictionary);
}

void Comparer::TestInsertForClassicListForDictionary(vector<string> dictionary)
{
	list<string> testingList;
	for (int i = 0; i < 1000; i++)
	{
		testingList.push_front(dictionary[i]);
	}
	list<string>::const_iterator it = testingList.end();
	it = testingList.insert(it, dictionary[0]);

	clock_t executionTime = clock();
	for (vector<string>::const_iterator itDic = dictionary.begin(); itDic != dictionary.end(); itDic++)
	{
		testingList.insert(it, *itDic);
	}
	executionTime = clock() - executionTime;

	Printer::PrintExecutionTime("insert whole dictionary into 1k position for classic list", executionTime);
}

void Comparer::TestPushFrontForClassicListForDictionary(vector<string> dictionary)
{
	list<string> testingList;
	
	clock_t executionTime = clock();
	for (vector<string>::const_iterator it = dictionary.begin(); it != dictionary.end(); it++)
	{
		testingList.push_front(*it);
	}
	executionTime = clock() - executionTime;

	Printer::PrintExecutionTime("push_front whole dictionary for classic list", executionTime);

}

void Comparer::TestPushBackForClassicListForDictionary(vector<string> dictionary)
{
	list<string> testingList;
	
	clock_t executionTime = clock();
	for (vector<string>::const_iterator it = dictionary.begin(); it != dictionary.end(); it++)
	{
		testingList.push_back(*it);
	}
	executionTime = clock() - executionTime;

	Printer::PrintExecutionTime("push_back whole dictionary for classic list", executionTime);

}

void Comparer::TestAssignForClassicListForDictionary(vector<string> dictionary)
{
	list<string> testingList;

	clock_t executionTime = clock();
	testingList.assign(dictionary.begin(), dictionary.end());
	executionTime = clock() - executionTime;

	Printer::PrintExecutionTime("assign whole dictionary for classic list", executionTime);

}

void Comparer::TestRemoveForClassicListForDictionary(vector<string> dictionary)
{
	list<string> testingList(dictionary.begin(), dictionary.end());

	clock_t executionTime = clock();
	testingList.remove("generous");
	executionTime = clock() - executionTime;

	Printer::PrintExecutionTime("remove 'generous' from classic list", executionTime);

}

void Comparer::TestReverseForClassicListForDictionary(vector<string> dictionary)
{
	list<string> testingList(dictionary.begin(), dictionary.end());

	clock_t executionTime = clock();
	testingList.reverse();
	executionTime = clock() - executionTime;

	Printer::PrintExecutionTime("reverse in classic list", executionTime);
}

void Comparer::TestOneWayListForDictionary(vector<string> dictionary)
{

}

void Comparer::TestCyclicListForDictionary(vector<string> dictionary)
{

}