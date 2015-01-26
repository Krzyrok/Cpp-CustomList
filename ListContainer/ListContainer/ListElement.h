#ifndef LIST_ELEMENT_HEADER
#define LIST_ELEMENT_HEADER

#include "Deleter.h"

#include <memory>

template<class Type, class Allocator>
class ListElement
{
public:
	ListElement(const Type& insertingValue, Allocator& passedAllocator)
	{
		NextElementPointer = nullptr;
		
		//Type* insertingValuePointer = new Type(insertingValue);

		Type* insertingValuePointer = passedAllocator.allocate(1);
		passedAllocator.construct(insertingValuePointer, insertingValue);
		
		Deleter<Type, Allocator> deleter(passedAllocator);
		ValuePointer = shared_ptr<Type>(insertingValuePointer, deleter);
	}

	Type& GetValue(void)
	{
		return *ValuePointer;
	}


	shared_ptr<Type> ValuePointer;
	shared_ptr<ListElement<Type, Allocator>> NextElementPointer;

};

#endif
