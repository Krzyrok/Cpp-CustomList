#ifndef LIST_HEADER
#define LIST_HEADER

#include "ListIterator.h"

#include <xmemory0>

template<class Type, class Allocator = allocator<Type>>
class List
{
public:
	typedef size_t size_type;
	typedef typename ListIterator<Type, false> Iterator;
	typedef typename ListIterator<Type, true> Const_Iterator;

	// Constructor
	List(const Allocator& passedAlloc = Allocator())
	{
		_firstElementPointer = nullptr;
		_allocator = passedAlloc;
		_numberOfElements = 0;
	}

	// methods
	Iterator begin(void)
	{
		return Iterator(_firstElementPointer);
	}

	Const_Iterator begin(void) const
	{
		return Const_Iterator(_firstElementPointer);
	}

	void push_back(const Type& value)
	{
		if (tryToPushOnFirstPosition(value))
		{
			return;
		}

		shared_ptr<ListElement<Type>> previousElement = _firstElementPointer;
		shared_ptr<ListElement<Type>> currentElement = _firstElementPointer->NextElementPointer;
		while (currentElement != nullptr)
		{
			previousElement = currentElement;
			currentElement = currentElement->NextElementPointer;
		}

		previousElement->NextElementPointer = shared_ptr <ListElement<Type>>(new ListElement<Type>(new Type(value)));
		_numberOfElements++;
	}

	void push_front(const Type& value)
	{
		if (tryToPushOnFirstPosition(value))
		{
			return;
		}

		shared_ptr<ListElement<Type>> newFirstElement = shared_ptr <ListElement<Type>>(new ListElement<Type>(new Type(value)));
		newFirstElement->NextElementPointer = _firstElementPointer;
		_firstElementPointer = newFirstElement;
		_numberOfElements++;
	}

	size_type size(void) const
	{
		return _numberOfElements;
	}

private:
	shared_ptr<ListElement<Type>> _firstElementPointer;
	Allocator _allocator;
	size_type _numberOfElements;


	bool tryToPushOnFirstPosition(const Type& value)
	{
		if (_firstElementPointer == nullptr)
		{
			_firstElementPointer = shared_ptr <ListElement<Type>>(new ListElement<Type>(new Type(value)));
			_numberOfElements++;
			return true;
		}

		return false;
	}
};

#endif 
