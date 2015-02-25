#include "FileReader.h"

vector<string> FileReader::ReadWordsIntoVector(string fileName)
{
	ifstream dictionaryFile;
	dictionaryFile.open(fileName);
	string line;

	vector<string> words;
	if (dictionaryFile.is_open())
	{
		while (getline(dictionaryFile, line))
		{
			words.push_back(line);
		}
		dictionaryFile.close();


	}
	else
	{
		cout << "Couldn't open the file.";
	}

	return words;
}