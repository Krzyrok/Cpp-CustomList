#include "Tester.h"

void Tester::Exeute(void)
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
	itConst = c.begin();
	//*itConst = 77;
	


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
		cout << "size works corretly: " << testingList.size() << endl << endl;
	}
	else
	{
		cout << "size DOESN'T work!!!! RESULT: " << testingList.size() << endl << endl;
	}
}

void Tester::TestListIterator(List<int>& testingList)
{
	List<int>::Iterator testingIterator = testingList.begin();

	cout << "1: " << (*testingIterator++) << endl;
	cout << "3: " << (*++testingIterator) << endl;
	cout << "4: " << (*++testingIterator) << endl;
	cout << "5: " << (*++testingIterator) << endl << endl;
	
	testingIterator = testingList.begin();
	List<int>::Iterator testingIterator2 = testingList.begin();
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
	List<int>::Iterator iterator3(testingIterator);
	cout << "checking difference (should be false): " << (testingIterator != iterator3) << endl;
	cout << "checking equality (should be true): " << (testingIterator == iterator3) << endl;
	cout << "1: " << *iterator3 << endl << endl;

	testingIterator = testingList.begin();
	*testingIterator = 77;
	cout << "77: " << *testingIterator++ << endl;
	cout << "77: " << *iterator3 << endl;
	cout << "2: " << *testingIterator << endl << endl;


	//shared_ptr<const TestObject> to_ptr = shared_ptr<TestObject>(new TestObject);
	//cout << to_ptr->TestValue <<endl;

	ListElement<const int> tle = ListElement<const int>(new int(798));
	//tle.GetValue() = 44;
	cout << tle.GetValue() << endl;;

	List<TestObject> listTestObject;
	listTestObject.push_front(TestObject());
	listTestObject.push_front(TestObject());
	List<TestObject>::Iterator iteratorForTestObject = listTestObject.begin();
	//iteratorForTestObject->PrintSomething();


	// testing const_iterator
	List<int>::Const_Iterator constTestingIterator = testingList.begin();
	//testingIterator = testingList.begin();
	//cout << "77: " << (*constTestingIterator++) << endl;
	//cout << "3: " << (*++constTestingIterator) << endl;
	//constTestingIterator = testingList.begin();
	//cout << "checking difference (should be false): " << (constTestingIterator != testingIterator) << endl;
	//cout << "checking equality (should be true): " << (constTestingIterator == testingIterator) << endl << endl;
	//constTestingIterator = testingList.begin();
	//*constTestingIterator = 124;
	cout << "should not compile for const_interator -> 124: " << (*constTestingIterator) << endl;
}