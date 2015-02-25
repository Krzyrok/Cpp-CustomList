#include "ListTester.h"
#include "CyclicListTester.h"
#include "Comparer.h"

int main()
{
	srand((unsigned int)time(NULL));
	//ListTester listTester;
	//listTester.Exeute();

	//CyclicListTester cyclicListTester;
	//cyclicListTester.Exeute();

	Comparer comparer;
	comparer.Execute();

	system("Pause");
	return 0;
}

