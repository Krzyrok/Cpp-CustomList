#ifndef FUNCTOR_HEADER
#define FUNCTOR_HEADER

template <class Type>
struct IsEqual
{
	void SetComparingValue(int newValue)
	{
		_comparingValue = newValue;
	}

	inline bool operator() (const Type& value) const
	{
		return value == _comparingValue;
	};

private:
	int _comparingValue;
};

template <class Type>
struct IsEven
{
	inline bool operator() (const Type& value) const
	{
		return value % 2 == 0;
	};
};

#endif