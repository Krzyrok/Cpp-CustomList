#ifndef LIST_ELEMENT_HEADER
#define LIST_ELEMENT_HEADER

#include "CommonHeaders.h"

#include <memory>

template<class Type>
class ListElement
{
public:
	ListElement(Type insertingValue);
	Type& GetValue(void);

	shared_ptr<ListElement<Type>> NextElement;

private:
	Type Value;
};

template<class Type>
ListElement<Type>::ListElement(Type insertingValue)
{
	NextElement = nullptr;
	Value = insertingValue;
}

template<class Type>
Type& ListElement<Type>::GetValue(void)
{
	return Value;
}

#endif
