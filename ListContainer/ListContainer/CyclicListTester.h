#ifndef CYCLIC_LIST_TESTER_HEADER
#define CYCLIC_LIST_TESTER_HEADER

#include "CyclicList.h"
#include "TestObject.h"

#include <list>
#include <ctime>

class CyclicListTester
{
public:
	void Exeute(void);

private:
	CyclicList<int> PrepareRandonIntList(int size);
	void PrintList(CyclicList<int>& printingList);
	CyclicList<int> PrepareTestList(void);

	void TestConstructors(void);
	void TestPushBack(void);
	void TestPushFront(void);
	void TestSize(void);
	void TestListIterator(void);
	void TestBeginEndIterator(void);
	void TestClear(void);
	void TestEmpty(void);
	void TestMaxSize(void);
	void TestFront(void);
	void TestBack(void);
	void TestAssign(void);
	void TestPopFront(void);
	void TestPopBack(void);
	void TestInsert(void);
	void TestErase(void);
	void TestSwap(void);
	void TestResize(void);
	void TestSplice(void);
	void TestRemoveAndRemoveIf(void);
	void TestUnique(void);
	void TestReverse(void);
	void TestSort(void);
	void TestMerge(void);
};

#endif 
