#include "IO_Helper.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;
namespace BDC
{
	void BDC::Outputter::printFloat(float value, int precision)
	{
		ios  state(NULL);
		state.copyfmt(cout);
		cout << fixed;
		cout << setprecision(2);
		cout << value;
		cout.copyfmt(state);
	}

	void BDC::Outputter::printDollarValue(float value)
	{
		cout << "$";
		BDC::Outputter::printFloat(value, 2);
	}

	void BDC::Outputter::printSelectionList(string* list,const int listLength)
	{
		for (int i = 0; i < listLength; i++)
		{
			cout << "[" << i << "] " << list[i];
		}
	}

	BDC::InputChecker::InputChecker()
	{
		float tempArray[3] = { 0, 1, 2 };
		this->setMatchingSet(tempArray, 3);

		this->errorMessage = ("\n\n\n\nInvalid input!\n The program will now close.\n\n\n\n");
		this->lowerBound = 0;
		this->upperBound = 3;
		this->lowerBoundInclusive = true;
		this->upperBoundInclusive = true;
		this->onError = BREAK;
	}

	BDC::InputChecker::~InputChecker()
	{
		delete[] this->matchingSet;
	}

	void BDC::InputChecker::setBounds(float lower, float upper)
	{
		if (upper < lower)
		{
			upper = lower;
		}

		this->lowerBound = lower;
		this->upperBound = upper;
	}

	void BDC::InputChecker::setMatchingSet(const float* arr, int setSize)
	{
		this->matchingSet = new float[setSize];
		this->setSize = setSize;
		for (int i = 0; i < setSize; i++)
		{
			this->matchingSet[i] = arr[i];
		}
	}

	bool BDC::InputChecker::removeFromMatchingSet(float numToRemove)
	{
		int countInArray = 0;
		for (int i = 0; i < this->setSize; i++)
		{
			if (this->matchingSet[i] == numToRemove)
			{
				countInArray += 1;
			}
		}

		int newSize = this->setSize - countInArray;
		float* newSet = new float[newSize];
		int insertIndex = 0;
		for (int i = 0; i < this->setSize; i++)
		{
			if (this->matchingSet[i] != numToRemove)
			{
				newSet[insertIndex] = this->matchingSet[i];
				insertIndex++;
			}
		}

		this->matchingSet = newSet;
		this->setSize = newSize;

		if (countInArray > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool BDC::InputChecker::addToMatchingSet(float numToAdd)
	{
		int newSize = this->setSize+1;
		float* newSet = new float[newSize];

		int i = 0;
		for (i; i < this->setSize; i++)
		{
			if (this->matchingSet[i] == numToAdd)
			{
				return false;
			}
			else
			{
				newSet[i] = this->matchingSet[i];
			}
		}
		newSet[i] = numToAdd;

		this->matchingSet = newSet;
		this->setSize = newSize;

		return true;
	}

	void BDC::InputChecker::setBoundsTypes(bool lowerInclusive, bool upperInclusive)
	{
		this->lowerBoundInclusive = lowerInclusive;
		this->upperBoundInclusive = upperInclusive;
	}

	void BDC::InputChecker::setErrorHandling(ErrorHandlingMethod onError)
	{
		this->onError = onError;
	}

	void BDC::InputChecker::setErrorHandling(ErrorHandlingMethod onError, string errorMessage)
	{
		this->onError = onError;
		this->errorMessage = "\n\n\n"
							 "============= ERROR =============\n"
							 "=================================\n\n"
							 +errorMessage+"\n\n"
							 "=================================\n"
							 "\n\n\n";
	}

	bool BDC::InputChecker::processError()
	{
		this->cleanCin();

		cout << this->errorMessage;
		switch (this->onError)
		{
		case BDC::BREAK:
			exit(400);
			break;
		case BDC::RETRY:
			return true;
			break;
		default:
			exit(400);
			break;
		}
	}

	void BDC::InputChecker::cleanCin()
	{
		cin.clear();
		if (cin.rdbuf()->in_avail() > 0)
		{
			cin.ignore(INT_MAX);
		}
	}

	//============================== StringInputCheker ============================
	//=============================================================================

	BDC::StringInputChecker::StringInputChecker(InputCheckType check)
		: BDC::InputChecker()
	{
		this->checkType = check;
	}

	bool BDC::StringInputChecker::check(string input)
	{
		istringstream inputStream(input);
		switch (this->checkType)
		{
		case SINGLE_WORD:
		{
			string word;
			inputStream >> word;
			if (inputStream.rdbuf()->in_avail() > 1)
			{
				return false;
			}	
			else
			{
				return true;
			}
			break;
		}
		case MULTI_WORD:
			return true;
			break;
		default:
			return false;
			break;
		}
	}

	string BDC::StringInputChecker::getInput()
	{
		return this->getInput("");
	}

	string BDC::StringInputChecker::getInput(string prompt)
	{
		// Display input prompt
		cout << prompt;

		string inputLine;
		getline(cin, inputLine);
		if (!this->check(inputLine))
		{
			return this->handleError(prompt);
		}

		this->cleanCin();
		return inputLine;
	}

	string BDC::StringInputChecker::handleError(string inputPrompt)
	{
		if (this->processError())
		{
			return this->getInput(inputPrompt);
		}
		else
		{
			exit(400);
		}
	}

	//============================== IntInputCheker ============================
	//==========================================================================

	BDC::IntInputChecker::IntInputChecker(InputCheckType check)
		: BDC::InputChecker()
	{
		this->checkType = check;
	}

	bool BDC::IntInputChecker::check(string input)
	{
		istringstream inputStream(input);

		int inInt;
		if (!(inputStream >> inInt))
		{
			return false;
		}
		else if(inputStream.rdbuf()->in_avail() > 1)
		{
			return false;
		}

		switch (this->checkType)
		{
		case BDC::INT:
		{
			return true;
			break;
		}
		case BDC::INT_RANGE:
			if (this->lowerBoundInclusive)
			{
				if (this->upperBoundInclusive)
				{
					if(inInt >= this->lowerBound && inInt <= this->upperBound)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					if(inInt >= this->lowerBound && inInt < this->upperBound)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				if (this->upperBoundInclusive)
				{
					if(inInt > this->lowerBound && inInt <= this->upperBound)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					if(inInt > this->lowerBound && inInt < this->upperBound)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			break;
		case BDC::INT_SET:
			for (int i=0; i < this->setSize; i++)
			{
				if (inInt == this->matchingSet[i])
				{
					return true;
				}
			}
			return false;
			break;
		default:
			return false;
			break;
		}
	}

	int BDC::IntInputChecker::getInput()
	{
		return this->getInput("");
	}

	int BDC::IntInputChecker::getInput(string prompt)
	{
		// Display input prompt
		cout << prompt;

		string inputLine;
		getline(cin, inputLine);
		if (!this->check(inputLine))
		{
			return this->handleError(prompt);
		}
		istringstream inputStream(inputLine);
		int inInt;
		inputStream >> inInt;

		this->cleanCin();
		return inInt;
	}

	int BDC::IntInputChecker::handleError(string inputPrompt)
	{
		if (this->processError())
		{
			return this->getInput(inputPrompt);
		}
		else
		{
			exit(400);
		}
	}

	//============================== FloatInputCheker ============================
	//============================================================================

	BDC::FloatInputChecker::FloatInputChecker(InputCheckType check)
		: BDC::InputChecker()
	{
		this->checkType = check;
	}

	bool BDC::FloatInputChecker::check(string input)
	{
		istringstream inputStream(input);

		float inFloat;
		if (!(inputStream >> inFloat))
		{
			return false;
		}
		else if(inputStream.rdbuf()->in_avail() > 1)
		{
			return false;
		}

		switch (this->checkType)
		{
		case BDC::FLOAT:
		{
			return true;
			break;
		}
		case BDC::FLOAT_RANGE:
			if (this->lowerBoundInclusive)
			{
				if (this->upperBoundInclusive)
				{
					if(inFloat >= this->lowerBound && inFloat <= this->upperBound)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					if(inFloat >= this->lowerBound && inFloat < this->upperBound)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				if (this->upperBoundInclusive)
				{
					if(inFloat > this->lowerBound && inFloat <= this->upperBound)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					if(inFloat > this->lowerBound && inFloat < this->upperBound)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			break;
		case BDC::FLOAT_SET:
			for (int i=0; i < this->setSize; i++)
			{
				if (inFloat == this->matchingSet[i])
				{
					return true;
				}
			}
			return false;
			break;
		default:
			return false;
			break;
		}
	}

	float BDC::FloatInputChecker::getInput()
	{
		return this->getInput("");
	}

	float BDC::FloatInputChecker::getInput(string prompt)
	{
		// Display input prompt
		cout << prompt;

		string inputLine;
		getline(cin, inputLine);
		if (!this->check(inputLine))
		{
			return this->handleError(prompt);
		}
		istringstream inputStream(inputLine);
		float inFloat;
		inputStream >> inFloat;

		this->cleanCin();
		return inFloat;
	}

	float BDC::FloatInputChecker::handleError(string inputPrompt)
	{
		if (this->processError())
		{
			return this->getInput(inputPrompt);
		}
		else
		{
			exit(400);
		}
	}
}

