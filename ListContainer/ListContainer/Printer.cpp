#include "Printer.h"

void Printer::PrintExecutionTime(string message, double executionTime)
{
	cout << "Execution time of " << message << ": " << ((double)executionTime / CLOCKS_PER_SEC) * 1000 << " ms. \n\n";
}