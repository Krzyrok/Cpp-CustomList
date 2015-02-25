#ifndef PRINTER_HEADER
#define PRINTER_HEADER

#include "CommonHeaders.h"

#include <time.h>  // clock_t, clock, CLOCKS_PER_SEC
#include <list>
#include <iostream>
#include <string>

class Printer
{
public:
	static void PrintExecutionTime(string message, double executionTime);
};

#endif