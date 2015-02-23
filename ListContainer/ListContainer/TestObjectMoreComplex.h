#ifndef TEST_OBJECT_MORE_COMPLEX_HEADER
#define TEST_OBJECT_MORE_COMPLEX_HEADER

#include "CommonHeaders.h"

#include <iostream>

class TestObjectMoreComplex
{
public:
	int Value1 = 44;
	int Value2 = 88;
	char Value3 = 'A';

	TestObjectMoreComplex(int arg1, int arg2, char arg3)
		: Value1(arg1), Value2(arg2), Value3(arg3)
	{
	}

	void Print(void)
	{
		cout << "Test message from TestObject! \nValue1: " << Value1 
			<< "\nValue2: " << Value2 << "\nValue3: "<< Value3 << "\n\n";
	}
};

#endif
