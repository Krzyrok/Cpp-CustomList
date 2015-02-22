#ifndef CYCLIC_LIST_ITERATOR_HEADER
#define CYCLIC_LIST_ITERATOR_HEADER

#include "ListIterator.h"

template <class Type, class Allocator>
class ConstCyclicListIterator;

template <class Type, class Allocator>
class CyclicListIterator
	: public ListIterator<Type, Allocator>
{
public:
	CyclicListIterator(void)
		: ListIterator(), _wasMovement(false) {}


	CyclicListIterator(shared_ptr<ListElement<Type, Allocator>> ptr)
		: ListIterator(ptr), _wasMovement(false) {}

	CyclicListIterator(const CyclicListIterator& originalIterator)
		: CyclicListIterator(originalIterator._pointer) {}

	CyclicListIterator(const ListIterator& originalIterator)
		: CyclicListIterator(originalIterator._pointer) {}


	CyclicListIterator operator++()
	{
		_pointer = _pointer->NextElementPointer;
		return *this;
	}

	CyclicListIterator operator++(int)
	{
		CyclicListIterator previousIterator = *this;
		_pointer = _pointer->NextElementPointer;
		return previousIterator;
	}

	bool operator==(const ListIterator& secondIterator)
	{
		return _pointer == secondIterator._pointer;
	}

	bool operator!=(const ListIterator& secondIterator)
	{
		return _pointer != secondIterator._pointer;
	}

	friend class ConstCyclicListIterator<Type, Allocator>;

private:
	bool _wasMovement;
};

template <class Type, class Allocator>
class ConstCyclicListIterator
	: public ConstListIterator<Type, Allocator>
{
public:
	ConstCyclicListIterator(void)
		: ConstListIterator(), _wasMovement(false) {}


	ConstCyclicListIterator(shared_ptr<ListElement<Type, Allocator>> ptr)
		: ConstListIterator(ptr), _wasMovement(false) {}

	ConstCyclicListIterator(const ConstCyclicListIterator& originalIterator)
		: ConstCyclicListIterator(originalIterator._pointer) {}

	ConstCyclicListIterator(const CyclicListIterator<Type, Allocator>& originalIterator)
		: ConstCyclicListIterator(originalIterator._pointer) {}

	ConstCyclicListIterator(const ConstListIterator& originalIterator)
		: ConstCyclicListIterator(originalIterator._pointer) {}

	ConstCyclicListIterator(const ListIterator<Type, Allocator>& originalIterator)
		: ConstCyclicListIterator(originalIterator._pointer) {}


	ConstCyclicListIterator operator++()
	{
		_pointer = _pointer->NextElementPointer;
		return *this;
	}

	ConstCyclicListIterator operator++(int)
	{
		ConstCyclicListIterator previousIterator = *this;
		_pointer = _pointer->NextElementPointer;
		return previousIterator;
	}

	bool operator==(const ConstCyclicListIterator& secondIterator)
	{
		return _pointer == secondIterator._pointer;
	}

	bool operator!=(const ConstCyclicListIterator& secondIterator)
	{
		return _pointer != secondIterator._pointer;
	}

private:
	bool _wasMovement;
};

#endif
