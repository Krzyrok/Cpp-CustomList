#ifndef TESTER_HEADER
#define TESTER_HEADER

#include "List.h"
#include "TestObject.h"

#include <list>
#include <ctime>

class Tester
{
public: 
	void Exeute(void);

private:
	void TestClassicList(void);

	List<int> PrepareRandonIntList(int size = 4);
	void PrintList(List<int>& printingList);
	void PrepareStandardList(List<int>& printingList);

	void TestConstructors(void);
	void TestPushBack(List<int>& testingList);
	void TestPushFront(List<int>& testingList);
	void TestSize(List<int>& testingList); 
	void TestListIterator(List<int>& testingList);
	void TestBeginEndIterator(List<int>& testingList);
	void TestClear(List<int>& testingList);
	void TestEmpty(List<int>& testingList);
	void TestMaxSize(List<int>& testingList);
	void TestFront(List<int>& testingList);
	void TestBack(List<int>& testingList);
	void TestAssign(List<int>& testingList);
	void TestPopFront(List<int>& testingList);
	void TestPopBack(List<int>& testingList);
	void TestInsert(List<int>& testingList);
	void TestErase(List<int>& testingList);
	void TestSwap(List<int>& testingList);

};

#endif 
