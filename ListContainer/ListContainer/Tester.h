#ifndef TESTER_HEADER
#define TESTER_HEADER

#include "List.h"

#include <list>
#include <iostream>

class Tester
{
public: 
	void Exeute(void);

private:
	void TestPushBack(List<int>& testingList);
	void TestBeginIterator(List<int>& testingList);
};

#endif 
