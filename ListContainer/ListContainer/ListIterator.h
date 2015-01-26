#ifndef LIST_ITERATOR_HEADER
#define LIST_ITERATOR_HEADER

#include "ListElement.h"

#include <iterator>

//template <class Type>
//class ConstListIterator;


template <class Type, bool is_const_iterator = true>
class ListIterator 
	: public iterator<forward_iterator_tag, Type, ptrdiff_t, Type*, Type&>
{
public:
	typedef typename conditional<is_const_iterator, const shared_ptr<ListElement<Type>>, shared_ptr<ListElement<Type>>>::type DataStructurePointerType;

	typedef typename conditional<is_const_iterator, const Type&, Type&>::type ValueReferenceType;

	ListIterator(DataStructurePointerType pointer_to_datastructure) : _list(pointer_to_datastructure) {
		// You might want to do something here, but not necessarily
	}

	ListIterator(const ListIterator<Type, false>& other) : _list(other._list) {
		// Copy constructor. Depending on your iterator, you might want to add something here.
	}

	bool operator== (const ListIterator& other) const {
		// Up to you to define
		return _list == other._list;
	}

	bool operator!= (const ListIterator& other) const {
		return _list != other._list;;
	}

	ValueReferenceType operator*() {
		// Up to you to define: get a reference to an element in your data structure
		return _list->GetValue();
	}

	ListIterator &operator++(){
		_list = _list->NextElementPointer;
		return *this;
	}

	ListIterator operator++(int){
		// Use operator++()
		ListIterator previousIterator = *this;
		_list = _list->NextElementPointer;
		return previousIterator;
	}


	friend class ListIterator<Type, true>;

private:
	DataStructurePointerType _list; // store a reference to MyDataStructure

//	ListIterator(void)
//		: _pointer(nullptr) {}
//
//
//	ListIterator(shared_ptr<ListElement<Type>> ptr) 
//		: _pointer(ptr) {}
//
//	ListIterator(const ListIterator &originalIterator)
//		: _pointer(originalIterator._pointer) {}
//
//	ListIterator operator++() 
//	{  
//		_pointer = _pointer->NextElementPointer;
//		return *this;
//	}
//
//	ListIterator operator++(int) 
//	{ 
//		ListIterator previousIterator = *this;
//		_pointer = _pointer->NextElementPointer;
//		return previousIterator;
//	}
//
//	Type& operator*()
//	{ 
//		return _pointer->GetValue();
//	}
//
//	Type* operator->()
//	{ 
//		return &(_pointer->GetValue());
//	}
//
//	Type& operator*() const
//	{
//		return _pointer->GetValue();
//	}
//
//	Type* operator->() const
//	{
//		return &(_pointer->GetValue());
//	}
//
//	bool operator==(const ListIterator& secondIterator)
//	{ 
//		return _pointer == secondIterator._pointer;
//	}
//
//	bool operator!=(const ListIterator& secondIterator)
//	{ 
//		return _pointer != secondIterator._pointer;
//	}
//
//
//	//friend class ConstListIterator<Type>;
//
//private:
//	shared_ptr<ListElement<Type>> _pointer;
};

//check before using
//template <class Type>
//class ConstListIterator
//	: public iterator<forward_iterator_tag, const ListElement<Type>, ptrdiff_t, const ListElement<Type>*, const ListElement<Type>&>
//{
//public:
//	ConstListIterator(void)
//		: _pointer(nullptr) {}
//
//
//	ConstListIterator(shared_ptr<ListElement<Type>> ptr)
//		: _pointer(ptr) {}
//
//	ConstListIterator(const ConstListIterator &originalIterator)
//		: _pointer(originalIterator._pointer) {}
//
//	ConstListIterator(const ListIterator<Type> &originalIterator)
//		: _pointer(originalIterator._pointer) {}
//
//	ConstListIterator operator++()
//	{
//		_pointer = _pointer->NextElementPointer;
//		return *this;
//	}
//
//	ConstListIterator operator++(int)
//	{
//		ConstListIterator previousIterator = *this;
//		_pointer = _pointer->NextElementPointer;
//		return previousIterator;
//	}
//
//	Type& operator*() const
//	{
//		return _pointer->GetValue();
//	}
//
//	Type* operator->() const
//	{
//		return &(_pointer->GetValue());
//	}
//
//	bool operator==(const ConstListIterator& secondIterator)
//	{
//		return _pointer == secondIterator._pointer;
//	}
//
//	bool operator!=(const ConstListIterator& secondIterator)
//	{
//		return _pointer != secondIterator._pointer;
//	}
//
//
//private:
//	shared_ptr<ListElement<Type>> _pointer;
//};

#endif
