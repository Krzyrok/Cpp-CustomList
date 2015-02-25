#ifndef COMPARER_HEADER
#define COMPARER_HEADER

#include "CyclicList.h"
#include "FileReader.h"
#include "Printer.h"

#include <algorithm>
#include <list>
#include <ctime>

class Comparer
{
public:
	void Execute(void);

private:
	void TestClassicListForDictionary(vector<string> dictionary);
	void TestInsertForClassicListForDictionary(vector<string> dictionary);
	void TestPushFrontForClassicListForDictionary(vector<string> dictionary);
	void TestPushBackForClassicListForDictionary(vector<string> dictionary);
	void TestAssignForClassicListForDictionary(vector<string> dictionary);
	void TestRemoveForClassicListForDictionary(vector<string> dictionary);
	void TestReverseForClassicListForDictionary(vector<string> dictionary);

	void TestOneWayListForDictionary(vector<string> dictionary);
	void TestInsertForOneWayListForDictionary(vector<string> dictionary);
	void TestPushFrontForOneWayListForDictionary(vector<string> dictionary);
	void TestPushBackForOneWayListForDictionary(vector<string> dictionary);
	void TestAssignForOneWayListForDictionary(vector<string> dictionary);
	void TestRemoveForOneWayListForDictionary(vector<string> dictionary);
	void TestReverseForOneWayListForDictionary(vector<string> dictionary);

	void TestCyclicListForDictionary(vector<string> dictionary);
	void TestInsertForCyclicListForDictionary(vector<string> dictionary);
	void TestPushFrontForCyclicListForDictionary(vector<string> dictionary);
	void TestPushBackForCyclicListForDictionary(vector<string> dictionary);
	void TestAssignForCyclicListForDictionary(vector<string> dictionary);
	void TestRemoveForCyclicListForDictionary(vector<string> dictionary);
	void TestReverseForCyclicListForDictionary(vector<string> dictionary);
};

#endif
