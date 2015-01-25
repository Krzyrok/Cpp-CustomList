#include "Tester.h"

void Tester::Exeute(void)
{
	list<int> c;
	c.size();
	list<int>::iterator itek = c.begin();


	allocator < int > alloc;
	List<int> myIntList(alloc);

	
	TestPushBack(myIntList);
	TestPushFront(myIntList);
	TestSize(myIntList);
	TestBeginIterator(myIntList);

	system("Pause");
}

void Tester::TestPushBack(List<int>& testingList)
{
	testingList.push_back(5);
	testingList.push_back(12);
	testingList.push_back(7);
}

void Tester::TestPushFront(List<int>& testingList)
{
	testingList.push_front(3);
	testingList.push_front(44);
	testingList.push_front(1);
}

void Tester::TestSize(List<int>& testingList)
{
	if (testingList.size() == 6)
	{
		cout << "size works corretly: " << testingList.size() << endl;
	}
	else
	{
		cout << "size DOESN'T work!!!! RESULT: " << testingList.size() << endl;
	}

}

void Tester::TestBeginIterator(List<int>& testingList)
{
	testingList.begin();
}