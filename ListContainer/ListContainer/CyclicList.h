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
		assign(listWithObjects);
		return *this;
	}


	// Iterators
	iterator begin(void)
	{
		return iterator(_firstElementPointer, true);
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
		return iterator(_firstElementPointer, false, true);
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
		return const_iterator(_firstElementPointer, true);
	}

	const_iterator cend(void) const
	{
		return const_iterator(_firstElementPointer, false, true);
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

	void assign(initializer_list<value_type> listWithValues)
	{
		assign(listWithValues.begin(), listWithValues.end());
	}

	template <class... Args>
	void emplace_front(Args&&... args)
	{
		List<Type, Allocator>::emplace_front(args...);
		createCyclicList();
	}

	void push_front(const Type& value)
	{
		List<Type, Allocator>::push_front(value);
		createCyclicList();
	}

	void push_front(Type&& value)
	{
		push_front(value);
	}

	void pop_front(void)
	{
		createNonCyclicList();
		List<Type, Allocator>::pop_front();
		if (empty())
			return;

		createCyclicList();
	}

	template <class... Args>
	void emplace_back(Args&&... args)
	{
		List<Type, Allocator>::emplace_back(args...);
		createCyclicList();
	}

	void push_back(const Type& value)
	{
		List<Type, Allocator>::push_back(value);
		createCyclicList();
	}

	void push_back(Type&& value)
	{
		push_back(value);
	}

	void pop_back(void)
	{
		createNonCyclicList();
		List<Type, Allocator>::pop_back();
		if (empty())
			return;

		createCyclicList();
	}

	template <class... Args>
	iterator emplace(const_iterator positionIterator, Args&&... args)
	{
		bool isInsertingOnBegin = changeIteratorIfEndAndCheckIfBegin(positionIterator);
		iterator result(List<Type, Allocator>::emplace(positionIterator, args...), isInsertingOnBegin);
		createCyclicList();
		return result;
	}

	iterator insert(const_iterator positionIterator, const Type& value)
	{
		bool isInsertingOnBegin = changeIteratorIfEndAndCheckIfBegin(positionIterator);
		iterator result(List<Type, Allocator>::insert(positionIterator, value), isInsertingOnBegin);
		createCyclicList();
		return result;
	}

	iterator insert(const_iterator positionIterator, size_type numberOfValues, const Type& value)
	{
		bool isInsertingOnBegin = changeIteratorIfEndAndCheckIfBegin(positionIterator);
		iterator result(List<Type, Allocator>::insert(positionIterator, numberOfValues, value), isInsertingOnBegin);
		createCyclicList();
		return result;
	}

	template <class InputIterator, class = typename enable_if<!is_fundamental<InputIterator>::value>::type>
	iterator insert(const_iterator positionIterator, InputIterator firstIterator, InputIterator lastIterator)
	{
		bool isInsertingOnBegin = changeIteratorIfEndAndCheckIfBegin(positionIterator);
		iterator result(List<Type, Allocator>::insert(positionIterator, firstIterator, lastIterator), isInsertingOnBegin);
		createCyclicList();
		return result;
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
		createNonCyclicList();
		bool isDeletingBeginning = checkIfBegin(positionIterator);

		iterator result(List<Type, Allocator>::erase(positionIterator), isDeletingBeginning);
		if (empty())
			return iterator();

		createCyclicList();
		return result;
	}

	iterator erase(const_iterator firstPosition, const_iterator lastPosition)
	{
		createNonCyclicList();
		bool isDeletingBeginning = checkIfBegin(firstPosition);

		iterator result(List<Type, Allocator>::erase(firstPosition, lastPosition), isDeletingBeginning);
		if (empty())
			return iterator();

		createCyclicList();
		return result;
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

	inline bool checkIfBegin(const_iterator& positionIterator)
	{
		bool result = false;
		if (positionIterator == cbegin())
			result = true;

		return result;
	}

	inline bool changeIteratorIfEndAndCheckIfBegin(const_iterator& positionIterator)
	{
		bool isInsertingOnBegin = checkIfBegin(positionIterator);
		if (positionIterator == cend())
		{
			positionIterator = const_iterator();
		}

		return isInsertingOnBegin;
	}

	void setFirstElementPointerAndMoveLast(const_iterator positionIterator)
	{
		shared_ptr<ListElement<Type, Allocator>> elementPointerBefore = findElementPointerBefore(positionIterator);
		_lastElementPointer = elementPointerBefore;
		_firstElementPointer = elementPointerBefore->NextElementPointer;
	}
};

#endif
