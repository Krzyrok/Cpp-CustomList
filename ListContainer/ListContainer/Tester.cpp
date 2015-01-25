#include "Tester.h"

void Tester::Exeute(void)
{
	list<int> c;
	c.size();
	c.push_front(3);
	c.push_front(5);
	list<int>::iterator itek = c.begin();
	list<int>::iterator itek2;
	itek2 = itek;
	if (itek == itek2)
		cout << "Rowne\n";
	else
		cout << "NIE rowne\n";

	allocator < int > alloc;
	List<int> myIntList(alloc);


	
	TestPushBack(myIntList);
	TestPushFront(myIntList);
	TestSize(myIntList);
	TestListIterator(myIntList);

	system("Pause");
}

void Tester::TestPushBack(List<int>& testingList)
{
	testingList.push_back(4);
	testingList.push_back(5);
	testingList.push_back(6);
}

void Tester::TestPushFront(List<int>& testingList)
{
	testingList.push_front(3);
	testingList.push_front(2);
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

void Tester::TestListIterator(List<int>& testingList)
{
	List<int>::iterator testingIterator = testingList.begin();

	cout << "1: " << (*testingIterator++) << endl;
	cout << "2: " << (*++testingIterator) << endl;
	cout << "3: " << (*++testingIterator) << endl;
	cout << "4: " << (*++testingIterator) << endl;
}