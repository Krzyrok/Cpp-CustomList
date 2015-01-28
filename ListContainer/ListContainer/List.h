#ifndef LIST_HEADER
#define LIST_HEADER

#include "ListIterator.h"

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

	

	
	void clear(void)
	{
		_lastElementPointer.reset();
		_firstElementPointer.reset();
		_numberOfElements = 0;
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

	shared_ptr<ListElement<Type, Allocator>> createElementPtrAndChangeSize(const Type& value)
	{
		shared_ptr <ListElement<Type, Allocator>> result = shared_ptr <ListElement<Type, Allocator>>(new ListElement<Type, Allocator>(value, _allocator));
		_numberOfElements++;

		return result;
	}
};

#endif 
