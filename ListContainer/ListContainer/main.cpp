#include "CommonHeaders.h"
#include "List.h"
#include <list>
#include <iostream>

int main()
{
	cout << "tests" << endl;

	list<int> c;
	cout << c.max_size() << endl;
	list<int>::iterator itek = c.begin();

	allocator < int > alloc;
	shared_ptr<int> ptr(new int(5));

	List<int> myIntList(alloc);
	myIntList.push_back(5);
	myIntList.push_back(12);
	myIntList.push_back(7);

	system("Pause");
	return 0;
}

