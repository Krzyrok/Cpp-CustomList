#ifndef LIST_TESTER_HEADER
#define LIST_TESTER_HEADER

#include "List.h"
#include "TestObject.h"
#include "TestObjectMoreComplex.h"

#include <list>
#include <ctime>

class ListTester
{
public: 
	void Exeute(void);

private:
	void TestClassicList(void);

	List<int> PrepareRandonIntList(int size);
	void PrintList(List<int>& printingList);
	List<int> PrepareTestList(void);

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
	void TestEmplaceFront(void);
	void TestEmplaceBack(void);
	void TestEmplace(void);
};

#endif 
