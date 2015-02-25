#include "Comparer.h"

void Comparer::Execute(void)
{
	vector<string> dictionary = FileReader::ReadWordsIntoVector("english.dic.txt");
	random_shuffle(dictionary.begin(), dictionary.end());



}