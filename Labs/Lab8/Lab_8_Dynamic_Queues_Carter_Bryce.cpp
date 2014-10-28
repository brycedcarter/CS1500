#include <iostream>
#include <string>
#include "IO_Helper.h"
using namespace std;

// structure representing a donut
struct Donut
{
	string flavor = "";
	float price = 0.0;

	// constructor to initialize member variables
	Donut(string flvr, float prc)
	{
		flavor = flvr;
		price = prc;
	}

	// default, no argument constructor
	Donut(){}
};

// structure representing a collection of donuts
struct DonutTray
{
	// dynamic array of pointers to donuts
	// first * is for the dynamic array
	// second * is for pointer to donut
	Donut** donuts;

	// maximum number of donuts in tray
	int capacity;

	// boundary indices of queue
	int front = 0, back = 0;

	// how many donuts are currently in the queue
	int count = 0;

	// constructor to initialize the tray
	DonutTray(int size)
	{
		// set the capacity and allocate the array
		capacity = size;
		donuts = new Donut*[capacity];
		cout << donuts[2]->price;
	}
};

// putting and removing donuts from the tray
void   enqueueDonut(DonutTray* tray, Donut* donut);
Donut* dequeueDonut(DonutTray* tray);

// display a single donut and the whole tray
void   displayDonut(Donut* donut);
void   displayDonutTray(DonutTray* tray);

int main()
{
	Donut donuts1[10];
	Donut donut1("Flavor 1", 0.54);
	donuts1[0] = donut1;

	Donut * donut2 = new Donut("Flavor 2", 0.56);


	// create some donuts
	Donut* chocolate = new Donut("Chocolate", 0.99);
	Donut* boston = new Donut("Boston Crm", 0.99);
	Donut* jelly = new Donut("Jelly", 0.99);
	Donut* glazed = new Donut("Glazed", 0.99);
	Donut* eclair = new Donut("Eclair", 0.99);
	Donut* snowy = new Donut("Snowy", 0.99);
	Donut* moon = new Donut("Moonraker", 0.99);

	// create a small tray that can hold 5 donuts
	DonutTray* tray = new DonutTray(5);

	// add 4 donuts to the tray and display it
	enqueueDonut(tray, chocolate);
	enqueueDonut(tray, boston);
	enqueueDonut(tray, jelly);
	enqueueDonut(tray, glazed);
	displayDonutTray(tray);

	// remove a donut from the tray, display the donut and tray
	Donut* donut = dequeueDonut(tray);
	displayDonut(donut);
	displayDonutTray(tray);

	// add two more donuts and display the tray
	enqueueDonut(tray, eclair);
	enqueueDonut(tray, snowy);
	displayDonutTray(tray);

	// remove and display two donuts, and add one more
	donut = dequeueDonut(tray);
	displayDonut(donut);
	donut = dequeueDonut(tray);
	displayDonut(donut);
	enqueueDonut(tray, moon);

	// display final tray
	displayDonutTray(tray);
}

// putting and removing donuts from the tray
void   enqueueDonut(DonutTray* tray, Donut* donut)
{
	if (tray->count < tray->capacity)
	{
		tray->donuts[tray->back] = donut;
		tray->back = (tray->back+1)%tray->capacity;
		tray->count++;
	}
	else
	{
		cout << "\n\n+++ WARNING! +++\nTray is full. The donut:\n";
		displayDonut(donut);
		cout << "Was not added to the tray.\n\n";
	}
}
Donut* dequeueDonut(DonutTray* tray)
{
	Donut* dequeuedDonut;
	static Donut imaginaryDonut("Imaginary", 0);
	if (tray->count > 0)
	{
		dequeuedDonut = tray->donuts[tray->front];

		tray->donuts[tray->front] = NULL;
		tray->front = (tray->front + 1) % tray->capacity;
		tray->count--;
	}
	else
	{
		cout << "\n\n+++ WARNING! +++\nTray is empty... no more donuts\nyou can have an imaginary donut though\n\n";
		dequeuedDonut = &imaginaryDonut;
	}
	return dequeuedDonut;
}

// display a single donut and the whole tray`
void   displayDonut(Donut* donut)
{
	cout << "Donut: " << donut->flavor << " ";
	BDC::Outputter::printDollarValue(donut->price);
	cout << endl;
}

void   displayDonutTray(DonutTray* tray)
{
	for (int i = 0; i < tray->count; i++)
	{
		int idx = (tray->front + i) % tray->capacity;
		cout << "[" << idx << "] ";
		displayDonut(tray->donuts[idx]);
	}
}