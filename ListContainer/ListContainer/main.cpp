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

	List<int> myIntList;
	myIntList.push_front(5);

	system("Pause");
	return 0;
}

