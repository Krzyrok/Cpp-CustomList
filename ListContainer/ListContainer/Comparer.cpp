#include "Comparer.h"

void Comparer::Execute(void)
{
	vector<string> dictionary = FileReader::ReadWordsIntoVector("english.dic.txt");
	random_shuffle(dictionary.begin(), dictionary.end());

	//TestClassicListForDictionary(dictionary);
	TestOneWayListForDictionary(dictionary);
	TestCyclicListForDictionary(dictionary);

}

void Comparer::TestClassicListForDictionary(vector<string> dictionary)
{
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
	TestPushFrontForOneWayListForDictionary(dictionary);
	TestPushBackForOneWayListForDictionary(dictionary);
	TestAssignForOneWayListForDictionary(dictionary);
	TestRemoveForOneWayListForDictionary(dictionary);
	TestReverseForOneWayListForDictionary(dictionary);
}

void Comparer::TestInsertForOneWayListForDictionary(vector<string> dictionary)
{
	List<string> testingList;
	for (int i = 0; i < 1000; i++)
	{
		testingList.push_front(dictionary[i]);
	}
	List<string>::const_iterator it = testingList.end();
	it = testingList.insert(it, dictionary[0]);

	clock_t executionTime = clock();
	for (vector<string>::const_iterator itDic = dictionary.begin(); itDic != dictionary.end(); itDic++)
	{
		testingList.insert(it, *itDic);
	}
	executionTime = clock() - executionTime;

	Printer::PrintExecutionTime("insert whole dictionary into 1k position for OneWay List", executionTime);
}

void Comparer::TestPushFrontForOneWayListForDictionary(vector<string> dictionary)
{
	List<string> testingList;

	clock_t executionTime = clock();
	for (vector<string>::const_iterator it = dictionary.begin(); it != dictionary.end(); it++)
	{
		testingList.push_front(*it);
	}
	executionTime = clock() - executionTime;

	Printer::PrintExecutionTime("push_front whole dictionary for OneWay List", executionTime);
}

void Comparer::TestPushBackForOneWayListForDictionary(vector<string> dictionary)
{
	List<string> testingList;

	clock_t executionTime = clock();
	for (vector<string>::const_iterator it = dictionary.begin(); it != dictionary.end(); it++)
	{
		testingList.push_back(*it);
	}
	executionTime = clock() - executionTime;

	Printer::PrintExecutionTime("push_back whole dictionary for OneWay List", executionTime);

}

void Comparer::TestAssignForOneWayListForDictionary(vector<string> dictionary)
{
	List<string> testingList;

	clock_t executionTime = clock();
	testingList.assign(dictionary.begin(), dictionary.end());
	executionTime = clock() - executionTime;

	Printer::PrintExecutionTime("assign whole dictionary for OneWay List", executionTime);

}

void Comparer::TestRemoveForOneWayListForDictionary(vector<string> dictionary)
{
	List<string> testingList(dictionary.begin(), dictionary.end());

	clock_t executionTime = clock();
	testingList.remove("generous");
	executionTime = clock() - executionTime;

	Printer::PrintExecutionTime("remove 'generous' from OneWay List", executionTime);

}

void Comparer::TestReverseForOneWayListForDictionary(vector<string> dictionary)
{
	List<string> testingList(dictionary.begin(), dictionary.end());

	clock_t executionTime = clock();
	testingList.reverse();
	executionTime = clock() - executionTime;

	Printer::PrintExecutionTime("reverse in OneWay List", executionTime);
}

void Comparer::TestCyclicListForDictionary(vector<string> dictionary)
{
	TestPushFrontForClassicListForDictionary(dictionary);
	TestPushBackForClassicListForDictionary(dictionary);
	TestAssignForClassicListForDictionary(dictionary);
	TestRemoveForClassicListForDictionary(dictionary);
	TestReverseForClassicListForDictionary(dictionary);
}

void Comparer::TestInsertForCyclicListForDictionary(vector<string> dictionary)
{
	CyclicList<string> testingList;
	for (int i = 0; i < 1000; i++)
	{
		testingList.push_front(dictionary[i]);
	}
	CyclicList<string>::const_iterator it = testingList.end();
	it = testingList.insert(it, dictionary[0]);

	clock_t executionTime = clock();
	for (vector<string>::const_iterator itDic = dictionary.begin(); itDic != dictionary.end(); itDic++)
	{
		testingList.insert(it, *itDic);
	}
	executionTime = clock() - executionTime;

	Printer::PrintExecutionTime("insert whole dictionary into 1k position for Cyclic list", executionTime);
}

void Comparer::TestPushFrontForCyclicListForDictionary(vector<string> dictionary)
{
	CyclicList<string> testingList;

	clock_t executionTime = clock();
	for (vector<string>::const_iterator it = dictionary.begin(); it != dictionary.end(); it++)
	{
		testingList.push_front(*it);
	}
	executionTime = clock() - executionTime;

	Printer::PrintExecutionTime("push_front whole dictionary for Cyclic list", executionTime);

}

void Comparer::TestPushBackForCyclicListForDictionary(vector<string> dictionary)
{
	CyclicList<string> testingList;

	clock_t executionTime = clock();
	for (vector<string>::const_iterator it = dictionary.begin(); it != dictionary.end(); it++)
	{
		testingList.push_back(*it);
	}
	executionTime = clock() - executionTime;

	Printer::PrintExecutionTime("push_back whole dictionary for Cyclic list", executionTime);

}

void Comparer::TestAssignForCyclicListForDictionary(vector<string> dictionary)
{
	CyclicList<string> testingList;

	clock_t executionTime = clock();
	testingList.assign(dictionary.begin(), dictionary.end());
	executionTime = clock() - executionTime;

	Printer::PrintExecutionTime("assign whole dictionary for Cyclic list", executionTime);

}

void Comparer::TestRemoveForCyclicListForDictionary(vector<string> dictionary)
{
	CyclicList<string> testingList(dictionary.begin(), dictionary.end());

	clock_t executionTime = clock();
	testingList.remove("generous");
	executionTime = clock() - executionTime;

	Printer::PrintExecutionTime("remove 'generous' from Cyclic list", executionTime);

}

void Comparer::TestReverseForCyclicListForDictionary(vector<string> dictionary)
{
	CyclicList<string> testingList(dictionary.begin(), dictionary.end());

	clock_t executionTime = clock();
	testingList.reverse();
	executionTime = clock() - executionTime;

	Printer::PrintExecutionTime("reverse in Cyclic list", executionTime);
}