#include <iostream>
using namespace std;

const int CREATE_APPLICATION = 1;
const int LIST_APPLICATIONS = 2;
const int FIND_APPLICATIONS = 3;
const int CREATE_PAGE = 4;
const int LIST_PAGES = 5;
const int FIND_PAGES = 6;
const int QUIT = 0;



int main() {
	short selection = -1;
	while (selection != 0) {
		cout << "[1] Create an Application\n"
				"[2] List all Applications\n"
				"[3] Find Applications\n"
				"[4] Create a Page\n"
				"[5] List all Pages\n"
				"[6] Find Pages\n"
				"[0] Quit\n";
		cin >> selection;
		cout << "\n\n\n========================== You have chosen: ==========================\n\n";
		switch (selection) {
		case CREATE_APPLICATION:
			cout << "Create an Application\n";
			break;
		case LIST_APPLICATIONS:
			cout << "List all Applications\n";
			break;
		case FIND_APPLICATIONS:
			cout << "Find Applications\n";
			break;
		case CREATE_PAGE:
			cout << "Create a Page\n";
			break;
		case LIST_PAGES:
			cout << "List all Pages\n";
			break;
		case FIND_PAGES:
			cout << "Find Pages\n";
			break;
		case QUIT:
			cout << "Quit\n";
			break;
		default:
			cout << "Unknown Option\n";
			break;
		}
		cout << "\n======================================================================\n\n\n";
	}
}