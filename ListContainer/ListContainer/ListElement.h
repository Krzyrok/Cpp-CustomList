#ifndef LIST_ELEMENT_HEADER
#define LIST_ELEMENT_HEADER

#include "CommonHeaders.h"

#include <memory>

template<class Type, class Allocator = allocator<Type>>
class ListElement
{
public:
	ListElement(Type* insertingValuePointer);
	
	Type& GetValue(void);

	shared_ptr<Type> ValuePointer;
	shared_ptr<ListElement<Type>> NextElementPtr;
};

template<class Type, class Allocator = allocator<Type>>
ListElement<Type, Allocator>::ListElement(Type* insertingValuePointer)
{
	NextElementPtr = nullptr;
	ValuePointer = shared_ptr<Type>(insertingValuePointer);
}

template<class Type, class Allocator = allocator<Type>>
Type& ListElement<Type, Allocator>::GetValue(void)
{
	return *ValuePointer;
}
#endif
