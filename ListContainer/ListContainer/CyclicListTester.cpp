#include "CyclicListTester.h"

void CyclicListTester::Exeute(void)
{
	srand((unsigned int)time(NULL));

	TestConstructors();
	TestPushBack();
	TestPushFront();
	TestSize();
	TestListIterator();
	TestClear();
	TestBeginEndIterator();
	TestEmpty();
	TestMaxSize();
	TestFront();
	TestBack();
	TestAssign();
	TestPopFront();
	TestPopBack();
	TestInsert();
	TestErase();
	TestSwap();
	TestResize();
	TestSplice();
	//return;
	TestRemoveAndRemoveIf();
	TestUnique();
	TestReverse();
	TestSort();

	TestMerge();
	TestEmplaceFront();
	TestEmplaceBack();
	TestEmplace();
}

CyclicList<int> CyclicListTester::PrepareRandonIntList(int size)
{
	CyclicList<int> result;
	for (int i = 0; i < size; i++)
	{
		int randomNumber = rand() % 100;
		result.push_front(randomNumber);
	}

	return result;
}

void CyclicListTester::PrintList(CyclicList<int>& printingList)
{
	int i = 1;
	for (CyclicList<int>::iterator it = printingList.begin(); it != printingList.end(); it++, i++)
	{
		cout << i << ": " << *it << endl;
	}
}

CyclicList<int> CyclicListTester::PrepareTestList(void)
{
	CyclicList<int> newList;
	newList.push_front(6);
	newList.push_front(5);
	newList.push_front(4);
	newList.push_front(3);
	newList.push_front(2);
	newList.push_front(1);

	return newList;
}

void CyclicListTester::TestConstructors(void)
{
	CyclicList<int> emptyList;
	cout << "Size (0): " << emptyList.size() << endl << endl;

	allocator<int> alloc;
	CyclicList<int, allocator<int>> emptyList2(alloc);
	cout << "Size (0): " << emptyList2.size() << endl << endl;

	CyclicList<int> listWithTheSameValues(5, 1410);
	cout << "CyclicList: 5 x 1410; size (5): " << listWithTheSameValues.size() << endl;
	PrintList(listWithTheSameValues);
	cout << endl;

	CyclicList<int> randomList;
	randomList = PrepareRandonIntList(4);
	cout << "Size (4): " << randomList.size() << endl;
	PrintList(randomList);
	CyclicList<int> copiedListUsingIterators(randomList.begin(), randomList.end());
	cout << "Should be the same values as above; size (4): " << copiedListUsingIterators.size() << endl;
	PrintList(copiedListUsingIterators);
	cout << endl;

	list<int> originalList;
	originalList.push_front(1085);
	originalList.push_front(5);
	originalList.push_front(966);
	CyclicList<int> copiedListUsingIterators2(originalList.begin(), ++++originalList.begin());
	cout << "CyclicList: 966, 5; size (2): " << copiedListUsingIterators2.size() << endl;
	PrintList(copiedListUsingIterators2);
	cout << endl;

	CyclicList<int> listToCopy;
	listToCopy.push_front(1772);
	listToCopy.push_front(13);
	CyclicList<int> copiedList(listToCopy);
	CyclicList<int>::iterator iteratorForList = listToCopy.begin();
	*iteratorForList = 4;
	cout << "CyclicList: 13, 1772; size (2): " << copiedList.size() << endl;
	PrintList(copiedList);
	cout << endl;

	listToCopy.clear();
	cout << "Should be nothing; size (0):" << listToCopy.size() << endl;
	PrintList(listToCopy);
	cout << "CyclicList: 13, 1772; size (2): " << copiedList.size() << endl;
	PrintList(copiedList);
	cout << endl;

	listToCopy.clear();
	copiedList.clear();
	listToCopy.push_front(1772);
	listToCopy.push_front(13);
	copiedList = listToCopy;
	iteratorForList = listToCopy.begin();
	*iteratorForList = 4;
	cout << "List: 13, 1772; size (2): " << copiedList.size() << endl;
	PrintList(copiedList);
	cout << endl;

	listToCopy.clear();
	cout << "Should be nothing; size (0):" << listToCopy.size() << endl;
	PrintList(listToCopy);
	cout << "List: 13, 1772; size (2): " << copiedList.size() << endl;
	PrintList(copiedList);
	cout << endl;

	initializer_list<int> li = { 1, 2, 7 };
	copiedList = li;
	cout << "List: 1, 2, 7; size (3): " << copiedList.size() << endl;
	PrintList(copiedList);
	cout << endl;

	CyclicList<int> copiedList2(li);
	cout << "List: 1, 2, 7; size (3): " << copiedList.size() << endl;
	PrintList(copiedList);
	cout << endl;

	CyclicList<int> testingList = PrepareTestList();
	CyclicList<int>::iterator testingIterator = testingList.begin();
	++++++++++testingIterator;
	testingIterator = testingList.begin(testingIterator);
	cout << "Value pointed by iterator (6): " << *testingIterator << endl;
	cout << "CyclicList: 6, 1-5; size (6): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	testingList.clear();
	testingList.push_front(5);
	CyclicList<int>::const_iterator testingIterator2 = testingList.begin();
	++testingIterator;
	testingIterator2 = testingList.begin(testingIterator2);
	cout << "Value pointed by const_iterator (5): " << *testingIterator2 << endl;
	cout << "CyclicList: 5; size (1): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	testingList = PrepareTestList();
	testingIterator = testingList.begin();
	++++testingIterator;
	testingIterator = testingList.end(testingIterator);
	cout << "Value pointed by iterator (3): " << *testingIterator << endl;
	cout << "CyclicList: 3-6, 1-2; size (6): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	testingList = PrepareTestList();
	testingIterator2 = testingList.begin();
	++testingIterator2;
	testingIterator2 = testingList.end(testingIterator2);
	cout << "Value pointed by const_iterator (2): " << *testingIterator2 << endl;
	cout << "CyclicList: 2-6, 1; size (6): " << testingList.size() << endl;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void CyclicListTester::TestPushBack(void)
{
	CyclicList<int> testingList;
	testingList.push_back(4);
	testingList.push_back(5);
	testingList.push_back(6);
	cout << "CyclicList: 4-6; size (3): " << testingList.size() << endl;
	PrintList(testingList);
	cout << "\n----------------\n\n";
}

void CyclicListTester::TestPushFront(void)
{
	CyclicList<int> testingList;
	testingList.push_front(3);
	testingList.push_front(2);
	testingList.push_front(1);
	cout << "CyclicList: 1-3; size (3): " << testingList.size() << endl;
	PrintList(testingList);
	cout << "\n----------------\n\n";
}

void CyclicListTester::TestSize(void)
{
	CyclicList<int>& testingList = PrepareTestList();
	if (testingList.size() == 6)
	{
		cout << "Size works corretly, (6): " << testingList.size() << endl << endl;
	}
	else
	{
		cout << "Size DOESN'T work!!!! RESULT (should be 6): " << testingList.size() << endl << endl;
	}

	cout << "----------------\n\n";
}

void CyclicListTester::TestListIterator(void)
{
	CyclicList<int>& testingList = PrepareTestList();

	CyclicList<int>::iterator testingIterator = testingList.begin();

	cout << "1: " << (*testingIterator++) << endl;
	cout << "3: " << (*++testingIterator) << endl;
	cout << "4: " << (*++testingIterator) << endl;
	cout << "5: " << (*++testingIterator) << endl << endl;

	testingIterator = testingList.begin();
	CyclicList<int>::iterator testingIterator2 = testingList.begin();
	cout << "Checking iterators difference (false, 0): " << (testingIterator != testingIterator2) << endl;
	cout << "Checking iterators equality (true, 1): " << (testingIterator == testingIterator2) << endl << endl;

	testingIterator++;
	cout << "Checking iterators equality (false, 0): " << (testingIterator == testingIterator2) << endl;
	testingIterator2++;
	cout << "Checking iterators equality (true, 1): " << (testingIterator == testingIterator2) << endl << endl;

	testingIterator2++;
	cout << "Checking iterators equality (false, 0): " << (testingIterator == testingIterator2) << endl;
	testingIterator = testingIterator2;
	cout << "Checking iterators equality (true, 1): " << (testingIterator == testingIterator2) << endl << endl;

	testingIterator = testingList.begin();
	CyclicList<int>::iterator iterator3(testingIterator);
	cout << "Checking iterators difference (false, 0): " << (testingIterator != iterator3) << endl;
	cout << "Checking iterators equality (true, 1): " << (testingIterator == iterator3) << endl;
	cout << "1: " << *iterator3 << endl << endl;

	testingIterator = testingList.begin();
	*testingIterator = 77;
	cout << "77: " << *testingIterator++ << endl;
	cout << "77: " << *iterator3 << endl;
	cout << "2: " << *testingIterator << endl << endl;


	CyclicList<TestObject> listTestObject;
	listTestObject.push_front(TestObject());
	listTestObject.push_front(TestObject());
	CyclicList<TestObject>::iterator iteratorForTestObject = listTestObject.begin();
	cout << "Test message: \n";
	iteratorForTestObject->PrintSomething();


	// testing const_iterator
	CyclicList<int>::const_iterator constTestingIterator = testingList.begin();
	testingIterator = testingList.begin();
	cout << "77: " << (*constTestingIterator++) << endl;
	cout << "3: " << (*++constTestingIterator) << endl;
	constTestingIterator = testingList.begin();
	cout << "Checking const iterators difference (false, 0): " << (constTestingIterator != testingIterator) << endl;
	cout << "Checking const iterators equality (true, 1): " << (constTestingIterator == testingIterator) << endl << endl;

	constTestingIterator++;
	constTestingIterator++;
	constTestingIterator = testingIterator;
	cout << "77: " << (*constTestingIterator) << endl << endl;


	CyclicList<int>::const_iterator constTestingIterator2 = testingList.begin();
	cout << "Checking const iterators difference (false, 0): " << (constTestingIterator != constTestingIterator2) << endl;
	cout << "Checking const iterators equality (true, 1): " << (constTestingIterator == constTestingIterator2) << endl << endl;


	shared_ptr<ListElement<int, allocator<int>>> pointer(new ListElement<int, allocator<int>>(allocator<int>(), 777));
	CyclicList<int>::const_iterator constTestingIterator3(pointer);
	cout << "777: " << (*constTestingIterator3) << endl << endl;


	cout << "----------------\n\n";



	// code below should not compile

	//testingIterator = constTestingIterator; // should be error
	//constTestingIterator = testingList.begin();
	//*constTestingIterator = 124;  // should be error
	//cout << "should not compile for const_interator -> 124: " << (*constTestingIterator) << endl;
}

void CyclicListTester::TestBeginEndIterator(void)
{
	CyclicList<int>& testingList = PrepareTestList();
	PrintList(testingList);
	cout << "\n----------------\n\n";
}

void CyclicListTester::TestClear(void)
{
	CyclicList<int>& testingList = PrepareTestList();
	cout << "CyclicList before clear: 1-6; size (6): " << testingList.size() << endl;
	PrintList(testingList);

	testingList.clear();
	cout << "CyclicList after clear: no elements; size (0): " << testingList.size() << endl;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void CyclicListTester::TestEmpty(void)
{
	CyclicList<int>& testingList = PrepareTestList();

	cout << "Size before clear (6): " << testingList.size() << endl;
	cout << "Is empty (false, 0): " << testingList.empty() << endl;
	testingList.clear();
	cout << "Size after clear (0): " << testingList.size() << endl;
	cout << "Is empty (true, 1): " << testingList.empty() << endl;

	CyclicList<int> newList;
	cout << "Is empty (true, 1): " << newList.empty() << endl;

	cout << "\n----------------\n\n";
}

void CyclicListTester::TestMaxSize(void)
{
	CyclicList<int> testingList;
	cout << "Max size for list: " << testingList.max_size() << endl;

	allocator<int> standardAllocator;
	CyclicList<int> listWithAllocator(standardAllocator);
	cout << "Max size for list (given allocator): " << testingList.max_size() << endl;

	cout << "\n----------------\n\n";
}

void CyclicListTester::TestFront(void)
{
	CyclicList<int>& testingList = PrepareTestList();

	int& variable = testingList.front();
	const CyclicList<int> constList(testingList);
	const int& constVariable = constList.front();

	cout << "Front (1): " << variable << endl;
	cout << "Const front (1): " << constVariable << endl;

	cout << "\n----------------\n\n";
}

void CyclicListTester::TestBack(void)
{
	CyclicList<int>& testingList = PrepareTestList();

	int& variable = testingList.back();
	const CyclicList<int> constList(testingList);
	const int& constVariable = constList.back();

	cout << "Back (6): " << variable << endl;
	cout << "Const back (6): " << constVariable << endl;

	testingList.push_back(7);
	cout << "Back (7): " << testingList.back() << endl;

	cout << "\n----------------\n\n";
}

void CyclicListTester::TestAssign(void)
{
	CyclicList<int>& testingList = PrepareTestList();

	list<int> classicList;
	classicList.push_back(7);
	classicList.push_back(14);
	testingList.assign(classicList.begin(), classicList.end());
	cout << "Should be: 7, 14; size (2): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	testingList.assign(5, 128);
	cout << "Should be: 5 x 128; size (5): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	CyclicList<int> originalList = PrepareTestList();
	testingList.assign(originalList.begin(), originalList.end());
	cout << "Should be: 1-6; size (6): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	cout << "\n----------------\n\n";
}

void CyclicListTester::TestPopFront(void)
{
	CyclicList<int>& testingList = PrepareTestList();

	cout << "Size before deleting from the front (6): " << testingList.size() << endl;
	cout << "First element (1): " << testingList.front() << endl;

	testingList.pop_front();
	cout << "Size after deleting from the front (5): " << testingList.size() << endl;
	cout << "First element (2): " << testingList.front() << endl;

	cout << "\n----------------\n\n";
}

void CyclicListTester::TestPopBack(void)
{
	CyclicList<int>& testingList = PrepareTestList();

	cout << "Size before deleting from the back (6): " << testingList.size() << endl;
	cout << "Last element (6): " << testingList.back() << endl;

	testingList.pop_back();
	cout << "Size after deleting from the back (5): " << testingList.size() << endl;
	cout << "Last element (5): " << testingList.back() << endl;

	cout << "\n----------------\n\n";
}

void CyclicListTester::TestInsert(void)
{
	CyclicList<int>& testingList = PrepareTestList();

	CyclicList<int>::iterator listIterator = testingList.begin();
	listIterator++;
	listIterator++;
	CyclicList<int>::iterator newIterator = testingList.insert(listIterator, 749);
	cout << "Added value (749): " << *newIterator << endl;
	newIterator++;
	cout << "Next value (3): " << *newIterator << endl;
	cout << "CyclicList: 1-2, 749, 3-6; size (7): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	newIterator++;
	testingList.insert(newIterator, 3, 44);
	cout << "Size (10): " << testingList.size() << endl;
	cout << "CyclicList: 1-2, 749, 3, 3 x 44, 4-6: \n";
	PrintList(testingList);
	cout << endl;

	testingList = PrepareTestList();
	listIterator = testingList.begin();
	listIterator++;
	listIterator++;
	listIterator++;
	list<int> standardList;
	standardList.push_back(2);
	standardList.push_back(1);
	standardList.push_back(3);
	testingList.insert(listIterator, standardList.begin(), standardList.end());
	cout << "Size (9): " << testingList.size() << endl;
	cout << "CyclicList: 1-3, 2, 1, 3, 4-6: \n";
	PrintList(testingList);
	cout << endl;

	testingList = PrepareTestList();
	listIterator = testingList.begin();
	standardList.clear();
	standardList.push_back(74);
	standardList.push_back(477);
	standardList.push_back(125);
	testingList.insert(listIterator, standardList.begin(), standardList.end());
	cout << "Size (9): " << testingList.size() << endl;
	cout << "CyclicList (insert on the front): 74, 477, 125, 1-6: \n";
	PrintList(testingList);
	cout << endl;

	testingList = PrepareTestList();
	listIterator = testingList.end();
	standardList.clear();
	standardList.push_back(12);
	standardList.push_back(17);
	standardList.push_back(22);
	testingList.insert(listIterator, standardList.begin(), standardList.end());
	cout << "Size (9): " << testingList.size() << endl;
	cout << "CyclicList (insert on the back): 1-6, 12, 17, 22: \n";
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void CyclicListTester::TestErase(void)
{
	CyclicList<int>& testingList = PrepareTestList();

	CyclicList<int>::iterator listIterator = testingList.begin();
	listIterator = testingList.erase(listIterator);
	CyclicList<int>::iterator resultIterator = testingList.erase(++++listIterator);
	resultIterator = testingList.erase(resultIterator);
	cout << "CyclicList after erase: 2, 3, 6; size (3): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	resultIterator = testingList.erase(testingList.begin(), ++++(testingList.begin()));
	cout << "CyclicList after erase with iterators: 6; size (1): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	testingList = PrepareTestList();
	testingList.erase(testingList.begin(), testingList.end());
	cout << "Should be: no elements; size (0): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	testingList = PrepareTestList();
	testingList.erase(++++testingList.begin(), testingList.end());
	cout << "List after erase with iterators: 1-2; size (2): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	testingList = PrepareTestList();
	listIterator = testingList.begin();
	++++listIterator;
	CyclicList<int>::iterator listIterator2 = listIterator;
	++++listIterator2;
	testingList.erase(listIterator, listIterator2);
	cout << "List after erase with iterators: 1-2, 5-6; size (4): " << testingList.size() << endl;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void CyclicListTester::TestSwap(void)
{
	CyclicList<int>& testingList = PrepareTestList();

	CyclicList<int> randomList = PrepareRandonIntList(4);
	cout << "Before swap, list1: 1-6; size (6): " << testingList.size() << endl;
	PrintList(testingList);
	cout << "Before swap, list2; size (4): " << randomList.size() << endl;
	PrintList(randomList);

	randomList.swap(testingList);
	cout << "After swap, list1; size (4): " << testingList.size() << endl;
	PrintList(testingList);
	cout << "After swap, list2: 1-6; size (6): " << randomList.size() << endl;
	PrintList(randomList);

	cout << "\n----------------\n\n";
}

void CyclicListTester::TestResize(void)
{
	CyclicList<int>& testingList = PrepareTestList();

	testingList.resize(3);
	cout << "CyclicList after resize (smaller): 1-3; size (3): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	testingList.resize(7, 256);
	cout << "CyclicList after resize (bigger): 1-3, 4 x 256; size (7): " << testingList.size() << endl;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void CyclicListTester::TestSplice(void)
{
	CyclicList<int>& testingList = PrepareTestList();

	int elementsForOtherList[5] = { 128, 256, 512, 1024, 2048 };
	CyclicList<int> otherList(elementsForOtherList, elementsForOtherList + 5);

	CyclicList<int>::iterator firstIterator = otherList.begin();
	firstIterator++;

	CyclicList<int>::iterator lastIterator = otherList.begin();
	lastIterator++;
	lastIterator++;
	lastIterator++;

	CyclicList<int>::iterator positionIterator = testingList.begin();
	positionIterator++;

	testingList.splice(positionIterator, otherList, firstIterator, lastIterator);

	cout << "CyclicList 1 after splice: 1, 256, 512, 2-6; size (8): " << testingList.size() << endl;
	PrintList(testingList);
	cout << "CyclicList 2 after splice: 128, 1024, 2048; size (3): " << otherList.size() << endl;
	PrintList(otherList);
	cout << endl;

	testingList = PrepareTestList();
	otherList = CyclicList<int>(elementsForOtherList, elementsForOtherList + 5);
	testingList.splice(testingList.begin(), otherList);
	cout << "CyclicList 1 after splice: 128-2048, 1-6; size (11): " << testingList.size() << endl;
	PrintList(testingList);
	cout << "CyclicList 2 after splice: no elements; size (0): " << otherList.size() << endl;
	PrintList(otherList);
	cout << endl;

	testingList = PrepareTestList();
	otherList = CyclicList<int>(elementsForOtherList, elementsForOtherList + 5);
	testingList.splice(testingList.end(), otherList);
	cout << "CyclicList 1 after splice: 1-6, 128-2048; size (11): " << testingList.size() << endl;
	PrintList(testingList);
	cout << "CyclicList 2 after splice: no elements; size (0): " << otherList.size() << endl;
	PrintList(otherList);
	cout << endl;

	testingList = PrepareTestList();
	otherList = CyclicList<int>(elementsForOtherList, elementsForOtherList + 5);
	firstIterator = otherList.begin();
	firstIterator++;
	firstIterator++;
	firstIterator++;
	firstIterator++;
	testingList.splice(testingList.begin(), otherList, firstIterator);
	cout << "CyclicList 1 after splice: 2048, 1-6; size (7): " << testingList.size() << endl;
	PrintList(testingList);
	cout << "CyclicList 2 after splice: 128-1024; size (4): " << otherList.size() << endl;
	PrintList(otherList);
	cout << endl;

	testingList.splice(testingList.end(), otherList, otherList.begin());
	cout << "CyclicList 1 after splice: 2048, 1-6, 128; size (8): " << testingList.size() << endl;
	PrintList(testingList);
	cout << "CyclicList 2 after splice; 256-1024; size (3): " << otherList.size() << endl;
	PrintList(otherList);
	cout << endl;

	testingList = PrepareTestList();
	positionIterator = testingList.begin();
	positionIterator++;
	otherList = CyclicList<int>(elementsForOtherList, elementsForOtherList + 5);
	firstIterator = otherList.begin();
	firstIterator++;
	testingList.splice(positionIterator, otherList, firstIterator);
	cout << "CyclicList 1 after splice: 1, 256, 2-6; size (7): " << testingList.size() << endl;
	PrintList(testingList);
	cout << "CyclicList 2 after splice: 128, 512-2048; size (4): " << otherList.size() << endl;
	PrintList(otherList);

	cout << "\n----------------\n\n";

}

void CyclicListTester::TestRemoveAndRemoveIf(void)
{
	CyclicList<int>& testingList = PrepareTestList();

	testingList.remove_if(IsEven<int>());
	cout << "CyclicList after remove_if: 1, 3, 5; size (3): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	testingList = PrepareTestList();
	testingList.remove(5);
	testingList.remove(1);
	cout << "CyclicList after remove: 2, 3, 4, 6; size (4): " << testingList.size() << endl;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void CyclicListTester::TestUnique(void)
{
	int elementsForList[5] = { 2, 3, 3, 3, 1 };
	CyclicList<int> testingList(elementsForList, elementsForList + 5);
	testingList.unique();
	cout << "CyclicList after unique: 2, 3, 1; size (3): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	int elementsForList2[6] = { 5, 5, 1, 6, 6, 5 };
	testingList = CyclicList<int>(elementsForList2, elementsForList2 + 6);
	testingList.unique();
	cout << "CyclicList after unique: 5, 1, 6, 5; size (4): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	int elementsForList3[5] = { 1, 3, 5, 1, 2 };
	testingList = CyclicList<int>(elementsForList3, elementsForList3 + 5);
	testingList.unique(SecondIsGreater<int>());
	cout << "CyclicList after unique with predicate: 5, 2; size (2): " << testingList.size() << endl;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void CyclicListTester::TestReverse(void)
{
	CyclicList<int>& testingList = PrepareTestList();

	testingList.reverse();
	cout << "CyclicList after reverse: 6-1; size (6): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	testingList.pop_back();
	testingList.reverse();
	cout << "CyclicList after reverse: 2-6; size (5): " << testingList.size() << endl;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void CyclicListTester::TestSort(void)
{
	int elementsForList[5] = { 2, 1, 3, 0, 1 };
	CyclicList<int> testingList(elementsForList, elementsForList + 5);
	cout << "CyclicList before sorting (5): " << testingList.size() << endl;
	PrintList(testingList);
	testingList.sort();
	cout << "CyclicList after sorting: 0, 1, 1, 2, 3; size (5): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	int elementsForList2[6] = { 77, 2, 128, 55, 974, 55 };
	testingList = CyclicList<int>(elementsForList2, elementsForList2 + 6);
	cout << "CyclicList before sorting with comparator (6): " << testingList.size() << endl;
	PrintList(testingList);
	testingList.sort(FirstGraterEqualThanSecond<int>());
	cout << "CyclicList after sorting with comparator: 974, 128, 77, 55, 55, 2; size (6): " << testingList.size() << endl;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void CyclicListTester::TestMerge(void)
{
	CyclicList<int> firstList = PrepareRandonIntList(4);
	CyclicList<int> secondList = PrepareRandonIntList(5);
	firstList.sort();
	secondList.sort();

	cout << "CyclicList 1 before merging (4): " << firstList.size() << endl;
	PrintList(firstList);
	cout << "CyclicList 2 before merging (5): " << secondList.size() << endl;
	PrintList(secondList);

	firstList.merge(secondList);
	cout << "CyclicList 1 after merging (9): " << firstList.size() << endl;
	PrintList(firstList);
	cout << "CyclicList 2 after merging (0): " << secondList.size() << endl;
	PrintList(secondList);

	cout << endl;


	firstList = PrepareRandonIntList(10);
	secondList = PrepareRandonIntList(6);
	firstList.sort(FirstGraterEqualThanSecond<int>());
	secondList.sort(FirstGraterEqualThanSecond<int>());

	cout << "CyclicList 1 before merging (10): " << firstList.size() << endl;
	PrintList(firstList);
	cout << "CyclicList 2 before merging (6): " << secondList.size() << endl;
	PrintList(secondList);

	firstList.merge(secondList, FirstGraterEqualThanSecond<int>());
	cout << "CyclicList 1 after merging with comparator (16): " << firstList.size() << endl;
	PrintList(firstList);
	cout << "CyclicList 2 after merging with comparator (0): " << secondList.size() << endl;
	PrintList(secondList);
	cout << "\n----------------\n\n";
}

void CyclicListTester::TestEmplaceFront(void)
{
	CyclicList<TestObjectMoreComplex> testingList;
	testingList.emplace_front(1, 2, 'Z');
	testingList.emplace_front(14, 28, 'j');

	CyclicList<TestObjectMoreComplex>::iterator iteratorForPrint = testingList.begin();
	cout << "emplace_front; size (2): " << testingList.size() << endl << endl;

	cout << "14, 28, j: \n";
	iteratorForPrint->Print();

	iteratorForPrint++;
	cout << "1, 2, Z: \n";
	iteratorForPrint->Print();

	cout << "----------------\n\n";
}

void CyclicListTester::TestEmplaceBack(void)
{
	CyclicList<TestObjectMoreComplex> testingList;
	testingList.emplace_back(11, 33, 'h');
	testingList.emplace_back(77, 154, 'f');

	CyclicList<TestObjectMoreComplex>::iterator iteratorForPrint = testingList.begin();
	cout << "emplace_back; size (2): " << testingList.size() << endl << endl;

	cout << "11, 33, h: \n";
	iteratorForPrint->Print();

	iteratorForPrint++;
	cout << "77, 154, f: \n";
	iteratorForPrint->Print();

	cout << "----------------\n\n";
}

void CyclicListTester::TestEmplace(void)
{
	CyclicList<TestObjectMoreComplex> testingList;
	CyclicList<TestObjectMoreComplex>::const_iterator iteratorForList = testingList.cbegin();
	iteratorForList = testingList.emplace(iteratorForList, 5, 6, 'c');
	iteratorForList = testingList.emplace(iteratorForList, 0, 1, 'a');
	iteratorForList++;
	testingList.emplace(iteratorForList, 3, 4, 'b');


	CyclicList<TestObjectMoreComplex>::iterator iteratorForPrint = testingList.begin();
	cout << "emplace; size (3): " << testingList.size() << endl << endl;

	cout << "0, 1, a: \n";
	iteratorForPrint->Print();

	iteratorForPrint++;
	cout << "3, 4, b: \n";
	iteratorForPrint->Print();

	iteratorForPrint++;
	cout << "5, 6, c: \n";
	iteratorForPrint->Print();

	cout << "----------------\n\n";
}

