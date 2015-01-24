#ifndef LIST_HEADER
#define LIST_HEADER

#include "ListElement.h"

template<class Type>
class ListeElement
{
public:
	ListeElement(void);

private:
	shared_ptr<ListeElement<Type>> _firstElementPointer;
};

template<class Type>
List<Type>::List(void)
{
	_firstElementPointer = nullptr;
}

#endif 
