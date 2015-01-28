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

	explicit List(size_type n, const Type& value = Type(), const Allocator& passedAlloc = Allocator())
		: List(passedAlloc)
	{
		if (n <= 0)
			return;

		_firstElementPointer = createElementPtrAndChangeSize(value);
		shared_ptr<ListElement<Type, Allocator>> currentElement = _firstElementPointer;
		for (size_type i = 1; i < n; i++)
		{
			currentElement->NextElementPointer = createElementPtrAndChangeSize(value);
			currentElement = currentElement->NextElementPointer;
		}
	}

	template <class InputIterator, class = typename enable_if<!is_fundamental<InputIterator>::value>::type>
	List(InputIterator firstIterator, InputIterator lastIterator, const Allocator& passedAlloc = Allocator())
		: List(passedAlloc)
	{
		if (firstIterator == lastIterator)
			return;

		InputIterator currentIterator = firstIterator;

		Type& value = (*currentIterator);
		_firstElementPointer = createElementPtrAndChangeSize(value);
		shared_ptr<ListElement<Type, Allocator>> currentElement = _firstElementPointer;
		currentIterator++;
		for (; currentIterator != lastIterator; currentIterator++)
		{
			value = *currentIterator;
			currentElement->NextElementPointer = createElementPtrAndChangeSize(value);
			currentElement = currentElement->NextElementPointer;
		}
	}

	// Methods
	iterator begin(void)
	{
		return iterator(_firstElementPointer);
	}

	const_iterator begin(void) const
	{
		return const_iterator(_firstElementPointer);
	}

	iterator end(void)
	{
		return iterator(nullptr);
	}

	const_iterator end(void) const
	{
		return const_iterator(nullptr);
	}


	size_type size(void) const
	{
		return _numberOfElements;
	}


	void push_back(const Type& value)
	{
		if (tryToPushOnFirstPosition(value))
		{
			return;
		}

		shared_ptr<ListElement<Type, Allocator>> previousElement = _firstElementPointer;
		shared_ptr<ListElement<Type, Allocator>> currentElement = _firstElementPointer->NextElementPointer;
		while (currentElement != nullptr)
		{
			previousElement = currentElement;
			currentElement = currentElement->NextElementPointer;
		}

		previousElement->NextElementPointer = createElementPtrAndChangeSize(value);
	}

	void push_front(const Type& value)
	{
		if (tryToPushOnFirstPosition(value))
		{
			return;
		}

		shared_ptr<ListElement<Type, Allocator>> newFirstElement = createElementPtrAndChangeSize(value);
		newFirstElement->NextElementPointer = _firstElementPointer;
		_firstElementPointer = newFirstElement;
	}

	
	void clear(void)
	{
		_firstElementPointer.reset();
		_numberOfElements = 0;
	}

private:
	shared_ptr<ListElement<Type, Allocator>> _firstElementPointer;
	Allocator _allocator;
	size_type _numberOfElements;


	bool tryToPushOnFirstPosition(const Type& value)
	{
		if (_firstElementPointer == nullptr)
		{
			_firstElementPointer = createElementPtrAndChangeSize(value);
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
