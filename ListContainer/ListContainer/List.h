#ifndef LIST_HEADER
#define LIST_HEADER

#include "ListElement.h"

#include <xmemory0>

template<class Type, class Allocator = allocator<Type>>
class List
{
public:
	List(const Allocator& passedAlloc = Allocator());

	void begin(void);
	void push_front(const Type& value);

private:
	shared_ptr<ListElement<Type>> _firstElementPointer;
	Allocator _allocator;
};

template<class Type, class Allocator = allocator<Type>>
List<Type, Allocator>::List(const Allocator& passedAllocator = Allocator())
{
	_firstElementPointer = nullptr;
	_allocator = passedAllocator;
}

template<class Type, class Allocator = allocator<Type>>
void List<Type, Allocator>::begin(void)
{

}

template<class Type, class Allocator = allocator<Type>>
void List<Type, Allocator>::push_front(const Type& value)
{
	if (_firstElementPointer == nullptr)
	{
		_firstElementPointer = shared_ptr <ListElement<Type>>(new ListElement<Type>(new Type(value)));
		return;
	}


}

#endif 
