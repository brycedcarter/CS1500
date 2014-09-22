#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

const int LOGIN = 1;
const int REGISTER = 2;
const int LOGIN_AS_GUEST = 3;
const int QUIT = 0;
const string CLEAN_DISPLAY_STR = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
const string HEADDER_BAR_STR = "=======================================================\n";

struct user {
	string username;
	string password;
	string message;
} users[3];



int main() 
{
	int selection = -1;
	string username;
	string password;
	string passwordVerify;
	bool loginMatch;

	users[0].username = "alice";
	users[0].password = "wonderland";
	users[0].message = "Follow me down the rabbit hole";

	users[1].username = "thomas";
	users[1].password = "anderson";
	users[1].message = "There is no spoon";

	users[2].username = "yoda";
	users[2].password = "minch";
	users[2].message = "Do. Or do not. There is no try";


	while (selection != QUIT)
	{
		cout << "[1] Login\n"
			"[2] Register\n"
			"[3] Login as a Guest\n"
			"[0] Quit\n";

		cin >> selection;
		// Clean out the cin buffer of any unwanted junk
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		cout << "\n\n\n";
		switch (selection)
		{
		case LOGIN:
			// Display login headder
			cout << CLEAN_DISPLAY_STR <<
				HEADDER_BAR_STR <<
				"LOGIN\n" <<
				HEADDER_BAR_STR << endl;

			// Show username and password prompts
			cout << "Username: ";
			cin >> username;
			cout << "\nPassword: ";
			cin >> password;

			// Clear the display and show either a login message or an error
			cout << CLEAN_DISPLAY_STR;
			loginMatch = false;
			for (int i=0; i < 3; i++)
			{
				if (users[i].username == username && users[i].password == password)
				{
					cout << "\n\n============= Hello " << users[i].username << " =============\n\n"
							<< users[i].message
							<< "\n\n========================================\n\n\n\n";

					loginMatch = true;
				}
			}

			if (!loginMatch) 
			{
				cout << "\n\n================= ERROR =================\n\n"
						"Sorry, your username or password is invalid"
						"\n\n=========================================\n\n\n\n";
			}

			break;

		case REGISTER:
			// Display register headder
			cout << CLEAN_DISPLAY_STR <<
				HEADDER_BAR_STR <<
				"REGISTER\n" <<
				HEADDER_BAR_STR << endl;

			// Display register prompts ("username", "password", and "verify password")
			cout << "Username: ";
			cin >> username;
			cout << "\nPassword: ";
			cin >> password;
			cout << "\nVerify Password: ";
			cin >> passwordVerify;

			// Clear the display and show either a successful registration message or an error
			cout << CLEAN_DISPLAY_STR;
			if (password == passwordVerify)
			{
				cout << "\n\n================= SUCCESS ========================================\n\n"
						"Congratulations " << username << " you have been successfuly registered"
						"\n\n==================================================================\n\n\n\n";
			}
			else
			{
				cout << "\n\n================= ERROR =================\n\n"
						"Passwords must match"
						"\n\n=========================================\n\n\n\n";
			}

			break;
		case LOGIN_AS_GUEST:
			// Clear the display and show a guest login message
			cout << CLEAN_DISPLAY_STR;
			cout << "\n\n============= Hello Guest =============\n\n"
					"You are now logged in as a guest user"
					"\n\n========================================\n\n\n\n";
			break;
		case QUIT:
			break;
		default:
			// Clear the display and show invalid command message
			cout << CLEAN_DISPLAY_STR;
			cout << "\n\n================= ERROR =================\n\n"
				"Invalid Command!"
				"\n\n=========================================\n\n\n\n";
			break;
		}
	}
}