#ifndef DELETER_HEADER
#define DELETER_HEADER

#include "CommonHeaders.h"

template<class Type, class Allocator>
class Deleter
{
public:
	Deleter(const Allocator& passedAllocator)
	{
		_allocator = passedAllocator;
	}

	void operator()(Type* pointer)
	{
		//cout << "Deleted." << endl;
		_allocator.deallocate(pointer, 1);
	}

private:
	Allocator _allocator;
};

#endif 
