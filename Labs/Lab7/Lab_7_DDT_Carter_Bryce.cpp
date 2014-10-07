#include <iostream>
#include <string>
using namespace std;

struct Employee {
	string firstName, lastName;
	float salary;
};

struct Department {
	string name;
	Employee director;
	Employee* employees;
	int currentSize;
	int maxSize;
};

void displayEmployee(Employee employee);
void displayDepartment(Department* department);
Employee createEmployee();
void addEmployee(Department* department, Employee employee);

int main()
{
	// create some employees
	Employee ada = { "Ada", "Lovelace", 325123 };
	Employee babbage = { "Charlie", "Babbage", 234432 };
	Employee turing = { "Alan", "Turing", 323323 };
	Employee von = { "John", "von Neumann", 432234 };

	displayEmployee(ada);

	// create an array of employees
	Employee* employees = new Employee[10];
	employees[0] = ada;
	employees[1] = babbage;
	employees[2] = turing;
	employees[3] = von;

	// create a "CS" department,
	// employee von is the directory,
	// the employees are the employees listed above,
	// currently has 4 employees,
	// with a max of 10 employees
	Department cs = { "CS", von, employees, 4, 10 };

	displayDepartment(&cs);
	Employee newEmployee = createEmployee();
	addEmployee(&cs, newEmployee);
	displayDepartment(&cs);
}

void displayEmployee(Employee employee)
{
	cout << employee.firstName << " " << employee.lastName << " $" << employee.salary << endl;
}

void displayDepartment(Department* department)
{
	cout << "Department: " << department->name << endl;
	cout << "Director: ";
	displayEmployee(department->director);
	cout << "Employees: " << endl;
	for (int i = 0; i < department->currentSize; i++)
	{
		displayEmployee(department->employees[i]);
	}

}

Employee createEmployee()
{
	Employee newEmployee;
	cout << "Employee First Name: ";
	cin >> newEmployee.firstName;
	cout << "Employee Last Name: ";
	cin >> newEmployee.lastName;
	cout << "Employee Salary: ";
	cin >> newEmployee.salary;
	cout << "\nNew employee created:";
	displayEmployee(newEmployee);
	cout << "\n\n\n";
	return newEmployee;
}

void addEmployee(Department* department, Employee employee)
{		
	if (department->maxSize > department->currentSize)
	{
		cout << "Adding employee === ";
		displayEmployee(employee);
		cout << " ==== to the " << department->name << " department\n\n";
		department->employees[department->currentSize] = employee;
		department->currentSize++;

	}
	else
	{
		cout << "Error! Could not add employee becase the department's maximum size has been reached";
	}
}