#ifndef LIST_HEADER
#define LIST_HEADER

#include "ListIterator.h"

#include <xmemory0>

template<class Type, class Allocator = allocator<Type>>
class List
{
public:
	typedef typename ListIterator<Type> iterator;
	typedef typename ConstListIterator<Type> const_iterator;

	typedef Type value_type;
	typedef Allocator allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef typename iterator_traits<iterator>::difference_type difference_type;
	typedef size_t size_type;


	// Constructor
	List(const Allocator& passedAlloc = Allocator())
	{
		_firstElementPointer = nullptr;
		_allocator = passedAlloc;
		_numberOfElements = 0;
	}

	// methods
	iterator begin(void)
	{
		return iterator(_firstElementPointer);
	}

	const_iterator begin(void) const
	{
		return const_iterator(_firstElementPointer);
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
