#ifndef LIST_ITERATOR_HEADER
#define LIST_ITERATOR_HEADER

#include "CommonHeaders.h"

#include <iterator>

template <class Type>
class ListIterator 
	: public iterator<forward_iterator_tag, Type, ptrdiff_t, Type*, Type&>
{
public:

};

#endif
