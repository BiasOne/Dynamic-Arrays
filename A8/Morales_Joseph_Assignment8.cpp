#include <iostream>
#include <string>

using namespace std;


class dynamicArrayString
{
	//Declare private variable
private:
	string* dynamicArray;
	int size;
	int capacity;

public:
	//Default constructor
	dynamicArrayString()
	{
		dynamicArray = nullptr;
		size = 0;
		capacity = 0;
	}
	//Copy constructor
	dynamicArrayString(const dynamicArrayString& lhs)
	{
		//size and capacity are set to the value of the array being copied
		dynamicArray = nullptr;
		delete[] dynamicArray;
		//size and capacity are set to the value of the array being copied
		size = lhs.size;
		capacity = lhs.capacity;
		//new memory is allocated using the copied capacity
		dynamicArray = new string[lhs.capacity];
		//elements are moved into the new array
		for (int i = 0; i < size; i++)
		{
			dynamicArray[i] = lhs.dynamicArray[i];
		}
	}
	//Assignment operator
	dynamicArrayString& operator=(const dynamicArrayString& rhs)
	{
		//size and capacity are set to the value of the array being copied
		dynamicArray = nullptr;
		delete[] dynamicArray;
		//size and capacity are set to the value of the array being copied
		size = rhs.size;
		capacity = rhs.capacity;
		//new memory is allocated using the copied capacity
		dynamicArray = new string[rhs.capacity];
		//elements are moved into the new array
		for (int i = 0; i < size; i++)
		{
			dynamicArray[i] = rhs.dynamicArray[i];
		}
		//allows for multiple assignments at once
		return *this;
	}

	//Adds an entry to the dynamic string array
	void addEntry(string value)
	{
		//if the array is pointing to nothing is creates memory for a single entry and adds it to the array
		if (dynamicArray == nullptr)
		{
			dynamicArray = new string[1];
			dynamicArray[0] = value;
			capacity = 1;
		}
		//if the size equals capacity, create a new array with more space for the entry and copy the elements into the new array 
		else if (size == capacity)
		{
			string* newArray = new string[capacity + 1];

			for (int i = 0; i < size; i++)
			{
				newArray[i] = dynamicArray[i];
			}
			//deletes the old array to prevent memory leaks- assigns the new array to the dynamic array - increments size and capacity
			newArray[size] = value;
			capacity++;
			delete[] dynamicArray;
			dynamicArray = newArray;
		}
		size++;
	}

	//Deletes memory at a specific index
	bool deleteEntry(string findMe)
	{
		//bool determines whether the entry was found and resets whenever the funtion is entered again
		bool found = false;
		//int determines the index where the entry was found
		int foundAt;
		//if the dynamic array is empty it returns false and does not search 
		if (dynamicArray == nullptr)
		{
			return false;
		}
		//searches through each iteration of the array until an entry is found and breaks out of the for loop
		else
		{
			for (int i = 0; i < size; i++) 
			{
				if (dynamicArray[i] == findMe)
				{
					//if entry is found - its index is stored
					foundAt = i;
					found = true;
					break;
				}
			}
		}
		//decreases the size of the array by 1 before adding a new element
		string* newArray = new string[capacity - 1];
		//is only entered if a boolean value is found
		if (found == true) {
			//stores all of the elements before the location of the found entry into the new array
			for (int i = 0; i < size; i++) 
			{
				//pushes the elements before the entry location into the array
				if (i < foundAt) 
				{
					newArray[i] = dynamicArray[i];
				}
				//skips over the index of the found element and copies the rest of entries into the new vector
				else if (i > foundAt) 
				{
					newArray[i - 1] = dynamicArray[i];
				}
			}
			//deletes the old array to prevent memory leaks- assigns the new array to the dynamic array - decrements size and capacity
			delete[] dynamicArray;			
			capacity--;
			dynamicArray = newArray;
		}
		size--;
		return true;
	}

	//Returns dynamicArray at a specific index
	string getEntry(int index)
	{
		if (index >= size)
		{
			return nullptr;
		}
		else
		{
			return dynamicArray[index];
		}

	}

	//Retruns the dynamicArray being pointed to 
	string* GetdynamicArray()
	{
		return dynamicArray;
	}

	//Returns number of elements currently in the array
	int getSize()
	{
		return size;
	}

	//Returns the Max Capacity of the array
	int getCapacity()
	{
		return capacity;
	}
	//Prints all the elements in the array
	void print()
	{
		for (int i = 0; i < size; i++)
		{
			cout << dynamicArray[i] << endl;
		}
	}
	//Destructor
	~dynamicArrayString()
	{
		delete[] dynamicArray;
	}
};


int main() {
	dynamicArrayString dynamicArrayStringOBJ;

	dynamicArrayString test1;
	cout << "** Test1: Added 6 entries **" << endl;
	test1.addEntry("This");
	test1.addEntry("is");
	test1.addEntry("testing");
	test1.addEntry("the");
	test1.addEntry("add");
	test1.addEntry("function");
	test1.print();
	cout << "** Size after adding 6 entries: " << test1.getSize() << " **" << endl;
	cout << endl;

	cout << "** Test2: Removed add and function - Added remove and function **" << endl;
	test1.deleteEntry("add");
	test1.deleteEntry("function");
	test1.addEntry("remove");
	test1.addEntry("function");
	test1.print();
	cout << "** Size after deleting two entries and adding one: " << test1.getSize() << " **" << endl;
	cout << endl;

	cout << "** Test3: Print index 2, 3, 4 **" << endl;
	cout << test1.getEntry(2) << endl;
	cout << test1.getEntry(3) << endl;
	cout << test1.getEntry(4) << endl;
	cout << endl;


	dynamicArrayString test2(test1);
	cout << "** Test4: Array Copy **" << endl;
	test2.print();
	cout << "** Size of copy: " << test2.getSize() << " **" << endl;
	cout << endl;

	cout << "** Test5: adding 3 entries to array copy **" << endl;
	test2.addEntry("This");
	test2.addEntry("Is");
	test2.addEntry("A");
	test2.addEntry("Test");
	test2.print();
	cout << "** Size of copy after new entries: " << test2.getSize() << " **" << endl;
	cout << endl;

	cout << "** Priting original array for comparison" << endl;
	test1.print();
	cout << "** Size of original: " << test1.getSize() << " **" << endl;


	return 0;
}