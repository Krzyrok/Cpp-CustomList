#include "Tester.h"

void Tester::Exeute(void)
{
	//TestClassicList();

	allocator <int> alloc;
	List<int> myIntList(alloc);

	TestConstructors();
	TestPushBack(myIntList);
	TestPushFront(myIntList);
	TestSize(myIntList);
	//TestListIterator(myIntList);
	TestClear(myIntList);
	TestBeginEndIterator(myIntList);
	TestEmpty(myIntList);
	TestMaxSize(myIntList);
	TestFront(myIntList);
	TestBack(myIntList);
}

List<int> Tester::PrepareRandonIntList(int size)
{
	List<int> result;
	for (int i = 0; i < size; i++)
	{
		int randomNumber = rand() % 100;
		result.push_front(randomNumber);
	}

	return result;
}

void Tester::PrintList(List<int>& printingList)
{
	int i = 1;
	for (List<int>::iterator it = printingList.begin(); it != printingList.end(); it++, i++)
	{
		cout << i << ": " << *it << endl;
	}
}

void Tester::TestClassicList(void)
{
	list<int> c;
	c.size();
	c.push_front(3);
	c.push_front(5);
	list<int>::iterator itek = c.begin();
	list<int>::iterator itek2 = c.begin();
	if (itek == itek2)
		cout << "Rowne\n";
	else
		cout << "NIE rowne\n";

	list<int>::const_iterator itConst = c.begin();
	itConst = c.end();
	itConst = itek;

	c.max_size();

	// code below should not compile

	//itek = itConst;
	//*itConst = 77;

}

void Tester::TestConstructors(void)
{
	List<int> emptyList;
	cout << "size (0): " << emptyList.size() << endl << endl;

	allocator<int> alloc;
	List<int, allocator<int>> emptyList2(alloc);
	cout << "size (0): " << emptyList2.size() << endl << endl;

	List<int> listWithTheSameValues(5, 1410);
	cout << "size (5, 1410): " << listWithTheSameValues.size() << endl;
	PrintList(listWithTheSameValues);
	cout << endl;

	List<int> randomList = PrepareRandonIntList();
	cout << "Size: " << randomList.size() << ". Random list: \n";
	PrintList(randomList);
	List<int> iteratorCopiedList(randomList.begin(), randomList.end());
	cout << "Size: " << iteratorCopiedList.size() << ". Copied (by iterators) list: \n";
	PrintList(iteratorCopiedList);
	cout << endl;

	list<int> originalList;
	originalList.push_front(5);
	originalList.push_front(966);
	List<int> iteratorCopiedList2(originalList.begin(), originalList.end());
	cout << "Should be 966 and 5: " << endl;
	PrintList(iteratorCopiedList2);
	cout << endl;

	List<int> listToCopy;
	listToCopy.push_front(1772);
	listToCopy.push_front(13);
	List<int> copiedList(listToCopy);
	cout << "Should be 13 and 1772: " << endl;
	PrintList(copiedList);
	cout << endl;

	listToCopy.clear();
	cout << "Should be nothing:" << endl;
	PrintList(listToCopy);
	cout << "Should be 13 and 1772: " << endl;
	PrintList(copiedList);

	cout << "\n----------------\n\n";
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
		cout << "size works corretly: " << testingList.size() << endl << endl;
	}
	else
	{
		cout << "size DOESN'T work!!!! RESULT: " << testingList.size() << endl << endl;
	}

	cout << "----------------\n\n";
}

void Tester::TestListIterator(List<int>& testingList)
{
	List<int>::iterator testingIterator = testingList.begin();

	cout << "1: " << (*testingIterator++) << endl;
	cout << "3: " << (*++testingIterator) << endl;
	cout << "4: " << (*++testingIterator) << endl;
	cout << "5: " << (*++testingIterator) << endl << endl;
	
	testingIterator = testingList.begin();
	List<int>::iterator testingIterator2 = testingList.begin();
	cout << "checking difference (should be false): " << (testingIterator != testingIterator2) << endl;
	cout << "checking equality (should be true): " << (testingIterator == testingIterator2) << endl << endl;

	testingIterator++;
	cout << "checking equality (should be false): " << (testingIterator == testingIterator2) << endl;
	testingIterator2++;
	cout << "checking equality (should be true): " << (testingIterator == testingIterator2) << endl << endl;

	testingIterator2++;
	cout << "checking equality (should be false): " << (testingIterator == testingIterator2) << endl;
	testingIterator = testingIterator2;
	cout << "checking equality (should be true): " << (testingIterator == testingIterator2) << endl << endl;

	testingIterator = testingList.begin();
	List<int>::iterator iterator3(testingIterator);
	cout << "checking difference (should be false): " << (testingIterator != iterator3) << endl;
	cout << "checking equality (should be true): " << (testingIterator == iterator3) << endl;
	cout << "1: " << *iterator3 << endl << endl;

	testingIterator = testingList.begin();
	*testingIterator = 77;
	cout << "77: " << *testingIterator++ << endl;
	cout << "77: " << *iterator3 << endl;
	cout << "2: " << *testingIterator << endl << endl;


	List<TestObject> listTestObject;
	listTestObject.push_front(TestObject());
	listTestObject.push_front(TestObject());
	List<TestObject>::iterator iteratorForTestObject = listTestObject.begin();
	iteratorForTestObject->PrintSomething();


	// testing const_iterator
	List<int>::const_iterator constTestingIterator = testingList.begin();
	testingIterator = testingList.begin();
	cout << "77: " << (*constTestingIterator++) << endl;
	cout << "3: " << (*++constTestingIterator) << endl;
	constTestingIterator = testingList.begin();
	cout << "checking difference (should be false): " << (constTestingIterator != testingIterator) << endl;
	cout << "checking equality (should be true): " << (constTestingIterator == testingIterator) << endl << endl;
	
	constTestingIterator++;
	constTestingIterator++;
	constTestingIterator = testingIterator;
	cout << "77: " << (*constTestingIterator) << endl << endl;


	List<int>::const_iterator constTestingIterator2 = testingList.begin();
	cout << "checking difference (should be false): " << (constTestingIterator != constTestingIterator2) << endl;
	cout << "checking equality (should be true): " << (constTestingIterator == constTestingIterator2) << endl << endl;
	
	
	shared_ptr<ListElement<int, allocator<int>>> pointer(new ListElement<int, allocator<int>>(777, allocator<int>()));
	List<int>::const_iterator constTestingIterator3(pointer);
	cout << "777: " << (*constTestingIterator3) << endl << endl;


	cout << "----------------\n\n";



	// code below should not compile

	//testingIterator = constTestingIterator; // should be error
	//constTestingIterator = testingList.begin();
	//*constTestingIterator = 124;  // should be error
	//cout << "should not compile for const_interator -> 124: " << (*constTestingIterator) << endl;
}

void Tester::TestBeginEndIterator(List<int>& testingList)
{
	TestPushBack(testingList);
	TestPushFront(testingList);
	PrintList(testingList);
	cout << "\n----------------\n\n";
}

void Tester::TestClear(List<int>& testingList)
{
	testingList.clear();
	cout << "Size after clear(): " << testingList.size() << endl ;
	cout << "\n----------------\n\n";
}

void Tester::TestEmpty(List<int>& testingList)
{
	cout << "Size before clear: " << testingList.size() << endl;
	cout << "Is empty (false): " << testingList.empty() << endl;
	testingList.clear();
	cout << "Size after clear: " << testingList.size() << endl;
	cout << "Is empty (true): " << testingList.empty() << endl;

	List<int> newList;
	cout << "Is empty (true): " << newList.empty() << endl;

	TestPushBack(testingList);
	TestPushFront(testingList);
	cout << "\n----------------\n\n";
}

void Tester::TestMaxSize(List<int>& testingList)
{
	cout << "Max size for list: " << testingList.max_size() << endl;
	cout << "Max size for classic list: " << List<int>().max_size() << endl;
	cout << "\n----------------\n\n";
}

void Tester::TestFront(List<int>& testingList)
{
	int& variable = testingList.front();
	const List<int> constList(testingList);
	const int& constVariable = constList.front();

	cout << "Front (1): " << variable << endl;
	cout << "Const front (1): " << constVariable << endl;

	cout << "\n----------------\n\n";
}

void Tester::TestBack(List<int>& testingList)
{
	int& variable = testingList.back();
	const List<int> constList(testingList);
	const int& constVariable = constList.back();

	cout << "Back (6): " << variable << endl;
	cout << "Const back (6): " << constVariable << endl;

	testingList.push_back(7);
	cout << "Back (7): " << testingList.back() << endl;

	cout << "\n----------------\n\n";
}
