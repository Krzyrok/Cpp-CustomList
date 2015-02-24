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
		_lastElementPointer = nullptr;
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

	List(const List& listToCopy, const Allocator& passedAlloc = Allocator())
		: List(listToCopy.begin(), listToCopy.end(), passedAlloc)
	{
	}

	List(List&& listToCopy, const Allocator& passedAlloc = Allocator())
		: List(passedAlloc)
	{
		swap(listToCopy);
	}

	List(initializer_list<value_type> listWithObjects, const Allocator& passedAlloc = Allocator())
		: List(listWithObjects.begin(), listWithObjects.end(), passedAlloc)
	{
	}


	// -------------------------------------------------------------------

	// Methods
	List& operator=(const List& otherList)
	{
		assign(otherList.begin(), otherList.end());
		return *this;
	}

	List& operator=(List&& otherList)
	{
		swap(otherList);
		return *this;
	}

	List& operator=(initializer_list<Type> listWithObjects)
	{
		assign(listWithObjects);
		return *this;
	}


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

	void assign(initializer_list<value_type> listWithValues)
	{
		assign(listWithValues.begin(), listWithValues.end());
	}

	template <class... Args>
	void emplace_front(Args&&... args)
	{
		if (checkIfEmptyAndPushElement(args...))
		{
			return;
		}

		shared_ptr<ListElement<Type, Allocator>> newElementPointer = createElementPtrAndChangeSize(args...);
		setFirstElementPointer(newElementPointer);
	}

	void push_front(const Type& value)
	{
		if (checkIfEmptyAndPushElement(value))
		{
			return;
		}

		shared_ptr<ListElement<Type, Allocator>> newElementPointer = createElementPtrAndChangeSize(value);
		setFirstElementPointer(newElementPointer);
	}

	void push_front(Type&& value)
	{
		push_front(value);
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

	template <class... Args>
	void emplace_back(Args&&... args)
	{
		if (checkIfEmptyAndPushElement(args...))
		{
			return;
		}

		shared_ptr<ListElement<Type, Allocator>> newElementPointer = createElementPtrAndChangeSize(args...);
		setLastElementPointer(newElementPointer);
	}

	void push_back(const Type& value)
	{
		if (checkIfEmptyAndPushElement(value))
		{
			return;
		}

		shared_ptr<ListElement<Type, Allocator>> newElementPointer = createElementPtrAndChangeSize(value);
		setLastElementPointer(newElementPointer);
	}

	void push_back(Type&& value)
	{
		push_back(value);
	}

	void pop_back(void)
	{
		if (checkIfEmptyOrOneElementAndDelete())
		{
			return;
		}

		shared_ptr<ListElement<Type, Allocator>> currentElement = findElementPointerBefore(_lastElementPointer);

		currentElement->NextElementPointer.reset();
		_lastElementPointer = currentElement;

		_numberOfElements--;
	}

	template <class... Args>
	iterator emplace(const_iterator positionIterator, Args&&... args)
	{
		if (positionIterator == cbegin())
		{
			emplace_front(args...);
			return begin();
		}
		else if (positionIterator == end())
		{
			emplace_back(args...);
			return iterator(_lastElementPointer);
		}

		shared_ptr<ListElement<Type, Allocator>> newElementPointer = createElementPtrAndChangeSize(args...);
		shared_ptr<ListElement<Type, Allocator>>& currentElementPointer = findElementPointer(positionIterator);
		insertNewElementPtr(currentElementPointer, newElementPointer);

		return iterator(currentElementPointer);
	}

	iterator insert(const_iterator positionIterator, const Type& value)
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

		shared_ptr<ListElement<Type, Allocator>> newElementPointer = createElementPtrAndChangeSize(value);
		shared_ptr<ListElement<Type, Allocator>>& currentElementPointer = findElementPointer(positionIterator);
		insertNewElementPtr(currentElementPointer, newElementPointer);

		return iterator(currentElementPointer);
	}

	iterator insert(const_iterator positionIterator, size_type numberOfValues, const Type& value)
	{
		if (numberOfValues < 1)
			return iterator(nullptr);

		List<Type, Allocator> listWithInsertingValues(numberOfValues, value, _allocator);
		insertFromOtherList(positionIterator, listWithInsertingValues);
		return iterator(listWithInsertingValues._firstElementPointer);
	}

	template <class InputIterator, class = typename enable_if<!is_fundamental<InputIterator>::value>::type>
	iterator insert(const_iterator positionIterator, InputIterator firstIterator, InputIterator lastIterator)
	{
		if (firstIterator == lastIterator)
			return iterator(nullptr);

		List<Type, Allocator> listWithInsertingValues(firstIterator, lastIterator, _allocator);
		insertFromOtherList(positionIterator, listWithInsertingValues);
		return iterator(listWithInsertingValues._firstElementPointer);
	}

	iterator insert(const_iterator positionIterator, Type&& value)
	{
		return insert(positionIterator, value);
	}

	iterator insert(const_iterator positionIterator, initializer_list<Type> listWithValues)
	{
		return insert(positionIterator, listWithValues.begin(), listWithValues.end());
	}

	iterator erase(const_iterator positionIterator)
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

		shared_ptr<ListElement<Type, Allocator>>& currentElementPointer = findElementPointer(positionIterator);
		if (currentElementPointer == _lastElementPointer)
		{
			pop_back();
			return end();
		}

		currentElementPointer = currentElementPointer->NextElementPointer;
		_numberOfElements--;
		return iterator(currentElementPointer);
	}

	iterator erase(const_iterator firstPosition, const_iterator lastPosition)
	{
		if (firstPosition == lastPosition)
			return nullptr;
		if (firstPosition == begin() && lastPosition == end())
		{
			clear();
			return nullptr;
		}
		int elementsNumberToErase = 0;

		shared_ptr<ListElement<Type, Allocator>>& firstElementPointerToErase = findElementPointer(firstPosition);
		shared_ptr<ListElement<Type, Allocator>> lastElementPointerToErase;

		if (lastPosition == end())
		{
			lastElementPointerToErase = _lastElementPointer;
			_lastElementPointer = findElementPointerBefore(firstPosition);
			elementsNumberToErase = countElementsNumberIncludingEndElements(firstElementPointerToErase, lastElementPointerToErase);
		}
		else
		{
			lastElementPointerToErase =
				findElementPointerBeforeFromStartPositionAndCountElements(firstElementPointerToErase, lastPosition, elementsNumberToErase);
		}

		firstElementPointerToErase = lastElementPointerToErase->NextElementPointer;
		_numberOfElements -= elementsNumberToErase;

		return iterator(firstElementPointerToErase);
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

	void resize(size_type newSize, const Type newValue = Type())
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
		if (empty())
			return;
		_lastElementPointer.reset();
		_firstElementPointer.reset();
		_numberOfElements = 0;
	}


	// Operations
	void splice(const_iterator positionIteratorForNewElements, List& otherList)
	{
		splice(positionIteratorForNewElements, otherList, otherList.begin(), otherList.end());
	}

	void splice(const_iterator positionIteratorForNewElements, List&& otherList)
	{
		splice(positionIteratorForNewElements, otherList);
	}

	void splice(const_iterator positionIteratorForNewElements, List& otherList, const_iterator positionIteratorInOtherList)
	{
		if (positionIteratorInOtherList == end())
			return;

		const_iterator lastIteratorInOtherList = positionIteratorInOtherList;
		lastIteratorInOtherList++;
		splice(positionIteratorForNewElements, otherList, positionIteratorInOtherList, lastIteratorInOtherList);
	}

	void splice(const_iterator positionIteratorForNewElements, List&& otherList, const_iterator positionIteratorInOtherList)
	{
		splice(positionIteratorForNewElements, otherList, positionIteratorInOtherList);
	}

	void splice(const_iterator positionIteratorForNewElements, List& otherList, 
		const_iterator firstIteratorInOtherList, const_iterator lastIteratorInOtherList)
	{
		if (firstIteratorInOtherList == lastIteratorInOtherList)
			return;

		insert(positionIteratorForNewElements, firstIteratorInOtherList, lastIteratorInOtherList);
		otherList.erase(firstIteratorInOtherList, lastIteratorInOtherList);
	}

	void splice(const_iterator positionIteratorForNewElements, List&& otherList,
		const_iterator firstIteratorInOtherList, const_iterator lastIteratorInOtherList)
	{
		splice(positionIteratorForNewElements, otherList, firstIteratorInOtherList, lastIteratorInOtherList);
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
		if (empty())
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

	void merge(List&& otherList)
	{
		merge(otherList);
	}

	template <class Compare>
	void merge(List& otherList, Compare compare)
	{
		if (this == &otherList)
			return;
		if (otherList.empty())
			return;

		List<Type> resultList;
		do
		{
			Type& valueFromFirstList = _firstElementPointer->GetValue();
			Type& valueFromSecondList = otherList._firstElementPointer->GetValue();
			if (compare(valueFromFirstList, valueFromSecondList))
			{
				resultList.push_back(valueFromFirstList);
				pop_front();
			}
			else
			{
				resultList.push_back(valueFromSecondList);
				otherList.pop_front();
			}
		}
		while (!empty() && !otherList.empty());

		if (!empty())
		{
			resultList.insert(resultList.end(), begin(), end());
		}
		else if (!otherList.empty())
		{
			resultList.insert(resultList.end(), otherList.begin(), otherList.end());
			otherList.clear();
		}

		assign(resultList.begin(), resultList.end());
	}

	template <class Compare>
	void merge(List&& otherList, Compare compare)
	{
		merge(otherList, compare);
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

		// buble sort
		size_type n = size();
		do
		{
			currentElementPointer = _firstElementPointer;
			nextElementPointer = _firstElementPointer->NextElementPointer;
			for (size_type i = 0; i < n - 1; i++)
			{
				if (compare(nextElementPointer->GetValue(), currentElementPointer->GetValue()))
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
						shared_ptr<ListElement<Type, Allocator>>& currentElementPointerInStructure = findElementPointer(currentElementPointer);
						currentElementPointerInStructure = nextElementPointer;

					}
					// move nextElement one position after currentElement 
					// (because currentElement is pointing to the next item in the row after changing places)
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
			// tmpPointer is essential to not lose pointer to the element after current element
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


protected:
	shared_ptr<ListElement<Type, Allocator>> _firstElementPointer;
	shared_ptr<ListElement<Type, Allocator>> _lastElementPointer;
	Allocator _allocator;
	size_type _numberOfElements;

	shared_ptr<ListElement<Type, Allocator>> findElementPointerBefore(const_iterator positionIterator)
	{
		shared_ptr<ListElement<Type, Allocator>> currentElement = _firstElementPointer;
		while (currentElement->NextElementPointer->ValuePointer.get() != (positionIterator.operator->()))
		{
			currentElement = currentElement->NextElementPointer;
		}

		return currentElement;
	}
	

private:
	void insertFromOtherList(const_iterator positionIterator, const List& listWithInsertingValues)
	{
		_numberOfElements += listWithInsertingValues.size();
		if (positionIterator == const_iterator(end()))
		{
			_lastElementPointer->NextElementPointer = listWithInsertingValues._firstElementPointer;
			_lastElementPointer = listWithInsertingValues._lastElementPointer;
			return;
		}

		shared_ptr<ListElement<Type, Allocator>>& currentElementPointer = findElementPointer(positionIterator);
		listWithInsertingValues._lastElementPointer->NextElementPointer = currentElementPointer;
		currentElementPointer = listWithInsertingValues._firstElementPointer;
	}

	template <class... Args>
	bool checkIfEmptyAndPushElement(Args&&... args)
	{
		if (size() == 0)
		{
			_firstElementPointer = createElementPtrAndChangeSize(args...);
			_lastElementPointer = _firstElementPointer;
			return true;
		}

		return false;
	}

	bool checkIfEmptyAndPushElement(const Type& value)
	{
		if (size() == 0)
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

	shared_ptr<ListElement<Type, Allocator>> findElementPointerBefore(shared_ptr<ListElement<Type, Allocator>> nextElementPointer)
	{
		return findElementPointerBefore(iterator(nextElementPointer));
	}

	shared_ptr<ListElement<Type, Allocator>>& findElementPointer(const_iterator positionIterator)
	{
		if (_firstElementPointer->ValuePointer.get() == positionIterator.operator->())
			return _firstElementPointer;

		shared_ptr<ListElement<Type, Allocator>> elementPointerBefore = findElementPointerBefore(positionIterator);
		return elementPointerBefore->NextElementPointer;
	}

	shared_ptr<ListElement<Type, Allocator>> findElementPointerBeforeFromStartPositionAndCountElements
		(shared_ptr<ListElement<Type, Allocator>>& startElementPointer, const_iterator endPositionIterator, int& elementsAmount)
	{
		shared_ptr<ListElement<Type, Allocator>> currentElementPointer = startElementPointer;
		elementsAmount = 1;
		while (currentElementPointer->NextElementPointer->ValuePointer.get() != (endPositionIterator.operator->()))
		{
			currentElementPointer = currentElementPointer->NextElementPointer;
			elementsAmount++;
		}

		return currentElementPointer;

	}

	int countElementsNumberIncludingEndElements(shared_ptr<ListElement<Type, Allocator>>& startElementPointer, 
		shared_ptr<ListElement<Type, Allocator>>& endElementPointer)
	{
		int result = 1;
		shared_ptr<ListElement<Type, Allocator>> currentElementPointer = startElementPointer;

		while (currentElementPointer != endElementPointer)
		{
			result++;
			currentElementPointer = currentElementPointer->NextElementPointer;
		}

		return result;
	}

	shared_ptr<ListElement<Type, Allocator>> createElementPtrAndChangeSize(const Type& value)
	{
		return createPtrForListElementPtrAndChangeSize(new ListElement<Type, Allocator>(_allocator, value));
	}

	template <class... Args>
	shared_ptr<ListElement<Type, Allocator>> createElementPtrAndChangeSize(Args&&... args)
	{
		return createPtrForListElementPtrAndChangeSize(new ListElement<Type, Allocator>(_allocator, args...));
	}

	inline shared_ptr<ListElement<Type, Allocator>> createPtrForListElementPtrAndChangeSize(ListElement<Type, Allocator>* listElementPointer)
	{
		shared_ptr <ListElement<Type, Allocator>> result = shared_ptr <ListElement<Type, Allocator>>(listElementPointer);
		_numberOfElements++;

		return result;
	}

	inline void setFirstElementPointer(shared_ptr<ListElement<Type, Allocator>>& elementPointer)
	{
		elementPointer->NextElementPointer = _firstElementPointer;
		_firstElementPointer = elementPointer;
	}

	inline void setLastElementPointer(shared_ptr<ListElement<Type, Allocator>>& elementPointer)
	{
		_lastElementPointer->NextElementPointer = elementPointer;
		_lastElementPointer = elementPointer;
	}

	inline void insertNewElementPtr(shared_ptr<ListElement<Type, Allocator>>& elementPointerBeforeShouldInsertNewElement,
		shared_ptr<ListElement<Type, Allocator>>& newElementPointer)
	{
		newElementPointer->NextElementPointer = elementPointerBeforeShouldInsertNewElement;
		elementPointerBeforeShouldInsertNewElement = newElementPointer;
	}
};

#endif 
