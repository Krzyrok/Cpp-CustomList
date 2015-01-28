#ifndef BINARY_FUNCTOR_HEADER
#define BINARY_FUNCTOR_HEADER

template <class Type>
struct BinaryIsEqual
{
	inline bool operator() (const Type& secondValue, const Type& firstValue) const
	{
		return secondValue == firstValue;
	};
};

template <class Type>
struct SecondIsGreater
{
	inline bool operator() (const Type& secondValue, const Type& firstValue) const
	{
		return secondValue > firstValue;
	};
};

#endif