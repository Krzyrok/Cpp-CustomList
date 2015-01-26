#include "Tester.h"

void Tester::Exeute(void)
{
	//TestClassicList();

	allocator <int> alloc;
	List<int> myIntList(alloc);

	TestPushBack(myIntList);
	TestPushFront(myIntList);
	TestSize(myIntList);
	TestListIterator(myIntList);

	system("Pause");
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

	
	// code below should not compile

	//itek = itConst;
	//*itConst = 77;
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
	
	shared_ptr<ListElement<int>> pointer(new ListElement<int>(new int(777)));
	List<int>::const_iterator constTestingIterator3(pointer);
	cout << "777: " << (*constTestingIterator3) << endl << endl;

	// code below should not compile

//	testingIterator = constTestingIterator; // should be error
//	constTestingIterator = testingList.begin();
//	*constTestingIterator = 124;  // should be error
//	cout << "should not compile for const_interator -> 124: " << (*constTestingIterator) << endl;
}

void Tester::TestBeginEndIterator(List<int>& testingList)
{

}