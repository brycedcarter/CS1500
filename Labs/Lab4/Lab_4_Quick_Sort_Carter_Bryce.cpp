#include <iostream>
#include <string>
using namespace std;

void displayAllApplicationNames(string appNames[], int appCount);
void swapAppNames(int appIndex1, int appIndex2, string appNames[]);
int  pivot(int first, int last, string appNames[]);
void quickSort(int first, int last, string appNames[]);

void main()
{
	string appNames[] =
	{
		"Pages", "Keynote", "Numbers",
		"Word", "PowerPoint", "Excel",
		"Documents", "Presentation", "Sheets"
	};

	displayAllApplicationNames(appNames, 9);
	swapAppNames(3, 6, appNames);
	displayAllApplicationNames(appNames, 9);
	quickSort(0, 8, appNames);
	displayAllApplicationNames(appNames, 9);

	getchar();
}

void displayAllApplicationNames(string appNames[], int appCount)
{
	cout << "Now displaying all aplication names\n\n";
	for (int i = 0; i < appCount; i++)
	{
		cout << appNames[i] << endl;
	}
	cout << "\n\n\n";
}

void swapAppNames(int appIndex1, int appIndex2, string appNames[])
{
	string tempData1 = appNames[appIndex1];
	appNames[appIndex1] = appNames[appIndex2];
	appNames[appIndex2] = tempData1;
}

int pivot(int first, int last, string appNames[])
{
	int piviotIndex = first;
	string piviotValue = appNames[first];
	for (int i = first + 1; i <= last; i++)
	{
		if (appNames[i].compare(piviotValue)<0)
		{
			piviotIndex++;
			swapAppNames(piviotIndex, i, appNames);
		}
	}
	swapAppNames(piviotIndex, first, appNames);
	return piviotIndex;
}

void quickSort(int first, int last, string appNames[])
{
	if (first < last)
	{
		int piviotIndex = pivot(first, last, appNames);
		quickSort(piviotIndex+1, last, appNames);
		quickSort(first, piviotIndex-1, appNames);
	}
}
