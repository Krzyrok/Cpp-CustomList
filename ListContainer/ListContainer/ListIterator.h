#ifndef LIST_ITERATOR_HEADER
#define LIST_ITERATOR_HEADER

#include "ListElement.h"

#include <iterator>

template <class Type>
class ListIterator 
	: public iterator<forward_iterator_tag, ListElement<Type>, ptrdiff_t, ListElement<Type>*, ListElement<Type>&>
{
public:
	ListIterator(shared_ptr<ListElement<Type>> ptr) 
		: _pointer(ptr) 
	{
	}

	ListIterator operator++() 
	{  
		_pointer = _pointer->NextElementPointer;
		return *this;
	}

	ListIterator operator++(int) 
	{ 
		ListIterator previousIterator = *this;
		_pointer = _pointer->NextElementPointer;
		return previousIterator;
	}

	Type& operator*()
	{ 
		return _pointer->GetValue();
	}

	Type* operator->()
	{ 
		return &(_pointer->GetValue());
	}

	bool operator==(const ListIterator& secondIterator)
	{ 
		return _pointer == secondIterator._pointer;
	}

	bool operator!=(const ListIterator& secondIterator)
	{ 
		return _pointer != secondIterator._pointer;
	}


private:
	shared_ptr<ListElement<Type>> _pointer;
};

#endif
