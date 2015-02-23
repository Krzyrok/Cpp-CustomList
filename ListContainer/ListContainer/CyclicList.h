#ifndef CYCLIC_LIST_HEADER
#define CYCLIC_LIST_HEADER

#include "List.h"
#include "CyclicListIterator.h"

template<class Type, class Allocator = allocator<Type>>
class CyclicList
	: public List<Type, Allocator>
{
public:
	typedef typename CyclicListIterator<Type, Allocator> iterator;
	typedef typename ConstCyclicListIterator<Type, Allocator> const_iterator;


	// Constructors
	explicit CyclicList(const Allocator& passedAlloc = Allocator())
		: List(passedAlloc)
	{
	}

	explicit CyclicList(size_type numberOfElements, const Type& value = Type(), const Allocator& passedAlloc = Allocator())
		: CyclicList(passedAlloc)
	{
		assign(numberOfElements, value);
	}

	template <class InputIterator, class = typename enable_if<!is_fundamental<InputIterator>::value>::type>
	CyclicList(InputIterator firstIterator, InputIterator lastIterator, const Allocator& passedAlloc = Allocator())
		: CyclicList(passedAlloc)
	{
		assign(firstIterator, lastIterator);
	}

	CyclicList(const CyclicList& listToCopy)
		: CyclicList(listToCopy.begin(), listToCopy.end())
	{
	}

	// -------------------------------------------------------------------

	// Methods

	// Iterators


	// Modifiers
	template <class InputIterator, class = typename enable_if<!is_fundamental<InputIterator>::value>::type>
	void assign(InputIterator firstIterator, InputIterator lastIterator)
	{
		if (firstIterator == lastIterator)
		{
			clear();
			return;
		}

		createNonCyclicList();
		List<Type, Allocator>::assign(firstIterator, lastIterator);

		createCyclicList();
	}

	void assign(size_type numberOfElements, const Type& value)
	{
		if (numberOfElements < 1)
		{
			clear();
			return;
		}

		createNonCyclicList();
		List<Type, Allocator>::assign(numberOfElements, value);
		
		createCyclicList();
	}

	void push_front(const Type& value)
	{
		List<Type, Allocator>::push_front(value);
		createCyclicList();
	}

	void push_back(const Type& value)
	{
		List<Type, Allocator>::push_back(value);
		createCyclicList();
	}

	void clear(void)
	{
		createNonCyclicList();
		List<Type, Allocator>::clear();
	}


private:
	inline void createNonCyclicList(void)
	{
		_lastElementPointer->NextElementPointer.reset();
	}

	inline void createCyclicList(void)
	{
		_lastElementPointer->NextElementPointer = _firstElementPointer;
	}
};

#endif
