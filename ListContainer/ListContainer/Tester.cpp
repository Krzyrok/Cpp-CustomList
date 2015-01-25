#include "Tester.h"

void Tester::Exeute(void)
{
	list<int> c;
	list<int>::iterator itek = c.begin();



	allocator < int > alloc;
	List<int> myIntList(alloc);
	
	TestPushBack(myIntList);
	TestBeginIterator(myIntList);

	system("Pause");
}

void Tester::TestPushBack(List<int>& testingList)
{
	testingList.push_back(5);
	testingList.push_back(12);
	testingList.push_back(7);
}

void Tester::TestBeginIterator(List<int>& testingList)
{
	testingList.begin();
}