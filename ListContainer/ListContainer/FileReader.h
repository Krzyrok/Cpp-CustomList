#ifndef FILE_READER_HEADER
#define FILE_READER_HEADER

#include "CommonHeaders.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

class FileReader
{
public:
	static vector<string> ReadWordsIntoVector(string fileName);
};

#endif