#ifndef LIST_HEADER
#define LIST_HEADER

#include "ListIterator.h"
#include "Functor.h"
#include "BinaryFunctor.h"
#include "CompareFunctor.h"

#include <xmemory0>

template<class Type, class Allocator = allocator<Type>>
class List
{
public:
	typedef typename ListIterator<Type, Allocator> iterator;
	typedef typename ConstListIterator<Type, Allocator> const_iterator;

	typedef Type value_type;
	typedef Allocator allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef typename iterator_traits<iterator>::difference_type difference_type;
	typedef size_t size_type;


	// Constructors
	explicit List(const Allocator& passedAlloc = Allocator())
	{
		_firstElementPointer = nullptr;
		_allocator = passedAlloc;
		_numberOfElements = 0;
	}

	explicit List(size_type numberOfElements, const Type& value = Type(), const Allocator& passedAlloc = Allocator())
		: List(passedAlloc)
	{
		assign(numberOfElements, value);
	}

	template <class InputIterator, class = typename enable_if<!is_fundamental<InputIterator>::value>::type>
	List(InputIterator firstIterator, InputIterator lastIterator, const Allocator& passedAlloc = Allocator())
		: List(passedAlloc)
	{
		assign(firstIterator, lastIterator);
	}

	List(const List& listToCopy)
		: List(listToCopy.begin(), listToCopy.end())
	{
	}

	// -------------------------------------------------------------------

	// Methods

	// Iterators
	iterator begin(void)
	{
		return iterator(_firstElementPointer);
	}

	const_iterator begin(void) const
	{
		return cbegin();
	}

	iterator end(void)
	{
		return iterator(nullptr);
	}

	const_iterator end(void) const
	{
		return cend();
	}

	const_iterator cbegin(void) const
	{
		return const_iterator(_firstElementPointer);
	}

	const_iterator cend(void) const
	{
		return const_iterator(nullptr);
	}


	// Capacity
	bool empty(void) const
	{
		return (size() == 0);
	}

	size_type size(void) const
	{
		return _numberOfElements;
	}

	size_type max_size(void) const
	{
		return _allocator.max_size();
	}


	// Element access
	reference front(void)
	{
		return _firstElementPointer->GetValue();
	}

	const_reference front(void) const
	{
		return _firstElementPointer->GetValue();
	}

	reference back(void)
	{
		return _lastElementPointer->GetValue();
	}

	const_reference back(void) const
	{
		return _lastElementPointer->GetValue();
	}


	// Modifiers
	template <class InputIterator, class = typename enable_if<!is_fundamental<InputIterator>::value>::type>
	void assign(InputIterator firstIterator, InputIterator lastIterator)
	{
		clear();

		if (firstIterator == lastIterator)
			return;

		InputIterator currentIterator = firstIterator;

		_firstElementPointer = createElementPtrAndChangeSize(*currentIterator);
		shared_ptr<ListElement<Type, Allocator>> currentElement = _firstElementPointer;
		currentIterator++;
		for (; currentIterator != lastIterator; currentIterator++)
		{
			currentElement->NextElementPointer = createElementPtrAndChangeSize(*currentIterator);
			currentElement = currentElement->NextElementPointer;
		}

		_lastElementPointer = currentElement;
	}

	void assign(size_type numberOfElements, const Type& value)
	{
		clear();
		if (numberOfElements <= 0)
			return;

		_firstElementPointer = createElementPtrAndChangeSize(value);
		shared_ptr<ListElement<Type, Allocator>> currentElement = _firstElementPointer;
		for (size_type i = 1; i < numberOfElements; i++)
		{
			currentElement->NextElementPointer = createElementPtrAndChangeSize(value);
			currentElement = currentElement->NextElementPointer;
		}

		_lastElementPointer = currentElement;
	}

	void push_front(const Type& value)
	{
		if (checkIfEmptyAndPushElement(value))
		{
			return;
		}

		shared_ptr<ListElement<Type, Allocator>> newFirstElement = createElementPtrAndChangeSize(value);
		newFirstElement->NextElementPointer = _firstElementPointer;
		_firstElementPointer = newFirstElement;
	}

	void pop_front(void)
	{
		if (checkIfEmptyOrOneElementAndDelete())
		{
			return;
		}
		_firstElementPointer = _firstElementPointer->NextElementPointer;
		_numberOfElements--;
	}

	void push_back(const Type& value)
	{
		if (checkIfEmptyAndPushElement(value))
		{
			return;
		}

		_lastElementPointer->NextElementPointer = createElementPtrAndChangeSize(value);
		_lastElementPointer = _lastElementPointer->NextElementPointer;
	}

	void pop_back(void)
	{
		if (checkIfEmptyOrOneElementAndDelete())
		{
			return;
		}

		shared_ptr<ListElement<Type, Allocator>> currentElement = findElementBefore(_lastElementPointer);

		currentElement->NextElementPointer.reset();
		_lastElementPointer = currentElement;

		_numberOfElements--;
	}

	iterator insert(iterator positionIterator, const Type& value)
	{
		if (positionIterator == begin())
		{
			push_front(value);
			return begin();
		}
		else if (positionIterator == end())
		{
			push_back(value);
			return iterator(_lastElementPointer);
		}

		shared_ptr<ListElement<Type, Allocator>> elementBefore = findElementBefore(positionIterator);
		shared_ptr<ListElement<Type, Allocator>> newElement = createElementPtrAndChangeSize(value);
		newElement->NextElementPointer = elementBefore->NextElementPointer;
		elementBefore->NextElementPointer = newElement;

		return iterator(newElement);
	}

	void insert(iterator positionIterator, size_type numberOfValues, const Type& value)
	{
		for (size_type i = 0; i < numberOfValues; i++)
		{
			insert(positionIterator, value);
		}
	}

	template <class InputIterator, class = typename enable_if<!is_fundamental<InputIterator>::value>::type>
	void insert(iterator positionIterator, InputIterator firstIterator, InputIterator lastIterator)
	{
		if (firstIterator == lastIterator)
			return;

		for (InputIterator currentIterator = firstIterator; currentIterator != lastIterator; currentIterator++)
		{
			insert(positionIterator, *currentIterator);
		}
	}

	iterator erase(iterator positionIterator)
	{
		if (positionIterator == begin())
		{
			pop_front();
			return begin();
		}
		else if (positionIterator == end())
		{
			return nullptr;
		}

		shared_ptr<ListElement<Type, Allocator>> elementBefore = findElementBefore(positionIterator);
		if (elementBefore->NextElementPointer == _lastElementPointer)
		{
			pop_back();
			return end();
		}

		elementBefore->NextElementPointer = elementBefore->NextElementPointer->NextElementPointer;
		_numberOfElements--;
		return iterator(elementBefore->NextElementPointer);
	}

	iterator erase(iterator firstPosition, iterator lastPosition)
	{
		if (firstPosition == lastPosition)
			return nullptr;
		
		iterator result;

		for (iterator currentIterator = firstPosition; currentIterator != lastPosition; currentIterator++)
		{
			result = erase(currentIterator);
		}


		return result;
	}

	void swap(List& otherList)
	{
		shared_ptr <ListElement<Type, Allocator>> tmpPointer = _firstElementPointer;
		_firstElementPointer = otherList._firstElementPointer;
		otherList._firstElementPointer = tmpPointer;

		tmpPointer = _lastElementPointer;
		_lastElementPointer = otherList._lastElementPointer;
		otherList._lastElementPointer = tmpPointer;

		Allocator tmpAllocator = _allocator;
		_allocator = otherList._allocator;
		otherList._allocator = tmpAllocator;

		size_type tmpNumberOfElements = _numberOfElements;
		_numberOfElements = otherList._numberOfElements;
		otherList._numberOfElements = tmpNumberOfElements;
	}

	void resize(size_type newSize, Type newValue = Type())
	{
		if (newSize < 0)
			return;

		if (newSize == 0)
		{
			clear();
		}

		if (newSize > size())
		{
			size_type initialSize = size();
			for (size_type i = 0; i < newSize - initialSize; i++)
			{
				push_back(newValue);
			}
		}
		else if (newSize < size())
		{
			shared_ptr <ListElement<Type, Allocator>> currentElementPointer = _firstElementPointer;
			for (size_type i = 1; i < newSize; i++)
			{
				currentElementPointer = currentElementPointer->NextElementPointer;
			}

			currentElementPointer->NextElementPointer.reset();
			_lastElementPointer = currentElementPointer;
		}

		_numberOfElements = newSize;
	}
	
	void clear(void)
	{
		_lastElementPointer.reset();
		_firstElementPointer.reset();
		_numberOfElements = 0;
	}


	// Operations
	void splice(iterator positionIteratorForNewElements, List& otherList)
	{
		splice(positionIteratorForNewElements, otherList, otherList.begin(), otherList.end());
	}

	void splice(iterator positionIteratorForNewElements, List& otherList, iterator positionIteratorInOtherList)
	{
		if (positionIteratorInOtherList == end())
			return;

		iterator lastIteratorInOtherList = positionIteratorInOtherList;
		lastIteratorInOtherList++;
		splice(positionIteratorForNewElements, otherList, positionIteratorInOtherList, lastIteratorInOtherList);
	}

	void splice(iterator positionIteratorForNewElements, List& otherList, iterator firstIteratorInOtherList, iterator lastIteratorInOtherList)
	{
		if (firstIteratorInOtherList == lastIteratorInOtherList)
			return;

		insert(positionIteratorForNewElements, firstIteratorInOtherList, lastIteratorInOtherList);
		otherList.erase(firstIteratorInOtherList, lastIteratorInOtherList);
	}

	void remove(const Type& value)
	{
		IsEqual<Type> predicate;
		predicate.SetComparingValue(value);
		remove_if(predicate);
	}

	template <class Predicate>
	void remove_if(Predicate predicate)
	{
		if (size() < 1)
			return;

		for (iterator listIterator = begin(); listIterator != end(); listIterator++)
		{
			if (predicate(*listIterator))
			{
				erase(listIterator);
			}
		}
	}

	void unique(void)
	{
		unique(BinaryIsEqual<Type>());
	}

	template <class BinaryPredicate>
	void unique(BinaryPredicate binaryPredicate)
	{
		if (size() < 2)
			return;

		for (iterator firstIterator = begin(), secondIterator = (++begin()); secondIterator != end(); firstIterator++, secondIterator++)
		{
			if (binaryPredicate(*secondIterator, *firstIterator))
			{
				erase(firstIterator);
			}
		}
	}

	void merge(List& otherList)
	{
		merge(otherList, FirstSmallerThanSecond<Type>());
	}

	template <class Compare>
	void merge(List& otherList, Compare compare)
	{
		if (this == &otherList)
			return;
		if (otherList.size() < 1)
			return;


	}

	void sort(void)
	{
		sort(FirstSmallerThanSecond<Type>());
	}

	template <class Compare>
	void sort(Compare compare)
	{
		if (size() < 2)
			return;

		shared_ptr<ListElement<Type, Allocator>> currentElementPointer;
		shared_ptr<ListElement<Type, Allocator>> nextElementPointer;


		size_type n = size();
		do
		{
			currentElementPointer = _firstElementPointer;
			nextElementPointer = _firstElementPointer->NextElementPointer;
			for (size_type i = 0; i < n - 1; i++)
			{
				if (!compare(currentElementPointer->GetValue(), nextElementPointer->GetValue()))
				{
					shared_ptr<ListElement<Type, Allocator>> afterNextPointer = nextElementPointer->NextElementPointer;
					nextElementPointer->NextElementPointer = currentElementPointer;
					currentElementPointer->NextElementPointer = afterNextPointer;
					if (i == 0)
					{
						_firstElementPointer = nextElementPointer;
					}
					else
					{
						shared_ptr<ListElement<Type, Allocator>> previousPointer = findElementBefore(currentElementPointer);
						previousPointer->NextElementPointer = nextElementPointer;

					}
					nextElementPointer = currentElementPointer->NextElementPointer;
				}
				else
				{
					currentElementPointer = currentElementPointer->NextElementPointer;
					nextElementPointer = nextElementPointer->NextElementPointer;
				}
			}
			n--;
		}
		while (n > 1);
			
	}

	void reverse(void)
	{
		if (size() < 2)
			return;

		shared_ptr<ListElement<Type, Allocator>> previousPointer = _firstElementPointer;
		shared_ptr<ListElement<Type, Allocator>> currentPointer = _firstElementPointer->NextElementPointer;
		_firstElementPointer->NextElementPointer = nullptr;
		
		shared_ptr<ListElement<Type, Allocator>> tmpPointer;
		for (size_type i = 1; i < size(); i++)
		{
			tmpPointer = currentPointer->NextElementPointer;
			currentPointer->NextElementPointer = previousPointer;
			previousPointer = currentPointer;
			currentPointer = tmpPointer;
		}

		tmpPointer = _firstElementPointer;
		_firstElementPointer = _lastElementPointer;
		_lastElementPointer = tmpPointer;
	}


	// Observers
	allocator_type get_allocator(void) const
	{
		return _allocator;
	}

private:
	shared_ptr<ListElement<Type, Allocator>> _firstElementPointer;
	shared_ptr<ListElement<Type, Allocator>> _lastElementPointer;
	Allocator _allocator;
	size_type _numberOfElements;


	bool checkIfEmptyAndPushElement(const Type& value)
	{
		if (_firstElementPointer == nullptr)
		{
			_firstElementPointer = createElementPtrAndChangeSize(value);
			_lastElementPointer = _firstElementPointer;
			return true;
		}

		return false;
	}

	bool checkIfEmptyOrOneElementAndDelete(void)
	{
		if (size() == 0)
		{
			return true;
		}
		else if (size() == 1)
		{
			clear();
			return true;
		}

		return false;
	}

	shared_ptr<ListElement<Type, Allocator>> findElementBefore(shared_ptr<ListElement<Type, Allocator>> nextPointer)
	{
		return findElementBefore(iterator(nextPointer));
	}

	shared_ptr<ListElement<Type, Allocator>> findElementBefore(iterator positionIterator)
	{
		shared_ptr<ListElement<Type, Allocator>> currentElement = _firstElementPointer;
		while (currentElement->NextElementPointer->ValuePointer.get() != (positionIterator.operator->()))
		{
			currentElement = currentElement->NextElementPointer;
		}

		return currentElement;
	}

	shared_ptr<ListElement<Type, Allocator>> findElement(iterator positionIterator)
	{
		shared_ptr<ListElement<Type, Allocator>> currentElement = _firstElementPointer;
		while (currentElement->ValuePointer.get() != (positionIterator.operator->()))
		{
			currentElement = currentElement->NextElementPointer;
		}

		return currentElement;
	}

	shared_ptr<ListElement<Type, Allocator>> createElementPtrAndChangeSize(const Type& value)
	{
		shared_ptr <ListElement<Type, Allocator>> result = shared_ptr <ListElement<Type, Allocator>>(new ListElement<Type, Allocator>(value, _allocator));
		_numberOfElements++;

		return result;
	}
};

#endif 
