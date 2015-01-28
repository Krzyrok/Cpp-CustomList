#include "Tester.h"

void Tester::Exeute(void)
{
	//TestClassicList();

	srand((unsigned int)time(NULL));

	allocator <int> alloc;
	List<int> myIntList(alloc);

	//TestConstructors();
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
	TestAssign(myIntList);
	TestPopFront(myIntList);
	TestPopBack(myIntList);
	TestInsert(myIntList);
	TestErase(myIntList);
	TestSwap(myIntList);
	TestResize(myIntList);
	TestSplice(myIntList);
	TestRemoveAndRemoveIf(myIntList);
	TestUnique();
	TestReverse(myIntList);
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

void Tester::PrepareStandardList(List<int>& printingList)
{
	printingList.clear();
	TestPushBack(printingList);
	TestPushFront(printingList);
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

void Tester::TestAssign(List<int>& testingList)
{
	list<int> classicList;
	classicList.push_back(7);
	classicList.push_back(14);
	testingList.assign(classicList.begin(), classicList.end());
	cout << "Should be 7, 14:" << endl;
	PrintList(testingList);
	cout << endl;

	testingList.assign(5, 128);
	cout << "Should be 5 x 128:" << endl;
	PrintList(testingList);
	cout << endl;

	List<int> originalList;
	TestPushBack(originalList);
	TestPushFront(originalList);
	testingList.assign(originalList.begin(), originalList.end());
	cout << "Should be 1 - 6:" << endl;
	PrintList(testingList);
	cout << endl;

	cout << "\n----------------\n\n";
}

void Tester::TestPopFront(List<int>& testingList)
{
	cout << "Size before deleting (6): " << testingList.size() << endl;
	cout << "First element (1): " << testingList.front() << endl;

	testingList.pop_front();
	cout << "Size after deleting (5): " << testingList.size() << endl;
	cout << "First element (2): " << testingList.front() << endl;

	testingList.push_front(1);
	cout << "\n----------------\n\n";
}

void Tester::TestPopBack(List<int>& testingList)
{
	cout << "Size before deleting (6): " << testingList.size() << endl;
	cout << "Last element (6): " << testingList.back() << endl;

	testingList.pop_back();
	cout << "Size after deleting (5): " << testingList.size() << endl;
	cout << "Last element (5): " << testingList.back() << endl;

	testingList.push_back(6);
	cout << "\n----------------\n\n";
}

void Tester::TestInsert(List<int>& testingList)
{
	List<int>::iterator listIterator = testingList.begin();
	listIterator++;
	listIterator++;
	List<int>::iterator newIterator = testingList.insert(listIterator, 749);
	cout << "Added value (749): " << *newIterator << endl;
	newIterator++;
	cout << "Next value (3): " << *newIterator << endl;
	cout << "Size (7): " << testingList.size() << endl;
	cout << "Complete list: \n";
	PrintList(testingList);
	cout << endl;

	newIterator++;
	testingList.insert(newIterator, 3, 44);
	cout << "Size (10): " << testingList.size() << endl;
	cout << "Complete list (should be 3 x 44 after no 3): \n";
	PrintList(testingList);
	cout << endl;

	PrepareStandardList(testingList);
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
	cout << "Complete list (should be 2 1 3 after no 3): \n";
	PrintList(testingList);
	cout << endl;

	PrepareStandardList(testingList);
	cout << "\n----------------\n\n";
}

void Tester::TestErase(List<int>& testingList)
{
	List<int>::iterator listIterator = testingList.begin();
	testingList.erase(listIterator);
	List<int>::iterator resultIterator = testingList.erase(++++listIterator);
	testingList.erase(resultIterator);
	cout << "Should be without 2, 5, 6:" << endl;
	PrintList(testingList);

	resultIterator = testingList.erase(testingList.begin(), ++++(testingList.begin()));
	cout << "Should be only 6:" << endl;
	PrintList(testingList);

	PrepareStandardList(testingList);
	cout << "\n----------------\n\n";
}

void Tester::TestSwap(List<int>& testingList)
{
	List<int> randomList = PrepareRandonIntList();
	cout << "Before swap, list1:" << endl;
	PrintList(testingList);
	cout << "Before swap, list2:" << endl;
	PrintList(randomList);

	randomList.swap(testingList);
	cout << "After swap, list1, size:" << testingList.size() << endl;
	PrintList(testingList);
	cout << "After swap, list2:" << randomList.size() << endl;
	PrintList(randomList);

	cout << "\n----------------\n\n";
}

void Tester::TestResize(List<int>& testingList)
{
	PrepareStandardList(testingList);
	testingList.resize(3);
	cout << "Should be 1-3, size::" << testingList.size() << endl;
	PrintList(testingList);

	testingList.resize(7, 256);
	cout << "Should be + 4 x 256, size::" << testingList.size() << endl;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void Tester::TestSplice(List<int>& testingList)
{
	PrepareStandardList(testingList);
	
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

	cout << "List 1 after splice, size (8) - 1, 256, 512, 2: " << testingList.size() << endl;
	PrintList(testingList);
	cout << "List 2 after splice, size (3) - 128, 1024, 2048: " << otherList.size() << endl;
	PrintList(otherList);


	PrepareStandardList(testingList);
	otherList = List<int>(elementsForOtherList, elementsForOtherList + 5);
	testingList.splice(testingList.begin(), otherList);
	cout << "List after splice, size (11) - 128-2048, 1-6: " << testingList.size() << endl;
	PrintList(testingList);
	cout << "List 2 after splice, size (0, non elements): " << otherList.size() << endl;
	PrintList(otherList);

	PrepareStandardList(testingList);
	otherList = List<int>(elementsForOtherList, elementsForOtherList + 5);
	testingList.splice(testingList.end(), otherList);
	cout << "List after splice, size (11) - 1-6, 128-2048 : " << testingList.size() << endl;
	PrintList(testingList);
	cout << "List 2 after splice, size (0, non elements): " << otherList.size() << endl;
	PrintList(otherList);

	PrepareStandardList(testingList);
	otherList = List<int>(elementsForOtherList, elementsForOtherList + 5);
	firstIterator = otherList.begin();
	firstIterator++;
	firstIterator++;
	firstIterator++;
	firstIterator++;
	testingList.splice(testingList.begin(), otherList, firstIterator);
	cout << "List after splice, size (7) - 2048, 1-6: " << testingList.size() << endl;
	PrintList(testingList);
	cout << "List 2 after splice, size (4) - 128-1024: " << otherList.size() << endl;
	PrintList(otherList);

	testingList.splice(testingList.end(), otherList, otherList.begin());
	cout << "List after splice, size (8) - 2048, 1-6, 128: " << testingList.size() << endl;
	PrintList(testingList);
	cout << "List 2 after splice, size (3) - 256-1024: " << otherList.size() << endl;
	PrintList(otherList);


	PrepareStandardList(testingList);
	positionIterator = testingList.begin();
	positionIterator++;
	otherList = List<int>(elementsForOtherList, elementsForOtherList + 5);
	firstIterator = otherList.begin();
	firstIterator++;
	testingList.splice(positionIterator, otherList, firstIterator);
	cout << "List after splice, size (7) - 1,256,2-6: " << testingList.size() << endl;
	PrintList(testingList);
	cout << "List 2 after splice, size (4) - 128,512-2048: " << otherList.size() << endl;
	PrintList(otherList);

	cout << "\n----------------\n\n";

}

void Tester::TestRemoveAndRemoveIf(List<int>& testingList)
{
	PrepareStandardList(testingList);
	testingList.remove_if(IsEven<int>());
	cout << "List after remove, size (3) - 1,3,5: " << testingList.size() << endl;
	PrintList(testingList);

	PrepareStandardList(testingList);
	testingList.remove(5);
	testingList.remove(1);
	cout << "List after remove, size (4) - 2,3,4,6: " << testingList.size() << endl;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void Tester::TestUnique(void)
{
	int elementsForList[5] = { 2, 3, 3, 3, 1 };
	List<int> testingList(elementsForList, elementsForList + 5);
	testingList.unique();
	cout << "List after unique, size (3) - 2,3,1: " << testingList.size() << endl;
	PrintList(testingList);

	int elementsForList2[5] = { 5, 5, 1, 6, 6 };
	testingList = List<int>(elementsForList2, elementsForList2 + 5);
	testingList.unique();
	cout << "List after unique, size (3) - 5,1,6: " << testingList.size() << endl;
	PrintList(testingList);

	int elementsForList3[5] = { 1, 3, 5, 1, 2 };
	testingList = List<int>(elementsForList3, elementsForList3 + 5);
	testingList.unique(SecondIsGreater<int>());
	cout << "List after unique with predicate, size (2) - 5,1: " << testingList.size() << endl;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void Tester::TestReverse(List<int>& testingList)
{
	PrepareStandardList(testingList);
	testingList.reverse();
	cout << "After reverse (6) 6-1: " << testingList.size() << endl;
	PrintList(testingList);

	testingList.pop_back();
	testingList.reverse();
	cout << "After reverse (5) 2-6: " << testingList.size() << endl;
	PrintList(testingList);

	cout << "\n----------------\n\n";
}

void Tester::TestSort(void)
{
	int elementsForList[5] = { 2, 1, 3, 0, 1 };
	List<int> testingList(elementsForList, elementsForList + 5);
	cout << "Before sorting (5): " << testingList.size() << endl;
	PrintList(testingList);
	testingList.sort();
	cout << "After sorting (5): " << testingList.size() << endl;
	PrintList(testingList);

	int elementsForList2[5] = { 77, 2, 128, 55, 974 };
	testingList = List<int>(elementsForList2, elementsForList2 + 5);
	cout << "Before sorting (5): " << testingList.size() << endl;
	PrintList(testingList);
	testingList.sort(FirstGraterEqualThanSecond<int>());
	cout << "After sorting (5): " << testingList.size() << endl;
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



	firstList = PrepareRandonIntList(10);
	secondList = PrepareRandonIntList(6);
	firstList.sort(FirstGraterEqualThanSecond<int>());
	secondList.sort(FirstGraterEqualThanSecond<int>());

	cout << "List 1 before merging (10): " << firstList.size() << endl;
	PrintList(firstList);
	cout << "List 2 before merging (6): " << secondList.size() << endl;
	PrintList(secondList);

	firstList.merge(secondList, FirstGraterEqualThanSecond<int>());
	cout << "List 1 after merging (16): " << firstList.size() << endl;
	PrintList(firstList);
	cout << "List 2 after merging (0): " << secondList.size() << endl;
	PrintList(secondList);
	cout << "\n----------------\n\n";
}

