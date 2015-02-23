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
	CyclicListIterator(bool isMadeByEndMethod = false)
		: ListIterator(), _isFirstIteration(true), _isMadeByEndMethod(isMadeByEndMethod) {}


	CyclicListIterator(shared_ptr<ListElement<Type, Allocator>> ptr, bool isMadeByEndMethod = false)
		: ListIterator(ptr), _isFirstIteration(true), _isMadeByEndMethod(isMadeByEndMethod) {}

	CyclicListIterator(const CyclicListIterator& originalIterator, bool isMadeByEndMethod = false)
		: CyclicListIterator(originalIterator._pointer, isMadeByEndMethod) {}

	CyclicListIterator(const ListIterator& originalIterator, bool isMadeByEndMethod = false)
		: CyclicListIterator(originalIterator._pointer, isMadeByEndMethod) {}


	CyclicListIterator operator++()
	{
		_pointer = _pointer->NextElementPointer;
		_isFirstIteration = false;
		return *this;
	}

	CyclicListIterator operator++(int)
	{
		CyclicListIterator previousIterator = *this;
		_pointer = _pointer->NextElementPointer;
		_isFirstIteration = false;
		return previousIterator;
	}

	bool operator==(const CyclicListIterator& secondIterator)
	{
		bool result = (_pointer == secondIterator._pointer) && (!_isFirstIteration || !secondIterator._isFirstIteration);
		return result;
	}

	bool operator!=(const CyclicListIterator& secondIterator)
	{
		return !(_pointer == secondIterator._pointer);
	}

	friend class ConstCyclicListIterator<Type, Allocator>;

private:
	bool _isFirstIteration;
	bool _isMadeByEndMethod;
};

template <class Type, class Allocator>
class ConstCyclicListIterator
	: public ConstListIterator<Type, Allocator>
{
public:
	ConstCyclicListIterator(bool isMadeByEndMethod = false)
		: ConstListIterator(), _isFirstIteration(true), _isMadeByEndMethod(isMadeByEndMethod) {}


	ConstCyclicListIterator(shared_ptr<ListElement<Type, Allocator>> ptr, bool isMadeByEndMethod = false)
		: ConstListIterator(ptr), _isFirstIteration(true), _isMadeByEndMethod(isMadeByEndMethod) {}

	ConstCyclicListIterator(const ConstCyclicListIterator& originalIterator, bool isMadeByEndMethod = false)
		: ConstCyclicListIterator(originalIterator._pointer, isMadeByEndMethod) {}

	ConstCyclicListIterator(const CyclicListIterator<Type, Allocator>& originalIterator, bool isMadeByEndMethod = false)
		: ConstCyclicListIterator(originalIterator._pointer, isMadeByEndMethod) {}

	ConstCyclicListIterator(const ConstListIterator& originalIterator, bool isMadeByEndMethod = false)
		: ConstCyclicListIterator(originalIterator._pointer, isMadeByEndMethod) {}

	ConstCyclicListIterator(const ListIterator<Type, Allocator>& originalIterator, bool isMadeByEndMethod = false)
		: ConstCyclicListIterator(originalIterator._pointer, isMadeByEndMethod) {}


	ConstCyclicListIterator operator++()
	{
		_pointer = _pointer->NextElementPointer;
		_isFirstIteration = false;
		return *this;
	}

	ConstCyclicListIterator operator++(int)
	{
		ConstCyclicListIterator previousIterator = *this;
		_pointer = _pointer->NextElementPointer;
		_isFirstIteration = false;
		return previousIterator;
	}

	bool operator==(const ConstCyclicListIterator& secondIterator)
	{
		bool result = (_pointer == secondIterator._pointer) && (!_isFirstIteration || !secondIterator._isFirstIteration);
		return result;
	}

	bool operator!=(const ConstCyclicListIterator& secondIterator)
	{
		return !(_pointer == secondIterator._pointer);
	}

private:
	bool _isFirstIteration;
	bool _isMadeByEndMethod;
};

#endif
