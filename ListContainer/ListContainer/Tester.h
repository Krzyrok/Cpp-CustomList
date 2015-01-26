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

	void TestPushBack(List<int>& testingList);
	void TestPushFront(List<int>& testingList);
	void TestSize(List<int>& testingList); 
	void TestListIterator(List<int>& testingList);
};

#endif 
