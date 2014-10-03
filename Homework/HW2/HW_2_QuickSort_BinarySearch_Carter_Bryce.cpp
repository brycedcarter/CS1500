#include <iostream>
#include <string>
using namespace std;

void displayApplication(int appIndex, string appNames[], float appPrices[]);
void displayAllApplications(string appNames[], float appPrices[], int appCount);
void swapApps(int appIndex1, int appIndex2, string appNames[], float appPrices[]);
int  pivot(int first, int last, string appNames[], float appPrices[]);
void quickSort(int first, int last, string appNames[], float appPrices[]);
int  binarySearchForPrice(float searchPrice, int first, int last, float appPrices[]);
void findAppWithPrice(float searchPrice, string appNames[], float appPrices[],int size);

void main()
{
	string appNames[] =
	{
		"Pages", "Keynote", "Numbers",
		"Word", "PowerPoint", "Excel",
		"Documents", "Presentation", "Sheets"
	};

	float appPrices[] =
	{
		3.99, 2.99, 1.99,
		19.99, 29.99, 39.99,
		34.99, 24.99, 14.99
	};

	displayAllApplications(appNames, appPrices, 9);
	quickSort(0, 8, appNames, appPrices);
	displayAllApplications(appNames, appPrices, 9);

	findAppWithPrice(25.99, appNames, appPrices, 9);
	findAppWithPrice(19.99, appNames, appPrices, 9);
	findAppWithPrice(1.99, appNames, appPrices, 9);
	findAppWithPrice(39.99, appNames, appPrices, 9);



	getchar();
}



void displayApplication(int appIndex, string appNames[], float appPrices[])
{
	cout << appNames[appIndex] << ' ' << appPrices[appIndex] << endl;
}

void displayAllApplications(string appNames[], float appPrices[], int appCount)
{
	for (int i = 0; i < appCount; i++)
	{
		cout << i << ") ";
		displayApplication(i, appNames, appPrices);
	}
	cout << endl;

}

void swapApps(int appIndex1, int appIndex2, string appNames[], float appPrices[])
{
	string tempName = appNames[appIndex1];
	float tempPrice = appPrices[appIndex1];

	appNames[appIndex1] = appNames[appIndex2];
	appPrices[appIndex1] = appPrices[appIndex2];

	appNames[appIndex2] = tempName;
	appPrices[appIndex2] = tempPrice;
}

int  pivot(int first, int last, string appNames[], float appPrices[])
{
	int piviotIndex = first;
	int piviotValue = appPrices[first];
	for (int i = first + 1; i <= last; i++)
	{
		if (appPrices[i] <= (piviotValue))
		{
			piviotIndex++;
			swapApps(piviotIndex, i, appNames, appPrices);
		}
	}
	swapApps(first, piviotIndex, appNames, appPrices);
	return piviotIndex;
}

void quickSort(int first, int last, string appNames[], float appPrices[])
{
	if (first < last)
	{
		int piviotIndex = pivot(first, last, appNames, appPrices);
		quickSort(first, piviotIndex-1, appNames, appPrices);
		quickSort(piviotIndex+1, last, appNames, appPrices);
	}
}

int  binarySearchForPrice(float searchPrice, int first, int last, float appPrices[])
{
	int midIndex = (last - first) / 2 + first;
	if (first == last)
	{
		if (appPrices[first] == searchPrice)
		{
			return first;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		if (appPrices[midIndex] >= searchPrice)
		{
			return binarySearchForPrice(searchPrice, first, midIndex, appPrices);
		}
		else
		{
			return binarySearchForPrice(searchPrice, midIndex+1, last, appPrices);
		}
	}
}

void findAppWithPrice(float searchPrice, string appNames[], float appPrices[], int size)
{
	cout << "Searching for an App with price of: " << searchPrice << "\n==========================================\n";

	int foundIndex = binarySearchForPrice(searchPrice, 0, size, appPrices);
	cout << "Price of " << searchPrice;
	if (foundIndex == -1)
	{
		cout << " Not Found" << endl;
		cout << "No app found!";
	}
	else
	{
		cout << " Found at index " << foundIndex << endl;
		cout << "App with price of " << searchPrice << " is " << appNames[foundIndex];
	}
	cout << "\n==========================================\n\n";
}
