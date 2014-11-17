#include <iostream>
#include <string>
using namespace std;

enum DepartmentType
{
	HR, ENGINEERING, SALES, MARKETING
};

class Employee
{
private:
	string firstName;
	string lastName;
	double salary;
	DepartmentType departmentType;
public:
	void display()
	{
		cout << firstName << " " << lastName << " $" << salary << endl;
	}
	Employee(){}
	Employee(string fName, string lName, double salary, DepartmentType dept)
	{
		setFirstName(fName);
		setLastName(lName);
		setSalary(salary);
		setDepartmentType(dept);
	}
	void setFirstName(string fName)
	{
		this->firstName = fName;
	}
	void setLastName(string lName)
	{
		this->lastName = lName;
	}
	void setSalary(double salary)
	{
		if (salary > 0)
		{
			this->salary = salary;
		}
	}
	void setDepartmentType(DepartmentType departmentType)
	{
		this->departmentType = departmentType;
	}
	string getFirstName() { return firstName; }
	string getLastName()  { return lastName; }
	double getSalary()    { return salary; }
	DepartmentType getDepartmentType() { return departmentType; }
};

struct EmployeeNode
{
	Employee* employee;
	EmployeeNode* left = NULL;
	EmployeeNode* right = NULL;
	EmployeeNode* queueNext = NULL;
	EmployeeNode(){}
	EmployeeNode(Employee* employee)
	{
		this->employee = employee;
	}
};

class EmployeeNodeQueue
{
private:
	EmployeeNode* front = NULL;
	EmployeeNode* back = NULL;
public:
	void enqueue(EmployeeNode* node);
	EmployeeNode* dequeue();
	EmployeeNodeQueue(){}
};

class EmployeeBinarySearchTree
{
private:
	EmployeeNode* root = NULL;
	void insert(EmployeeNode* node, EmployeeNode** root);
	void traverseInOrder(EmployeeNode* root);
	void traversePreOrder(EmployeeNode* root);
	void traversePostOrder(EmployeeNode* root);
	Employee* depthFirstSearch(string firstName, EmployeeNode* root);
	void remove(string firstName, EmployeeNode* root, EmployeeNode** parentsChild);
	EmployeeNode* getMinNode(EmployeeNode* root);
public:
	void insert(Employee* employee);
	void remove(string firstName);
	Employee* depthFirstSearch(string firstName);
	void traverseInOrder();
	void traversePreOrder();
	void traversePostOrder();
	void traverseBreadthFirst();
};

void EmployeeNodeQueue::enqueue(EmployeeNode* node)
{
	if (node != NULL)
	{
		if (this->front == NULL)
		{
			this->front = node;
		}
		else
		{
			this->back->queueNext = node;
		}
		this->back = node;
	}
}

EmployeeNode* EmployeeNodeQueue::dequeue()
{
	EmployeeNode* removedNode;
	if (this->front == NULL)
	{
		removedNode = NULL;
	}
	else
	{
		removedNode = this->front;
		this->front = removedNode->queueNext;
		removedNode->queueNext = NULL;
	}
	
	return removedNode;
}

void EmployeeBinarySearchTree::insert(EmployeeNode* node, EmployeeNode** root)
{

	if (*root == NULL)
	{
		*root = node;
	}
	else
	{
		if (node->employee->getFirstName().compare((*root)->employee->getFirstName()) < 0)
		{
			this->insert(node, &(*root)->left);
		}
		else if (node->employee->getFirstName().compare((*root)->employee->getFirstName()) > 0)
		{
			this->insert(node, &(*root)->right);
		}
		else
		{
			cout << "======= ERROR! =======\n================\nNode with same key value already exists!\nInsertion was NOT performed.\n====================";
		}
	}
}

void EmployeeBinarySearchTree::insert(Employee* employee)
{
	EmployeeNode* node = new EmployeeNode(employee);
	this->insert(node, &(this->root));
}

void EmployeeBinarySearchTree::traverseInOrder(EmployeeNode* root)
{
	if (root->left != NULL)
	{
		this->traverseInOrder(root->left);
	}
	root->employee->display();
	if (root->right != NULL)
	{
		this->traverseInOrder(root->right);
	}
}

void EmployeeBinarySearchTree::traverseInOrder()
{
	this->traverseInOrder(this->root);
}

void EmployeeBinarySearchTree::traversePreOrder(EmployeeNode* root)
{
	root->employee->display();
	if (root->left != NULL)
	{
		this->traversePreOrder(root->left);
	}
	if (root->right != NULL)
	{
		this->traversePreOrder(root->right);
	}
}

void EmployeeBinarySearchTree::traversePreOrder()
{
	this->traversePreOrder(this->root);
}

void EmployeeBinarySearchTree::traversePostOrder(EmployeeNode* root)
{
	if (root->left != NULL)
	{
		this->traversePostOrder(root->left);
	}
	if (root->right != NULL)
	{
		this->traversePostOrder(root->right);
	}
	root->employee->display();
}

void EmployeeBinarySearchTree::traversePostOrder()
{
	this->traversePostOrder(this->root);
}

void EmployeeBinarySearchTree::traverseBreadthFirst()
{
	EmployeeNodeQueue queue = EmployeeNodeQueue();
	EmployeeNode* currentNode;
	queue.enqueue(this->root);
	currentNode = queue.dequeue();
	do 
	{
		queue.enqueue(currentNode->left);
		queue.enqueue(currentNode->right);
		currentNode->employee->display();
		currentNode = queue.dequeue();
	} while (currentNode != NULL);
}

Employee* EmployeeBinarySearchTree::depthFirstSearch(string firstName, EmployeeNode* root)
{
	if (root == NULL)
	{
		return NULL;
	}
	else
	{
		int compareValue = firstName.compare(root->employee->getFirstName());
		if (compareValue == 0)
		{
			return root->employee;
		}
		else if (compareValue < 0)
		{
			return this->depthFirstSearch(firstName, root->left);
		}
		else if (compareValue > 0)
		{
			return this->depthFirstSearch(firstName, root->right);
		}
	}
}

EmployeeNode* EmployeeBinarySearchTree::getMinNode(EmployeeNode* root)
{
	if (root->left == NULL)
	{
		return root;
	}
	else
	{
		return this->getMinNode(root->left);
	}
}

Employee* EmployeeBinarySearchTree::depthFirstSearch(string firstName)
{
	return this->depthFirstSearch(firstName, this->root);
}

void EmployeeBinarySearchTree::remove(string firstName, EmployeeNode* root, EmployeeNode** parentsChild)
{
	if (root == NULL)
	{
		cout << "Value did not exist in tree and thus could not be removed" << endl;
		return;
	}

	int compareValue = firstName.compare(root->employee->getFirstName());

	if (compareValue < 0)
	{
		this->remove(firstName, root->left, &root->left);
	}
	else if (compareValue > 0)
	{
		this->remove(firstName, root->right, &root->right);
	}
	else if (compareValue == 0)
	{

		if (root->left != NULL && root->right != NULL)
		{
			EmployeeNode* copyMin = new EmployeeNode(this->getMinNode(root->right)->employee);
			*parentsChild = copyMin;
			copyMin->left = root->left;
			copyMin->right = root->right;
			this->remove(copyMin->employee->getFirstName(), root->right, &copyMin->right);
		}
		else if (root->left != NULL)
		{
			*parentsChild = root->left;
		}
		else if (root->right != NULL)
		{
			*parentsChild = root->right;
		}
		else
		{
			*parentsChild = NULL;
		}
		delete root;

	}
}

void EmployeeBinarySearchTree::remove(string firstName)
{
	cout << "\n\nRemoving: " << firstName << endl;
	this->remove(firstName, root, &this->root);
}


int main()
{
	Employee* alice = new Employee("Alice", "Wonderland", 3211232, ENGINEERING);
	Employee* bob = new Employee("Bob", "Marley", 3211232, MARKETING);
	Employee* charlie = new Employee("Charlie", "Gargia", 3211232, MARKETING);
	Employee* dan = new Employee("Daniel", "Craig", 123123, HR);
	Employee* edward = new Employee("Edward", "Norton", 21211212, ENGINEERING);
	Employee* frank = new Employee("Frank", "Herbert", 233223, SALES);
	Employee* gregory = new Employee("Gregory", "Peck", 344334, MARKETING);

	EmployeeBinarySearchTree* tree = new EmployeeBinarySearchTree();

	tree->insert(dan);
	tree->insert(bob);
	tree->insert(alice);
	tree->insert(charlie);
	tree->insert(frank);
	tree->insert(edward);
	tree->insert(gregory);


	/*
	The tree now looks like this:
	Daniel
	Bob				Frank
	Alice		Charlie		Edward		Gregory
	*/

	cout << endl << "In Order: " << endl;
	tree->traverseInOrder();

	cout << endl << "Pre Order: " << endl;
	tree->traversePreOrder();

	cout << endl << "Post Order: " << endl;
	tree->traversePostOrder();

	cout << endl << "Depth First Search: " << endl;
	Employee* found = tree->depthFirstSearch("Bob");
	if (found != NULL)
	{
		found->display();
	}
	else
	{
		cout << "Not Found" << endl;
	}

	cout << endl << "Breadth First Traversal: " << endl;
	tree->traverseBreadthFirst();

	tree->remove("Frank");
	cout << endl << "Breadth First Traversal: " << endl;
	tree->traverseBreadthFirst();
	tree->remove("Gregory");
	cout << endl << "Breadth First Traversal: " << endl;
	tree->traverseBreadthFirst();
	tree->remove("Edward");
	cout << endl << "Breadth First Traversal: " << endl;
	tree->traverseBreadthFirst();
	tree->remove("Daniel");
	cout << endl << "Breadth First Traversal: " << endl;
	tree->traverseBreadthFirst();

	getchar();
}

/*
Sample Output:
In Order:
Alice Wonderland $3.21123e+006
Bob Marley $3.21123e+006
Charlie Gargia $3.21123e+006
Daniel Craig $123123
Edward Norton $2.12112e+007
Frank Herbert $233223
Gregory Peck $344334
Pre Order:
Daniel Craig $123123
Bob Marley $3.21123e+006
Alice Wonderland $3.21123e+006
Charlie Gargia $3.21123e+006
Frank Herbert $233223
Edward Norton $2.12112e+007
Gregory Peck $344334
Post Order:
Alice Wonderland $3.21123e+006
Charlie Gargia $3.21123e+006
Bob Marley $3.21123e+006
Edward Norton $2.12112e+007
Gregory Peck $344334
Frank Herbert $233223
Daniel Craig $123123
Depth First Search:
Bob Marley $3.21123e+006
Breadth First Search:
Frank Herbert $233223
*/