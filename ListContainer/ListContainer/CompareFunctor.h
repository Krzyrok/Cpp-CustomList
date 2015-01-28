#ifndef COMPARE_FUNCTOR_HEADER
#define COMPARE_FUNCTOR_HEADER

template <class Type>
struct FirstSmallerThanSecond
{
	inline bool operator() (const Type& firstValue, const Type& secondValue) const
	{
		return firstValue < secondValue;
	};
};

template <class Type>
struct FirstGraterEqualThanSecond
{
	inline bool operator() (const Type& firstValue, const Type& secondValue) const
	{
		return firstValue >= secondValue;
	};
};

#endif