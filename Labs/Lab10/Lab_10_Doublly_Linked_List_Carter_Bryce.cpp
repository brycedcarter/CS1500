#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

struct Donut
{
	string flavor;
	double price;
	Donut* prev = NULL;
	Donut* next = NULL;
	Donut(){}
	Donut(string flavor, double price)
	{
		this->flavor = flavor;
		this->price = price;
	}
	void display()
	{
		cout << flavor << "\t$" << price << endl;
	}
};

struct DonutTray
{
	Donut* head = NULL;
	Donut* tail = NULL;
	int length = 0;
	DonutTray(){}
	void append(Donut* donut);
	void prepend(Donut* donut);
	void insert(Donut* donut, int index);
	void remove(int index);
	void display()
	{
		Donut* current = head;
		int counter = 0;
		while (current != NULL)
		{
			cout << "[" << counter << "] ";
			current->display();
			current = current->next;
			counter++;
		}
		cout << "======================" << endl;
	}
};

int main()
{
	// create some donuts
	Donut* chocolate = new Donut("Chocolate", 0.99);
	Donut* boston = new Donut("Boston Crm", 1.99);
	Donut* jelly = new Donut("Jelly", 2.99);
	Donut* glazed = new Donut("Glazed", 1.99);
	Donut* eclair = new Donut("Eclair", 1.99);
	Donut* snowy = new Donut("Snowy", 0.99);
	Donut* glazed2 = new Donut("Glazed", 0.99);
	Donut* moon = new Donut("Moonraker", 2.99);
	Donut* vanilla = new Donut("Vanilla", 1.99);
	Donut* strawberry = new Donut("Strawberry", 0.99);
	Donut* caramel = new Donut("Caramel", 2.99);
	Donut* coffee = new Donut("Coffee", 1.99);

	// create a donut tray
	DonutTray* tray = new DonutTray;

	// append some donuts
	tray->append(chocolate);
	tray->append(boston);
	tray->append(jelly);
	tray->append(glazed);

	tray->display();

	// prepend some donuts
	tray->prepend(eclair);
	tray->prepend(snowy);
	tray->prepend(glazed2);
	tray->prepend(moon);

	tray->display();

	// insert some donuts
	tray->insert(vanilla, 2);
	tray->insert(strawberry, 4);
	tray->insert(caramel, 7);
	tray->insert(coffee, 9);
	tray->display();

	// remove some donuts
	tray->remove(3);
	tray->display();
	tray->remove(5);
	tray->display();
}

void DonutTray::append(Donut* donut)
{
	if (this->length == 0)
	{
		this->head = donut;
		donut->prev = NULL;
	}
	else
	{
		this->tail->next = donut;
		donut->prev = this->tail;
	}
	this->tail = donut;
	this->tail->next = NULL;
	this->length++;
}

void DonutTray::prepend(Donut* donut)
{
	if (this->length == 0)
	{
		this->tail = donut;
		donut->next = NULL;
	}
	else
	{
		this->head->prev = donut;
		donut->next = this->head;
	}
	this->head = donut;
	this->head->prev = NULL;
	this->length++;
}

void DonutTray::insert(Donut* donut, int index)
{
	if (index > this->length - 1 || index < 0)
	{
		cout << "\n\n============= WARNING! =============\nIndex value is out of range\nThe donut was NOT inserted\n====================================\n\n";
	}
	else
	{
		Donut* previous = NULL;
		Donut* next = this->head;

		for (int i = 0; i < index; i++)
		{
			previous = next;
			next = next->next;
		}
		donut->prev = previous;
		donut->next = next;

		if (previous == NULL)
		{
			next->prev = donut;
			this->head = donut;
		}
		else if (next == NULL)
		{
			previous->next = donut;
			this->tail = donut;
		}
		else
		{
			next->prev = donut;
			previous->next = donut;
		}
		this->length++;
	}
}

void DonutTray::remove(int index)
{
	if (index > this->length - 1 || index < 0)
	{
		cout << "\n\n============= WARNING! =============\nIndex value is out of range\nThe donut was NOT removed\n====================================\n\n";
	}
	else
	{
		Donut* toRemove = this->head;

		for (int i = 0; i < index; i++)
		{
			toRemove = toRemove->next;
		}
		if (toRemove == this->head)
		{
			toRemove->next->prev = NULL;
			this->head = toRemove->next;
		}
		else if (toRemove == this->tail)
		{
			toRemove->prev->next = NULL;
			this->tail = toRemove->prev;
		}
		else
		{
			toRemove->prev->next = toRemove->next;
			toRemove->next->prev = toRemove->prev;
		}
		this->length--;

		delete toRemove;
	}
}