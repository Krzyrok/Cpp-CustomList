#ifndef LIST_ELEMENT_HEADER
#define LIST_ELEMENT_HEADER

#include "CommonHeaders.h"

#include <memory>

template<class Type>
class ListElement
{
public:
	ListElement(Type insertingValue);

	Type Value;
	shared_ptr<ListElement<Type>> NextElementPtr;
};

template<class Type>
ListElement<Type>::ListElement(Type insertingValue)
{
	NextElementPtr = nullptr;
	Value = insertingValue;
}

#endif
