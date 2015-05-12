#ifndef __DYNAMICARRAY_H__
#define __DYNAMICARRAY_H__

#include <assert.h>
#include <stdio.h>

template <class TYPE>
class DynamicArray {

private:

	TYPE *data;
	unsigned int allocatedMemory;
	unsigned int elementsNumber;

	void reallocate(unsigned int requiredMemorySize)
	{
		if (data != NULL)
		{
			//Create a new temporal array
			TYPE *tmp = new TYPE[allocatedMemory];

			//Copy original array in to the new
			for (unsigned int i = 0; i < elementsNumber; i++)
			{
				tmp[i] = data[i];
			}

			//Delete original array
			delete[] data;

			//Create a new array with enough space
			allocatedMemory = requiredMemorySize;
			data = new TYPE[allocatedMemory];

			//Copy the temporal array in to the original
			for (unsigned int i = 0; i < elementsNumber; i++)
			{
				data[i] = tmp[i];
			}
		}
		else
		{
			//Delete original array
			delete[] data;

			//Create a new array with enough space
			allocatedMemory = requiredMemorySize;
			data = new TYPE[allocatedMemory];
		}
	}

public:


	DynamicArray<TYPE>() : data(NULL), allocatedMemory(0), elementsNumber(0) 
	{
		reallocate(16);
	}

	DynamicArray<TYPE>(unsigned int requiredMemorySize) : data(NULL), elementsNumber(0)
	{
		reallocate(requiredMemorySize);
	}

	~DynamicArray<TYPE>() 
	{ 
		if (data != NULL) delete[] data; 
	}

	void pushBack(TYPE value)
	{
		if (elementsNumber == allocatedMemory)
			reallocate(allocatedMemory + 1);

		data[elementsNumber] = value;
		elementsNumber++;
	}

	bool pop()
	{
		if (data != NULL && elementsNumber != 0)
		{
			elementsNumber--;
			return true;
		}
		return false;
	}

	bool insert(int value, unsigned int position)
	{
		if (position <= elementsNumber)
		{
			//Create a new temporal array
			TYPE *tmp = new TYPE[allocatedMemory];

			//Copy original array in to the new
			for (unsigned int i = 0; i < elementsNumber; i++)
			{
				tmp[i] = data[i];
			}

			//If we don't have space for the new value of the array, we make 1 more
			if (elementsNumber == allocatedMemory)
			{
				reallocate(allocatedMemory + 1);
			}

			//Copy the temporal array in to the original 
			for (unsigned int i = 0; i < position; i++)
			{
				data[i] = tmp[i];
			}
			data[position] = value;
			for (unsigned int i = position; i < elementsNumber; i++)
			{
				data[i + 1] = tmp[i];
			}

			//Increase number of elements 
			elementsNumber++;

			//Delete temporal array
			delete[] tmp;

			return true;
		}
		return false;
	}

	bool clear()
	{
		if (data != NULL)
		{
			elementsNumber = 0;
			return true;
		}
		return false;
	}
	void swap(TYPE& a, TYPE& b)
	{
		TYPE tmp;
		tmp = a;
		a = b;
		b = tmp;
	}


	unsigned int bubble()
	{
		unsigned int compareCounter = 0;

		bool swapped = true;

		while (swapped == true)
		{
			swapped = false;
			for (unsigned int i = 0; i < elementsNumber - 1; i++)
				{
					compareCounter++;
					if (data[i] > data[i + 1])
					{
						swap(data[i], data[i + 1]);
						swapped = true;
					}
				}
		}
		return compareCounter;
	}

	int& operator[] (unsigned int index)
	{
		assert(index < elementsNumber);
		return data[index];
	}

	const int& operator[] (unsigned int index) const
	{
		assert(index < elementsNumber);
		return data[index];
	}

	unsigned int getMemory() const
	{
		return allocatedMemory;
	}

	unsigned int getElementsNumber() const
	{
		return elementsNumber;
	}
};


#endif 