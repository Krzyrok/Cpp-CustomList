#ifndef LIST_ELEMENT_HEADER
#define LIST_ELEMENT_HEADER

#include "CommonHeaders.h"

#include <memory>

template<class Type, class Allocator = allocator<Type>>
class ListElement
{
public:
	ListElement(Type* insertingValuePointer)
	{
		NextElementPointer = nullptr;
		ValuePointer = shared_ptr<Type>(insertingValuePointer);
	}

	Type& GetValue(void)
	{
		return *ValuePointer;
	}

	~ListElement(void)
	{
		cout << "Deleted " << endl;
	}


	shared_ptr<Type> ValuePointer;
	shared_ptr<ListElement<Type>> NextElementPointer;
};

#endif
