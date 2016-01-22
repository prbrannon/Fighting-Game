#ifndef ARRAYLIST_H
#define ARRAYLIST_H

const int DEFAULT_SIZE = 2;

template <class T>
class ArrayList
{
	public:
		// Constructor
		ArrayList()
		{
			size = DEFAULT_SIZE;
			length = 0;
			arr = new T[DEFAULT_SIZE];
		}
		
		// Destructor
		~ArrayList()
		{
			delete[] arr;
		}

		// Copy constructor
		ArrayList(const ArrayList &copy_me)
		{
			size = copy_me.size;
			length = copy_me.length;
			for (int i = 0; i < copy_me.length; i++)
			{
				Add(copy_me.arr[i]);
			}
		}

		
		// = overload operator
		void operator = (const ArrayList &copy_me)
		{
			size = copy_me.size;
			length = copy_me.length;
			for (int i = 0; i < copy_me.length; i++)
			{
				Add(copy_me.arr[i]);
			}
		}

		// get element at specified index
		T& operator [] (unsigned int index)
		{
			return arr[index];
		}

		// return length 
		int GetLength() const { return length; }

		void Add(const T& element)
		{
			// Resize if needed
			if (length >= size)
			{
				Resize(size * 2);
			}

			arr[length++] = element;
		}
		
		// Delete at index
		void Delete(int index)
		{
			arr[index] = T();
			arr[index] = arr[--length];
		}

		// Resize array. Caution: Elements will be moved.
		void Resize(unsigned int new_size)
		{
			T *new_array = new T[new_size];

			for (int i = 0; i < length; i++)
			{
				new_array[i] = arr[i];
			}

			delete[] arr;
			arr = new_array;

			size = new_size;
		}

	private:

		int size;							// Max number elements 
		int length;							// Current number elements 
		T* arr;								// Array (uses differnet types depending on different situations)
};

#endif