#ifndef LIST_ITERATOR_HEADER
#define LIST_ITERATOR_HEADER

#include "ListElement.h"

#include <iterator>

template <class Type, class Allocator>
class ConstListIterator;


template <class Type, class Allocator>
class ListIterator 
	: public iterator<forward_iterator_tag, Type>
{
public:
	ListIterator(void)
		: _pointer(nullptr) {}


	ListIterator(shared_ptr<ListElement<Type, Allocator>> ptr)
		: _pointer(ptr) {}

	ListIterator(const ListIterator &originalIterator)
		: _pointer(originalIterator._pointer) {}

	ListIterator& operator++() 
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


protected:
	shared_ptr<ListElement<Type, Allocator>> _pointer;


private:
	friend class ConstListIterator<Type, Allocator>;
	
	template<class TypeForCLI, class TypeForA>
	friend class CyclicListIterator;

	template<class TypeForCCLI, class TypeForA>
	friend class ConstCyclicListIterator;
};

template <class Type, class Allocator>
class ConstListIterator
	: public iterator<forward_iterator_tag, const Type>
{
public:
	ConstListIterator(void)
		: _pointer(nullptr) {}


	ConstListIterator(shared_ptr<ListElement<Type, Allocator>> ptr)
		: _pointer(ptr) {}

	ConstListIterator(const ConstListIterator &originalIterator)
		: _pointer(originalIterator._pointer) {}

	ConstListIterator(const ListIterator<Type, Allocator> &originalIterator)
		: _pointer(originalIterator._pointer) {}

	ConstListIterator& operator++()
	{
		_pointer = _pointer->NextElementPointer;
		return *this;
	}

	ConstListIterator operator++(int)
	{
		ConstListIterator previousIterator = *this;
		_pointer = _pointer->NextElementPointer;
		return previousIterator;
	}

	const Type& operator*() const
	{
		return _pointer->GetValue();
	}

	const Type* operator->() const
	{
		return &(_pointer->GetValue());
	}

	bool operator==(const ConstListIterator& secondIterator)
	{
		return _pointer == secondIterator._pointer;
	}

	bool operator!=(const ConstListIterator& secondIterator)
	{
		return _pointer != secondIterator._pointer;
	}


protected:
	shared_ptr<ListElement<Type, Allocator>> _pointer;


private:
	template<class TypeForCCLI, class TypeForA>
	friend class ConstCyclicListIterator;
};

#endif
