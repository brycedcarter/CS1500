#include <iostream>
#include <string>
using namespace std;

const int LOGIN = 1;
const int REGISTER = 2;
const int LOGIN_AS_GUEST = 3;
const int QUIT = 0;

struct user {
	string username;
	string password;
	string message;
} users[3];



int main() 
{
	short selection = -1;
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
		cout << "\n\n\n";
		switch (selection)
		{
		case LOGIN:
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
				"=======================================================\n"
				"LOGIN\n"
				"=======================================================\n\n";
			cout << "Username: ";
			cin >> username;
			cout << "\nPassword: ";
			cin >> password;
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
				;
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

			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
				"=======================================================\n"
				"REGISTER\n"
				"=======================================================\n\n";
			cout << "Username: ";
			cin >> username;
			cout << "\nPassword: ";
			cin >> password;
			cout << "\nVerify Password: ";
			cin >> passwordVerify;
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

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
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
			cout << "\n\n============= Hello Guest =============\n\n"
					"You are now logged in as a guest user"
					"\n\n========================================\n\n\n\n";
			break;
		case QUIT:
			break;
		default:
			cout << "Invalid Command!\n";
			break;
		}
	}
}