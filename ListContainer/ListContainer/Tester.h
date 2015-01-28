#ifndef TESTER_HEADER
#define TESTER_HEADER

#include "List.h"
#include "TestObject.h"

#include <list>

class Tester
{
public: 
	void Exeute(void);

private:
	void TestClassicList(void);

	List<int> PrepareRandonIntList(int size = 4);
	void PrintList(List<int>& printingList);

	void TestConstructors(void);
	void TestPushBack(List<int>& testingList);
	void TestPushFront(List<int>& testingList);
	void TestSize(List<int>& testingList); 
	void TestListIterator(List<int>& testingList);
	void TestBeginEndIterator(List<int>& testingList);
	void TestClear(List<int>& testingList);
	void TestEmpty(List<int>& testingList);
	void TestMaxSize(List<int>& testingList);
};

#endif 
