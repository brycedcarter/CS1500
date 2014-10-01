#include <iostream>
using namespace std;

void displayIntArray(int arr[], int size);
void readIntArray(int arr[], int size);
int* copyArray(int arr[], int size);
int* concatenateIntArrays(int arr1[], int arr2[], int size1, int size2);
int* subArray(int arr[], int size, int start, int count);
void error(int errorCode);

int main()
{
	// Read 2 dynamic arrays
	int size1, size2, size3;
	cout << "Size of arr1: ";
	cin >> size1;
	if (size1 <= 0) error(100);
	cout << "Size of arr2: ";
	cin >> size2;
	if (size2 <= 0) error(100);

	int* arr1 = new int[size1];
	int* arr2 = new int[size2];

	readIntArray(arr1, size1);
	readIntArray(arr2, size2);

	// concatenate two arrays into a third
	int* arr3;
	arr3 = concatenateIntArrays(arr1, arr2, size1, size2);

	size3 = size1 + size2;
	cout << "Concatenated Array:" << endl;
	displayIntArray(arr3, size3);

	getchar();

	// Copy an array
	int* copy = copyArray(arr1, size1);
	cout << "Copied Array:" << endl;
	displayIntArray(copy, size1);

	// Get sub array
	// Read parent array
	int size4;
	cout << "Array Size: ";
	cin >> size4;
	if (size4 <= 0) error(100);
	int* arr4 = new int[size4];
	readIntArray(arr4, size4);

	// get sub array
	int start, count;
	cout << "Start: ";
	cin >> start;
	if (start >= size4) error(100);
	if (start < 0) error(100);
	cout << "Count: ";
	cin >> count;
	if (start+count > size4) error(100);
	if (count < 0) error(100);
	int* sub = subArray(arr4, size4, start, count);

	// display sub array
	cout << "Sub Array:" << endl;
	displayIntArray(sub, count);
}


void displayIntArray(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << endl;
	}
}

void readIntArray(int arr[], int size)
{
	cout << "Now filling an array of length " << size << endl << "==============================================\n\n";
	for (int i = 0; i < size; i++)
	{	
		
		while (1) {
			cout << "Enter a value for array element # " << i << endl;
			if (cin >> arr[i]) {
				break;
			}
			else {
				error(101);
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cout << "\n\n==============================================\nArray has been successfuly filled\n\n";
}


int* copyArray(int arr[], int size)
{
	int* copy = new int[size];
	for (int i = 0; i < size; i++)
	{
		copy[i] = arr[i];
	}
	return copy;
}


int* concatenateIntArrays(int arr1[], int arr2[], int size1, int size2)
{
	int newSize = size1 + size2;
	int* concat = new int[newSize];
	for (int i = 0; i < size1; i++)
	{
		concat[i] = arr1[i];
	}
	for (int i = 0; i < size2; i++)
	{
		concat[i + size1] = arr2[i];
	}
	return concat;
}

int* subArray(int arr[], int size, int start, int count)
{
	int* sub = new int[count];
	for (int i = 0; i < count; i++)
	{
		sub[i] = arr[start + i];
	}
	return sub;
}

void error(int errorCode)
{
	switch (errorCode)
	{
	case 100:
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPICNIC Error (Problem in chair not in computer)\nNo second chances\nDon't give bad input!!!\nGoodbye\n";
		exit(errorCode);
		break;
	case 101:
		cout << "\n\nInvalid value enerted...\nWe will give you another chance, but don't be dumb this time\n\n";
		break;
	}
	
}