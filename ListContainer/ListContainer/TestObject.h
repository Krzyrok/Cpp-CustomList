#ifndef TEST_OBJECT_HEADER
#define TEST_OBJECT_HEADER

#include "CommonHeaders.h"

#include <iostream>

class TestObject
{
public:
	int TestValue = 44;

	void PrintSomething(void)
	{
		cout << "Test message from TesTObject\n\n";
	}
};

#endif
