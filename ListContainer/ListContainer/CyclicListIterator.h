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
	CyclicListIterator(bool isFirstIteration = false, bool isMadeByEndMethod = false)
		: ListIterator(), _isFirstIteration(isFirstIteration), _isMadeByEndMethod(isMadeByEndMethod){}


	CyclicListIterator(shared_ptr<ListElement<Type, Allocator>> ptr, bool isFirstIteration = false, bool isMadeByEndMethod = false)
		: ListIterator(ptr), _isFirstIteration(isFirstIteration), _isMadeByEndMethod(isMadeByEndMethod) {}

	CyclicListIterator(const CyclicListIterator& originalIterator, bool isFirstIteration = false, bool isMadeByEndMethod = false)
		: CyclicListIterator(originalIterator._pointer, isFirstIteration, isMadeByEndMethod) {}

	CyclicListIterator(const ListIterator& originalIterator, bool isFirstIteration = false, bool isMadeByEndMethod = false)
		: CyclicListIterator(originalIterator._pointer, isFirstIteration, isMadeByEndMethod) {}


	CyclicListIterator& operator++()
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
		bool result = (_pointer == secondIterator._pointer) && (!_isFirstIteration || !secondIterator._isFirstIteration)
			|| (_pointer == secondIterator._pointer) && (_isMadeByEndMethod == secondIterator._isMadeByEndMethod);
		return result;
	}

	bool operator!=(const CyclicListIterator& secondIterator)
	{
		return !(*this == secondIterator);
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
	ConstCyclicListIterator(bool isFirstIteration = false, bool isMadeByEndMethod = false)
		: ConstListIterator(), _isFirstIteration(isFirstIteration), _isMadeByEndMethod(isMadeByEndMethod) {}


	ConstCyclicListIterator(shared_ptr<ListElement<Type, Allocator>> ptr, bool isFirstIteration = false, bool isMadeByEndMethod = false)
		: ConstListIterator(ptr), _isFirstIteration(isFirstIteration), _isMadeByEndMethod(isMadeByEndMethod) {}

	ConstCyclicListIterator(const ConstCyclicListIterator& originalIterator, bool isFirstIteration = false, bool isMadeByEndMethod = false)
		: ConstCyclicListIterator(originalIterator._pointer, isFirstIteration, isMadeByEndMethod) {}

	ConstCyclicListIterator(const CyclicListIterator<Type, Allocator>& originalIterator, 
		bool isFirstIteration = false, bool isMadeByEndMethod = false)
		: ConstCyclicListIterator(originalIterator._pointer, isFirstIteration, isMadeByEndMethod) {}

	ConstCyclicListIterator(const ConstListIterator& originalIterator, bool isFirstIteration = false, bool isMadeByEndMethod = false)
		: ConstCyclicListIterator(originalIterator._pointer, isFirstIteration, isMadeByEndMethod) {}

	ConstCyclicListIterator(const ListIterator<Type, Allocator>& originalIterator, bool isFirstIteration = false, bool isMadeByEndMethod = false)
		: ConstCyclicListIterator(originalIterator._pointer, isFirstIteration, isMadeByEndMethod) {}


	ConstCyclicListIterator& operator++()
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
		bool result = (_pointer == secondIterator._pointer) && (!_isFirstIteration || !secondIterator._isFirstIteration)
			|| (_pointer == secondIterator._pointer) && (_isMadeByEndMethod == secondIterator._isMadeByEndMethod);
		return result;
	}

	bool operator!=(const ConstCyclicListIterator& secondIterator)
	{
		return !(*this == secondIterator);
	}

private:
	bool _isFirstIteration;
	bool _isMadeByEndMethod;
};

#endif
