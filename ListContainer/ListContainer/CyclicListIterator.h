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
	CyclicListIterator(bool isMadeByBeginMethod = false, bool isMadeByEndMethod = false)
		: ListIterator(), _isMadeByBeginMethod(isMadeByBeginMethod), _isMadeByEndMethod(isMadeByEndMethod), _isFirstIteration(true) {}


	CyclicListIterator(shared_ptr<ListElement<Type, Allocator>> ptr, bool isMadeByBeginMethod = false, bool isMadeByEndMethod = false)
		: ListIterator(ptr), _isMadeByBeginMethod(isMadeByBeginMethod), _isMadeByEndMethod(isMadeByEndMethod), _isFirstIteration(true) {}

	CyclicListIterator(const CyclicListIterator& originalIterator)
		: CyclicListIterator(originalIterator._pointer, originalIterator._isMadeByBeginMethod, originalIterator._isMadeByEndMethod) {}

	CyclicListIterator(const ListIterator& originalIterator, bool isMadeByBeginMethod = false, bool isMadeByEndMethod = false)
		: CyclicListIterator(originalIterator._pointer, isMadeByBeginMethod, isMadeByEndMethod) {}


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
		bool result = (_pointer == nullptr && secondIterator._pointer == nullptr)
			|| (_pointer == secondIterator._pointer)
			&& ((!_isFirstIteration || !secondIterator._isFirstIteration)
				|| (_isMadeByBeginMethod == secondIterator._isMadeByBeginMethod == true)
				|| (_isMadeByEndMethod == secondIterator._isMadeByEndMethod == true));
		return result;
	}

	bool operator!=(const CyclicListIterator& secondIterator)
	{
		return !(*this == secondIterator);
	}

	friend class ConstCyclicListIterator<Type, Allocator>;

private:
	bool _isMadeByBeginMethod;
	bool _isMadeByEndMethod;
	bool _isFirstIteration;
};

template <class Type, class Allocator>
class ConstCyclicListIterator
	: public ConstListIterator<Type, Allocator>
{
public:
	ConstCyclicListIterator(bool isMadeByBeginMethod = false, bool isMadeByEndMethod = false)
		: ConstListIterator(), _isMadeByBeginMethod(isMadeByBeginMethod), _isMadeByEndMethod(isMadeByEndMethod), _isFirstIteration(true) {}


	ConstCyclicListIterator(shared_ptr<ListElement<Type, Allocator>> ptr, bool isMadeByBeginMethod = false, bool isMadeByEndMethod = false)
		: ConstListIterator(ptr), _isMadeByBeginMethod(isMadeByBeginMethod), _isMadeByEndMethod(isMadeByEndMethod), _isFirstIteration(true) {}

	ConstCyclicListIterator(const ConstCyclicListIterator& originalIterator)
		: ConstCyclicListIterator(originalIterator._pointer, originalIterator._isMadeByBeginMethod, originalIterator._isMadeByEndMethod) {}

	ConstCyclicListIterator(const CyclicListIterator<Type, Allocator>& originalIterator)
		: ConstCyclicListIterator(originalIterator._pointer, originalIterator._isMadeByBeginMethod, originalIterator._isMadeByEndMethod) {}

	ConstCyclicListIterator(const ConstListIterator& originalIterator, bool isMadeByBeginMethod = false, bool isMadeByEndMethod = false)
		: ConstCyclicListIterator(originalIterator._pointer, isMadeByBeginMethod, isMadeByEndMethod) {}

	ConstCyclicListIterator(const ListIterator<Type, Allocator>& originalIterator, bool isMadeByBeginMethod = false, bool isMadeByEndMethod = false)
		: ConstCyclicListIterator(originalIterator._pointer, isMadeByBeginMethod, isMadeByEndMethod) {}


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
		bool result = (_pointer == nullptr && secondIterator._pointer == nullptr)
			|| (_pointer == secondIterator._pointer) 
			&& ((!_isFirstIteration || !secondIterator._isFirstIteration)
				|| (_isMadeByBeginMethod == secondIterator._isMadeByBeginMethod == true)
				|| (_isMadeByEndMethod == secondIterator._isMadeByEndMethod == true));
		return result;
	}

	bool operator!=(const ConstCyclicListIterator& secondIterator)
	{
		return !(*this == secondIterator);
	}

private:
	bool _isMadeByBeginMethod;
	bool _isMadeByEndMethod;
	bool _isFirstIteration;
};

#endif
