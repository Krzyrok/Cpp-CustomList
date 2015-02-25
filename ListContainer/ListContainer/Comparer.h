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
	void TestOneWayListForDictionary(vector<string> dictionary);
	void TestCyclicListForDictionary(vector<string> dictionary);
};

#endif
