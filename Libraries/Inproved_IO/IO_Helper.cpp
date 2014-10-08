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

	template <typename returnType>
	returnType BDC::IO_Helper::getInput(InputCheckType check)
	{
		return getInput<returnType>(check, BREAK);
	}

	template <typename returnType>
	static returnType BDC::IO_Helper::getInput(InputCheckType check, ErrorHandlingMethod onError)
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
	static returnType BDC::IO_Helper::getInput(InputCheckType check, ErrorHandlingMethod onError, std::string errorMessage)
	{
		
		string inputLine;
		getline(cin, inputLine);

		switch (check)
		{
		case MULTI_WORD:
			{
						   string output
			}
			break;
		case SINGLE_WORD:
			break;
		case INT:
		{
					string firstWord = inputLine.substr(0, inputLine.find(" "));
		}
			break;
		case FLOAT:
			cin >> output;
			break;
		}
		return (returnType)output;

	}
}
