#include "Tester.h"

void Tester::Exeute(void)
{
	//TestClassicList();

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
	TestRemoveAndRemoveIf();
	TestUnique();
	TestReverse();
	TestSort();
	TestMerge();
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

List<int> Tester::PrepareTestList(void)
{
	List<int> newList;
	newList.push_front(6);
	newList.push_front(5);
	newList.push_front(4);
	newList.push_front(3);
	newList.push_front(2);
	newList.push_front(1);

	return newList;
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

	list<int> list2;
	list2.push_front(22);
	list2.push_front(77);
	itek = c.begin();
	list2.swap(c);
	cout << "Po zamianie it1: " << *itek << endl;
	cout << "A w liscie: " << *c.begin() << endl;

	int values1[4] = {1, 5, 88, 94};
	list<int> list1(values1, values1 + 4);
	int values2[4] = { 3, 17, 44, 102 };
	list2 = list<int>(values2, values2 + 4);
	list<int>::iterator itL2 = list2.begin();
	itL2++;
	itL2++;
	list1.merge(list2);
	cout << "It 2 : " << *itL2 << endl;
	cout << "list 2 size : " << list2.size() << endl;
	cout << "It 2++ : " << *++itL2 << endl;

}

void Tester::TestConstructors(void)
{
	List<int> emptyList;
	cout << "Size (0): " << emptyList.size() << endl << endl;

	allocator<int> alloc;
	List<int, allocator<int>> emptyList2(alloc);
	cout << "Size (0): " << emptyList2.size() << endl << endl;

	List<int> listWithTheSameValues(5, 1410);
	cout << "List: 5 x 1410; size (5): " << listWithTheSameValues.size() << endl;
	PrintList(listWithTheSameValues);
	cout << endl;

	List<int> randomList = PrepareRandonIntList(4);
	cout << "Size (4): " << randomList.size() << endl;
	PrintList(randomList);
	List<int> copiedListUsingIterators(randomList.begin(), randomList.end());
	cout << "Should be the same values as above; size (4): " << copiedListUsingIterators.size() << endl;
	PrintList(copiedListUsingIterators);
	cout << endl;

	list<int> originalList;
	originalList.push_front(1085);
	originalList.push_front(5);
	originalList.push_front(966);
	List<int> copiedListUsingIterators2(originalList.begin(), ++++originalList.begin());
	cout << "List: 966, 5; size (2): " << copiedListUsingIterators2.size() << endl;
	PrintList(copiedListUsingIterators2);
	cout << endl;

	List<int> listToCopy;
	listToCopy.push_front(1772);
	listToCopy.push_front(13);
	List<int> copiedList(listToCopy);
	cout << "List: 13, 1772; size (2): " << copiedList.size() << endl;
	PrintList(copiedList);
	cout << endl;

	listToCopy.clear();
	cout << "Should be nothing; size (0):" << listToCopy.size() << endl;
	PrintList(listToCopy);
	cout << "List: 13, 1772; size (2): " << copiedList.size() << endl;
	PrintList(copiedList);

	cout << "\n----------------\n\n";
}

void Tester::TestPushBack(void)
{
	List<int> testingList;
	testingList.push_back(4);
	testingList.push_back(5);
	testingList.push_back(6);
	cout << "List: 4-6; size (3): " << testingList.size() << endl;
	PrintList(testingList);
	cout << "\n----------------\n\n";
}

void Tester::TestPushFront(void)
{
	List<int> testingList;
	testingList.push_front(3);
	testingList.push_front(2);
	testingList.push_front(1);
	cout << "List: 1-3; size (3): " << testingList.size() << endl;
	PrintList(testingList);
	cout << "\n----------------\n\n";
}

void Tester::TestSize(void)
{
	List<int>& testingList = PrepareTestList();
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

void Tester::TestListIterator(void)
{
	List<int>& testingList = PrepareTestList();

	List<int>::iterator testingIterator = testingList.begin();

	cout << "1: " << (*testingIterator++) << endl;
	cout << "3: " << (*++testingIterator) << endl;
	cout << "4: " << (*++testingIterator) << endl;
	cout << "5: " << (*++testingIterator) << endl << endl;
	
	testingIterator = testingList.begin();
	List<int>::iterator testingIterator2 = testingList.begin();
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
	List<int>::iterator iterator3(testingIterator);
	cout << "Checking iterators difference (false, 0): " << (testingIterator != iterator3) << endl;
	cout << "Checking iterators equality (true, 1): " << (testingIterator == iterator3) << endl;
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
	cout << "Test message: \n";
	iteratorForTestObject->PrintSomething();


	// testing const_iterator
	List<int>::const_iterator constTestingIterator = testingList.begin();
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


	List<int>::const_iterator constTestingIterator2 = testingList.begin();
	cout << "Checking const iterators difference (false, 0): " << (constTestingIterator != constTestingIterator2) << endl;
	cout << "Checking const iterators equality (true, 1): " << (constTestingIterator == constTestingIterator2) << endl << endl;
	
	
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

void Tester::TestBeginEndIterator(void)
{
	List<int>& testingList = PrepareTestList();
	PrintList(testingList);
	cout << "\n----------------\n\n";
}

void Tester::TestClear(void)
{
	List<int>& testingList = PrepareTestList();
	cout << "List before clear: 1-6; size (6): " << testingList.size() << endl;
	PrintList(testingList);

	testingList.clear();
	cout << "List after clear: no elements; size (0): " << testingList.size() << endl ;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void Tester::TestEmpty(void)
{
	List<int>& testingList = PrepareTestList();

	cout << "Size before clear (6): " << testingList.size() << endl;
	cout << "Is empty (false, 0): " << testingList.empty() << endl;
	testingList.clear();
	cout << "Size after clear (0): " << testingList.size() << endl;
	cout << "Is empty (true, 1): " << testingList.empty() << endl;

	List<int> newList;
	cout << "Is empty (true, 1): " << newList.empty() << endl;

	cout << "\n----------------\n\n";
}

void Tester::TestMaxSize(void)
{
	List<int> testingList;
	cout << "Max size for list: " << testingList.max_size() << endl;

	allocator<int> standardAllocator;
	List<int> listWithAllocator(standardAllocator);
	cout << "Max size for list (given allocator): " << testingList.max_size() << endl;

	cout << "\n----------------\n\n";
}

void Tester::TestFront(void)
{
	List<int>& testingList = PrepareTestList();

	int& variable = testingList.front();
	const List<int> constList(testingList);
	const int& constVariable = constList.front();

	cout << "Front (1): " << variable << endl;
	cout << "Const front (1): " << constVariable << endl;

	cout << "\n----------------\n\n";
}

void Tester::TestBack(void)
{
	List<int>& testingList = PrepareTestList();

	int& variable = testingList.back();
	const List<int> constList(testingList);
	const int& constVariable = constList.back();

	cout << "Back (6): " << variable << endl;
	cout << "Const back (6): " << constVariable << endl;

	testingList.push_back(7);
	cout << "Back (7): " << testingList.back() << endl;

	cout << "\n----------------\n\n";
}

void Tester::TestAssign(void)
{
	List<int>& testingList = PrepareTestList();

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

	List<int> originalList = PrepareTestList();
	testingList.assign(originalList.begin(), originalList.end());
	cout << "Should be: 1-6; size (6): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	cout << "\n----------------\n\n";
}

void Tester::TestPopFront(void)
{
	List<int>& testingList = PrepareTestList();
	
	cout << "Size before deleting from the front (6): " << testingList.size() << endl;
	cout << "First element (1): " << testingList.front() << endl;

	testingList.pop_front();
	cout << "Size after deleting from the front (5): " << testingList.size() << endl;
	cout << "First element (2): " << testingList.front() << endl;

	cout << "\n----------------\n\n";
}

void Tester::TestPopBack(void)
{
	List<int>& testingList = PrepareTestList();

	cout << "Size before deleting from the back (6): " << testingList.size() << endl;
	cout << "Last element (6): " << testingList.back() << endl;

	testingList.pop_back();
	cout << "Size after deleting from the back (5): " << testingList.size() << endl;
	cout << "Last element (5): " << testingList.back() << endl;

	cout << "\n----------------\n\n";
}

void Tester::TestInsert(void)
{
	List<int>& testingList = PrepareTestList();
	
	List<int>::iterator listIterator = testingList.begin();
	listIterator++;
	listIterator++;
	List<int>::iterator newIterator = testingList.insert(listIterator, 749);
	cout << "Added value (749): " << *newIterator << endl;
	newIterator++;
	cout << "Next value (3): " << *newIterator << endl;
	cout << "List: 1-2, 749, 3-6; size (7):" << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	newIterator++;
	testingList.insert(newIterator, 3, 44);
	cout << "Size (10): " << testingList.size() << endl;
	cout << "List: 1-2, 749, 3, 3 x 44, 4-6: \n";
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
	cout << "List: 1-3, 2, 1, 3, 4-6: \n";
	PrintList(testingList);
	cout << endl;

	cout << "\n----------------\n\n";
}

void Tester::TestErase(void)
{
	List<int>& testingList = PrepareTestList();

	List<int>::iterator listIterator = testingList.begin();
	testingList.erase(listIterator);
	List<int>::iterator resultIterator = testingList.erase(++++listIterator);
	testingList.erase(resultIterator);
	cout << "List after erase: 2, 5, 6; size (3): " << testingList.size() << endl;
	PrintList(testingList);

	resultIterator = testingList.erase(testingList.begin(), ++++(testingList.begin()));
	cout << "List after erase with iterators: 6; size (1): " << testingList.size() << endl;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void Tester::TestSwap(void)
{
	List<int>& testingList = PrepareTestList();

	List<int> randomList = PrepareRandonIntList(4);
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

void Tester::TestResize(void)
{
	List<int>& testingList = PrepareTestList();

	testingList.resize(3);
	cout << "List after resize (smaller): 1-3; size (3): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	testingList.resize(7, 256);
	cout << "List after resize (bigger): 1-3, 4 x 256; size (7): " << testingList.size() << endl;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void Tester::TestSplice(void)
{
	List<int>& testingList = PrepareTestList();
	
	int elementsForOtherList[5] = {128, 256, 512, 1024, 2048};
	List<int> otherList(elementsForOtherList, elementsForOtherList + 5);
	
	List<int>::iterator firstIterator = otherList.begin();
	firstIterator++;

	List<int>::iterator lastIterator = otherList.begin();
	lastIterator++;
	lastIterator++;
	lastIterator++;

	List<int>::iterator positionIterator = testingList.begin();
	positionIterator++;

	testingList.splice(positionIterator, otherList, firstIterator, lastIterator);

	cout << "List 1 after splice: 1, 256, 512, 2-6; size (8): " << testingList.size() << endl;
	PrintList(testingList);
	cout << "List 2 after splice: 128, 1024, 2048; size (3): " << otherList.size() << endl;
	PrintList(otherList);
	cout << endl;

	testingList = PrepareTestList();
	otherList = List<int>(elementsForOtherList, elementsForOtherList + 5);
	testingList.splice(testingList.begin(), otherList);
	cout << "List 1 after splice: 128-2048, 1-6; size (11): " << testingList.size() << endl;
	PrintList(testingList);
	cout << "List 2 after splice: no elements; size (0): " << otherList.size() << endl;
	PrintList(otherList);
	cout << endl;

	testingList = PrepareTestList();
	otherList = List<int>(elementsForOtherList, elementsForOtherList + 5);
	testingList.splice(testingList.end(), otherList);
	cout << "List 1 after splice: 1-6, 128-2048; size (11): " << testingList.size() << endl;
	PrintList(testingList);
	cout << "List 2 after splice: no elements; size (0): " << otherList.size() << endl;
	PrintList(otherList);
	cout << endl;

	testingList = PrepareTestList();
	otherList = List<int>(elementsForOtherList, elementsForOtherList + 5);
	firstIterator = otherList.begin();
	firstIterator++;
	firstIterator++;
	firstIterator++;
	firstIterator++;
	testingList.splice(testingList.begin(), otherList, firstIterator);
	cout << "List 1 after splice: 2048, 1-6; size (7): " << testingList.size() << endl;
	PrintList(testingList);
	cout << "List 2 after splice: 128-1024; size (4): " << otherList.size() << endl;
	PrintList(otherList);
	cout << endl;

	testingList.splice(testingList.end(), otherList, otherList.begin());
	cout << "List 1 after splice: 2048, 1-6, 128; size (8): " << testingList.size() << endl;
	PrintList(testingList);
	cout << "List 2 after splice; 256-1024; size (3): " << otherList.size() << endl;
	PrintList(otherList);
	cout << endl;

	testingList = PrepareTestList();
	positionIterator = testingList.begin();
	positionIterator++;
	otherList = List<int>(elementsForOtherList, elementsForOtherList + 5);
	firstIterator = otherList.begin();
	firstIterator++;
	testingList.splice(positionIterator, otherList, firstIterator);
	cout << "List 1 after splice: 1, 256, 2-6; size (7): " << testingList.size() << endl;
	PrintList(testingList);
	cout << "List 2 after splice: 128, 512-2048; size (4): " << otherList.size() << endl;
	PrintList(otherList);

	cout << "\n----------------\n\n";

}

void Tester::TestRemoveAndRemoveIf(void)
{
	List<int>& testingList = PrepareTestList();

	testingList.remove_if(IsEven<int>());
	cout << "List after remove_if: 1, 3, 5; size (3): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	testingList = PrepareTestList();
	testingList.remove(5);
	testingList.remove(1);
	cout << "List after remove: 2, 3, 4, 6; size (4): " << testingList.size() << endl;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void Tester::TestUnique(void)
{
	int elementsForList[5] = { 2, 3, 3, 3, 1 };
	List<int> testingList(elementsForList, elementsForList + 5);
	testingList.unique();
	cout << "List after unique: 2, 3, 1; size (3): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	int elementsForList2[6] = { 5, 5, 1, 6, 6, 5 };
	testingList = List<int>(elementsForList2, elementsForList2 + 6);
	testingList.unique();
	cout << "List after unique: 5, 1, 6, 5; size (4): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	int elementsForList3[5] = { 1, 3, 5, 1, 2 };
	testingList = List<int>(elementsForList3, elementsForList3 + 5);
	testingList.unique(SecondIsGreater<int>());
	cout << "List after unique with predicate: 5, 2; size (2): " << testingList.size() << endl;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void Tester::TestReverse(void)
{
	List<int>& testingList = PrepareTestList();

	testingList.reverse();
	cout << "List after reverse: 6-1; size (6): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	testingList.pop_back();
	testingList.reverse();
	cout << "List after reverse: 2-6; size (5): " << testingList.size() << endl;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void Tester::TestSort(void)
{
	int elementsForList[5] = { 2, 1, 3, 0, 1 };
	List<int> testingList(elementsForList, elementsForList + 5);
	cout << "List before sorting (5): " << testingList.size() << endl;
	PrintList(testingList);
	testingList.sort();
	cout << "List after sorting: 0, 1, 1, 2, 3; size (5): " << testingList.size() << endl;
	PrintList(testingList);
	cout << endl;

	int elementsForList2[6] = { 77, 2, 128, 55, 974, 55 };
	testingList = List<int>(elementsForList2, elementsForList2 + 6);
	cout << "List before sorting with comparator (6): " << testingList.size() << endl;
	PrintList(testingList);
	testingList.sort(FirstGraterEqualThanSecond<int>());
	cout << "List after sorting with comparator: 974, 128, 77, 55, 55, 2; size (6): " << testingList.size() << endl;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void Tester::TestMerge(void)
{
	List<int> firstList = PrepareRandonIntList(4);
	List<int> secondList = PrepareRandonIntList(5);
	firstList.sort();
	secondList.sort();
	
	cout << "List 1 before merging (4): " << firstList.size() << endl;
	PrintList(firstList);
	cout << "List 2 before merging (5): " << secondList.size() << endl;
	PrintList(secondList);

	firstList.merge(secondList);
	cout << "List 1 after merging (9): " << firstList.size() << endl;
	PrintList(firstList);
	cout << "List 2 after merging (0): " << secondList.size() << endl;
	PrintList(secondList);

	cout << endl;


	firstList = PrepareRandonIntList(10);
	secondList = PrepareRandonIntList(6);
	firstList.sort(FirstGraterEqualThanSecond<int>());
	secondList.sort(FirstGraterEqualThanSecond<int>());

	cout << "List 1 before merging (10): " << firstList.size() << endl;
	PrintList(firstList);
	cout << "List 2 before merging (6): " << secondList.size() << endl;
	PrintList(secondList);

	firstList.merge(secondList, FirstGraterEqualThanSecond<int>());
	cout << "List 1 after merging with comparator (16): " << firstList.size() << endl;
	PrintList(firstList);
	cout << "List 2 after merging with comparator (0): " << secondList.size() << endl;
	PrintList(secondList);
	cout << "\n----------------\n\n";
}

