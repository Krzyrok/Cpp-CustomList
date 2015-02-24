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

	CyclicList(const CyclicList& listToCopy, const Allocator& passedAlloc = Allocator())
		: CyclicList(listToCopy.begin(), listToCopy.end(), passedAlloc)
	{
	}

	CyclicList(CyclicList&& listToCopy, const Allocator& passedAlloc = Allocator())
		: CyclicList(passedAlloc)
	{
		swap(listToCopy);
	}

	CyclicList(initializer_list<value_type> listWithObjects, const Allocator& passedAlloc = Allocator())
		: CyclicList(listWithObjects.begin(), listWithObjects.end(), passedAlloc)
	{
	}


	// -------------------------------------------------------------------

	// Methods
	CyclicList& operator=(const CyclicList& otherList)
	{
		assign(otherList.begin(), otherList.end());
		return *this;
	}

	CyclicList& operator=(CyclicList&& otherList)
	{
		swap(otherList);
		return *this;
	}

	CyclicList& operator=(initializer_list<Type> listWithObjects)
	{
		assign(listWithObjects.begin(), listWithObjects.end());
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

	iterator begin(iterator positionIterator)
	{
		setFirstElementPointerAndMoveLast(positionIterator);
		return begin();
	}

	const_iterator begin(const_iterator positionIterator)
	{
		setFirstElementPointerAndMoveLast(positionIterator);
		return cbegin();
	}

	iterator end(void)
	{
		return iterator(_firstElementPointer, true);
	}

	const_iterator end(void) const
	{
		return cend();
	}

	iterator end(iterator positionIterator)
	{
		setFirstElementPointerAndMoveLast(positionIterator);
		return end();
	}

	const_iterator end(const_iterator positionIterator)
	{
		setFirstElementPointerAndMoveLast(positionIterator);
		return cend();
	}

	const_iterator cbegin(void) const
	{
		return const_iterator(_firstElementPointer);
	}

	const_iterator cend(void) const
	{
		return const_iterator(_firstElementPointer, true);
	}


	// Modifiers
	template <class InputIterator, class = typename enable_if<!is_fundamental<InputIterator>::value>::type>
	void assign(InputIterator firstIterator, InputIterator lastIterator)
	{
		if (firstIterator == lastIterator)
		{
			clear();
			return;
		}

		if (size() > 0)
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

		if (size() > 0)
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
		if (empty())
			return;
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

	void setFirstElementPointerAndMoveLast(const_iterator positionIterator)
	{
		shared_ptr<ListElement<Type, Allocator>> elementPointerBefore = findElementPointerBefore(positionIterator);
		_lastElementPointer = elementPointerBefore;
		_firstElementPointer = elementPointerBefore->NextElementPointer;
	}
};

#endif
