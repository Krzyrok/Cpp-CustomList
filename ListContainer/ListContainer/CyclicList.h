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
		: List(numberOfElements, value, passedAlloc)
	{
	}

	template <class InputIterator, class = typename enable_if<!is_fundamental<InputIterator>::value>::type>
	CyclicList(InputIterator firstIterator, InputIterator lastIterator, const Allocator& passedAlloc = Allocator())
		: List(firstIterator, lastIterator, passedAlloc)
	{
	}

	CyclicList(const CyclicList& listToCopy)
		: List(listToCopy.begin(), listToCopy.end())
	{
	}

	// -------------------------------------------------------------------

	// Methods

	// Iterators
};

#endif
