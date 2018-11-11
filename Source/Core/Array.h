#pragma once

template<typename T, typename CountType = uint32_t>
struct DArray
{
	CountType Count = 0;
	T* Data = nullptr;

	// Range based for begin() and end()
	T* begin() const
	{
		return Data;
	}

	T* end() const
	{
		return Data + (Count - 1);
	}

	DArray(CountType InCount = 0)
		: Count(0)
		, Data(nullptr)
	{
		if (InCount > 0) Resize(InCount);
	}

	virtual ~DArray()
	{
		free(Data);
	}

	void Resize(CountType NewCount)
	{
		Count = NewCount;
		Data = static_cast<T*>(realloc(Data, sizeof(T) * Count));
	}

	void PushBack(const T& Value)
	{
		Count++;
		Data = static_cast<T*>(realloc(Data, sizeof(T) * Count));
		Data[Count - 1] = Value;
	}

	void PushBack(T&& Value)
	{
		Count++;
		Data = static_cast<T*>(realloc(Data, sizeof(T) * Count));
		Data[Count - 1] = Value;
	}

	T& operator [] (CountType Index) { assert(Index < Count); return Data[Index]; }
	const T& operator [] (CountType Index) const { assert(Index < Count); return Data[Index]; }
};