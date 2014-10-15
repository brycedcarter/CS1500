#include "IO_Helper.h"
#include <string>
#include <iostream>

using namespace std;
namespace BDC
{
	template string BDC::IO_Helper::getInput<string>(BDC::InputCheckType);
	template int BDC::IO_Helper::getInput<int>(BDC::InputCheckType);
	template float BDC::IO_Helper::getInput<float>(BDC::InputCheckType);

	template string BDC::IO_Helper::getInput<string>(BDC::InputCheckType, BDC::ErrorHandlingMethod);
	template int BDC::IO_Helper::getInput<int>(BDC::InputCheckType, BDC::ErrorHandlingMethod);
	template float BDC::IO_Helper::getInput<float>(BDC::InputCheckType, BDC::ErrorHandlingMethod);

	template string BDC::IO_Helper::getInput<string>(BDC::InputCheckType, BDC::ErrorHandlingMethod, string);
	template int BDC::IO_Helper::getInput<int>(BDC::InputCheckType, BDC::ErrorHandlingMethod, string);
	template float BDC::IO_Helper::getInput<float>(BDC::InputCheckType, BDC::ErrorHandlingMethod, string);

	template string BDC::IO_Helper::raiseError(ErrorHandlingMethod onError, std::string errorMessage, InputCheckType check,
		string(*callBack)(InputCheckType check, ErrorHandlingMethod onError, string errorMessage));

	template int BDC::IO_Helper::raiseError(ErrorHandlingMethod onError, std::string errorMessage, InputCheckType check,
		int(*callBack)(InputCheckType check, ErrorHandlingMethod onError, string errorMessage));

	template float BDC::IO_Helper::raiseError(ErrorHandlingMethod onError, std::string errorMessage, InputCheckType check,
		float(*callBack)(InputCheckType check, ErrorHandlingMethod onError, string errorMessage));

	template <typename returnType>
	returnType BDC::IO_Helper::getInput((returnType)(*checkFunction)(returnType))
	{
		return getInput<returnType>(check, BREAK);
	}

	template <typename returnType>
	returnType BDC::IO_Helper::getInput(InputCheckType check, ErrorHandlingMethod onError)
	{
		string errorMessage;
		switch (onError)
		{
		case BREAK:
			errorMessage = "\n\n\n\nInvalid input!\n The program will now close.\n\n";
			break;
		case RETRY:
			errorMessage = "\n\n\n\nInvalid input!\n\n Please try again: ";
			break;
		default:
			errorMessage = "\n\n\n\nInvalid input!\n\n";
		}
		return getInput<returnType>(check, onError, errorMessage);
	}

	template <typename returnType>
	returnType BDC::IO_Helper::getInput(InputCheckType check, ErrorHandlingMethod onError, string errorMessage)
	{
		returnType typeVar = 0;
		return getInput(check, onError, errorMessage, typeVar);
	}

	string BDC::IO_Helper::getInput(InputCheckType check, ErrorHandlingMethod onError, string errorMessage, string typeVar)
	{
		return getInputString(check, onError, errorMessage);
	}

	int BDC::IO_Helper::getInput(InputCheckType check, ErrorHandlingMethod onError, string errorMessage, int typeVar)
	{
		return getInputInt(check, onError, errorMessage);
	}

	float BDC::IO_Helper::getInput(InputCheckType check, ErrorHandlingMethod onError, string errorMessage, float typeVar)
	{
		return getInputFloat(check, onError, errorMessage);
	}




	string BDC::IO_Helper::getInputString(InputCheckType check, ErrorHandlingMethod onError, std::string errorMessage)
	{
		string output;
		string inputLine;
		getline(cin, inputLine);


		switch (check)
		{
		case MULTI_WORD:
			output = inputLine;
			break;
		case SINGLE_WORD:
			output = inputLine.substr(0, inputLine.find(" "));
			break;
		}
		cin.clear();
		cin.ignore(INT_MAX);
		return output;
	}

	int BDC::IO_Helper::getInputInt(InputCheckType check, ErrorHandlingMethod onError, std::string errorMessage)
	{
		int output;

		if (!(cin >> output))
		{
			output = BDC::IO_Helper::raiseError<int>(onError, errorMessage, check, &BDC::IO_Helper::getInputInt);
		}
		if (cin.rdbuf()->in_avail() > 1)
		{
			output = BDC::IO_Helper::raiseError<int>(onError, errorMessage, check, &BDC::IO_Helper::getInputInt);
		}

		switch (check)
		{
		case INT:
			break;
		case POS_INT:
			if (output < 0)
			{
				output = BDC::IO_Helper::raiseError(onError, errorMessage, check, &BDC::IO_Helper::getInputInt);
			}
			break;
		}
		return output;
	}

	float BDC::IO_Helper::getInputFloat(InputCheckType check, ErrorHandlingMethod onError, std::string errorMessage)
	{
		float output;

		if (!(cin >> output))
		{
			output = BDC::IO_Helper::raiseError<float>(onError, errorMessage, check, &BDC::IO_Helper::getInputFloat);
		}

		switch (check)
		{
		case FLOAT:
			break;
		case POS_FLOAT:
			if (output < 0)
			{
				output = BDC::IO_Helper::raiseError<float>(onError, errorMessage, check, &BDC::IO_Helper::getInputFloat);
			}
			break;
		}
		return output;
	}


	template <typename returnType>
	returnType BDC::IO_Helper::raiseError(ErrorHandlingMethod onError, std::string errorMessage, InputCheckType check,
		returnType(*callBack)(InputCheckType, ErrorHandlingMethod, string))
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << errorMessage;
		switch (onError)
		{
		case BDC::BREAK:
			exit(400);
			break;
		case BDC::RETRY:
			return (*callBack)(check, onError, errorMessage);
			break;
		default:
			exit(400);
			break;
		}
	}

	template <class inputType>
	bool BDC::InputChecker::check(inputType input)
	{
		switch (this->checkType)
		{
		case BDC::InputCheckType::INT:
		default:
			break;
		}
	}
}