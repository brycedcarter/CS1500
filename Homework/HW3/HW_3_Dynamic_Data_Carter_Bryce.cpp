#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

// Disable this define if you do not want to use the external IO library...  
// be warned thought that error checking will not be as good
#define ENABLE_BETTER_IO

#ifdef ENABLE_BETTER_IO
#include "IO_Helper.h"
#endif

using namespace std;

// Structure for application objects
struct Application {
	string name;
	float price;
};


// A string used to clean the output
string cleanOutput = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

// function declarations
int displayMainMenu();
Application* createNewAppArray(int length);
Application* createNewApp();
void addAppToAppArray(Application* app, Application* appArray, int appArrayCount);
void displayApp(Application app);
void displayAppArray(Application* appArray, int);
int chooseApp(Application* appArray, int appArrayCount);
void updateApp(Application* appArray, int appIndex, Application* app);

// Setup the input error handling
#ifdef ENABLE_BETTER_IO
BDC::IntInputChecker choiceCheckerMainMenu(BDC::INT_SET);
BDC::IntInputChecker intChecker0to100(BDC::INT_RANGE);
BDC::StringInputChecker appNameChekcer(BDC::MULTI_WORD);
BDC::FloatInputChecker appPriceChecker(BDC::FLOAT_RANGE);
BDC::IntInputChecker appChoiceChecker(BDC::INT_RANGE);
#else
void simpleError();
void simpleError(string message);
#endif

int main()
{
#ifdef ENABLE_BETTER_IO
	// Instantiate input handling objects
	float set[] = { 0, 1 };
	choiceCheckerMainMenu.setMatchingSet(set, 2);
	choiceCheckerMainMenu.setErrorHandling(BDC::RETRY, "Invalid Input!\nYou must create an array before any other actions can be used");

	intChecker0to100.setBounds(1,100);
	intChecker0to100.setBoundsTypes(true,true);
	intChecker0to100.setErrorHandling(BDC::RETRY, "Invalid Input!\nThe length of the array must be an integer value between 1 and 100");

	appPriceChecker.setErrorHandling(BDC::RETRY, "Invalid Input!\nThe app price must be a positive number");
	appPriceChecker.setBounds(0,numeric_limits<float>::max());
	appPriceChecker.setBoundsTypes(true,true);

	appChoiceChecker.setBounds(0,0);
	appChoiceChecker.setBoundsTypes(true,true);
	appChoiceChecker.setErrorHandling(BDC::RETRY, "Invalid Input!\nPlease enter an integer between 0 and 0");
#else	
	// Make floats display with 2 digit precision
	cout << fixed;
	cout << setprecision(2);
#endif

	// menu choices
	enum MainMenuChoice
	{
		QUIT,
		CREATE_NEW_APP_ARRAY,
		CREATE_NEW_APP,
		READ_ALL_APPS,
		UPDATE_APP
	};

	Application* appArray;	// array of applications
	Application* app;		// pointer to an application

	int choice;				// current menu choice
	int appArraySize = -1;		// size of the array containing applications
	int appArrayCount = 0;	// how many applications have been added to array
	int appIndex;			// which application to update
	do
	{
#ifdef ENABLE_BETTER_IO
		// if the app array is filled, disable the "create app" option in the main menu
		if (appArrayCount == appArraySize)
		{
			choiceCheckerMainMenu.setErrorHandling(BDC::RETRY, "Invalid Input!\nPlease enter one of 0, 1, 3, 4\nNote that adding new apps is not allowed because the app array is full");
			choiceCheckerMainMenu.removeFromMatchingSet(2);
		}
#endif
		choice = displayMainMenu();	// display menu and return choice
		switch (choice)
		{
		case CREATE_NEW_APP_ARRAY:
			{
			// ask how many applications,
			// read in the size,
			// create application array dynamically
			cout << cleanOutput;
#ifdef ENABLE_BETTER_IO
			appArraySize = intChecker0to100.getInput("How Many Applications?\n");
			choiceCheckerMainMenu.addToMatchingSet(2); // enable option two now that we have an array
			choiceCheckerMainMenu.setErrorHandling(BDC::RETRY, "Invalid Input!\nYou must add a app to the array before any other actions can be used");
#else 
			cout << "How Many Applications?" << endl;
			bool error = false;
			if (!(cin >> appArraySize)) {error = true;}
			if ((appArraySize < 0) || (appArraySize > 100)) {error = true;}
			if (error)
			{
				simpleError("Invalid input.\nThe program will now exit\n");
			}
#endif
			cout << cleanOutput;
			appArray = createNewAppArray(appArraySize);
			break;
			}
		case CREATE_NEW_APP:
		{
							   // create a new application
							   // add it to the array
							   // keep count of how many apps we've created so far

#ifdef ENABLE_BETTER_IO
							   choiceCheckerMainMenu.addToMatchingSet(3); // enable options 3 and 4 now that we have an app in the array
							   choiceCheckerMainMenu.addToMatchingSet(4);
							   choiceCheckerMainMenu.setErrorHandling(BDC::RETRY, "Invalid Input!\nPlease enter an integer between 0 and 4");
#else
							   if (appArrayCount == appArraySize)
							   {
								   simpleError();
							   }
#endif

							   app = createNewApp();
							   cout << cleanOutput;
							   addAppToAppArray(app, appArray, appArrayCount);
							   appArrayCount++;
							   break;
		}
		case READ_ALL_APPS:
			// pass application array to function to display them all
			cout << cleanOutput;
			displayAppArray(appArray, appArrayCount);
			break;
		case UPDATE_APP:
			// display all the apps and ask user to choose one
			// create a new app to get all the updates user wants to perform
			// update the selected application with the data in the app just created
			appIndex = chooseApp(appArray, appArrayCount);
			app = createNewApp();
			updateApp(appArray, appIndex, app);
			break;
		}
	} while (choice != QUIT);
}


int displayMainMenu()
{
	// Display the main menu and return the user's choice as an int
	int choice;
	cout << "Main Menu\n"
		"[1] Create New Array of Applications\n"
		"[2] Add New Application to Array\n"
		"[3] Display Array of Applications\n"
		"[4] Update Existing Application\n"
		""
		"[0] Quit\n";
#ifdef ENABLE_BETTER_IO
	choice = choiceCheckerMainMenu.getInput("Your choice : \n");
#else
	cout << "Your choice : \n";
	bool error = false;
	if (!(cin >> choice)) {error = true;}
	if ((choice < 0) || (choice > 4)) {error = true;}
	if (error)
	{
		simpleError("Invalid input.\nThe program will now exit\n");
	}
#endif
	return choice;
}

Application* createNewAppArray(int length)
{
	// dynamically allocate memory for an array of "length" application objects
	Application* appArray = new Application[length];
	// return a pointer to the array
	return appArray;
}

Application* createNewApp()
{
	// Create a new application object with information obtained from user prompts
	Application* newApp = new Application;

#ifdef ENABLE_BETTER_IO
	newApp->name = appNameChekcer.getInput("App name: ");
	newApp->price = appPriceChecker.getInput("App Price: ");
#else
	cout << cleanOutput << "App name: ";
	bool error = false;
	if (!(cin >> newApp->name)) {error = true;}
	if (error)
	{
		simpleError("Invalid input.\nThe program will now exit\n");
	}
	cout << "App Price: ";
	if (!(cin >> newApp->price)) {error = true;}
	if ((newApp->price < 0)) {error = true;}
	if (error)
	{
		simpleError("Invalid input.\nThe program will now exit\n");
	}
#endif
	// return a pointer to the new app object
	return newApp;
}

void addAppToAppArray(Application* app, Application* appArray, int appArrayCount)
{
	// make the "appArrayCount"th element of "appArray" point to "app"
	appArray[appArrayCount] = *app;
}

void displayApp(Application app)
{
	// Display an application by showing its name and its price
	cout << app.name << " ";
#ifdef ENABLE_BETTER_IO
	BDC::Outputter::printDollarValue(app.price);
#else
	cout << "$" << app.price;
#endif
}

void displayAppArray(Application* appArray, int appArrayCount)
{
	// Display the list of applications in "appArray"
	cout << "APPLICATIONS\n";
	for (int i = 0; i < appArrayCount; i++)
	{
		cout << "[" << i << "] ";
		displayApp(appArray[i]);
		cout << endl;
	}
	cout << endl << endl;
}

int chooseApp(Application* appArray, int appArrayCount)
{
	// Displays a list of apps in "appArray" and then allows the user to pick one of them
	int appChoice;
	cout << cleanOutput;
	displayAppArray(appArray, appArrayCount);

#ifdef ENABLE_BETTER_IO
	appChoiceChecker.setBounds(0, (float)(appArrayCount-1));
	appChoiceChecker.setErrorHandling(BDC::RETRY,"Invalid Input!\nPlease enter an integer between 0 and "+to_string(static_cast<long long>(appArrayCount-1)));
	
	appChoice = appChoiceChecker.getInput("Your Choice: ");
#else
	cout << "Your Choice: ";
	bool error = false;
	if (!(cin >> appChoice)) {error = true;}
	if ((appChoice < 0) || (appChoice > appArrayCount-1)) {error = true;}
	if (error)
	{
		simpleError("Invalid input.\nThe program will now exit\n");
	}
#endif	
	// Return the index of the selected app
	return appChoice;
}

void updateApp(Application* appArray, int appIndex, Application* app)
{
	// Replace the pointer to the app at index "appIndex" in  "appArray" with a pointer to "app"
	appArray[appIndex] = *app;
}

#ifndef ENABLE_BETTER_IO
void simpleError()
{
	simpleError("An error has occured.\nThe program will now exit\n");
}

void simpleError(string message)
{
	cout << "\n\n\n\n\n" << message << "\n\n\n\n\n";
	exit(1);
};
#endif