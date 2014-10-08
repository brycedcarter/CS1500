#include "IO_Helper.h"
#include <string>

using namespace std;
namespace BDC
{
	int IO_Helper::test(int in)
	{
		return in;
	}
}
//
//namespace BDC
//{
//
//	template <typename returnType>
//	static returnType getInput(InputCheckType check)
//	{
//		return getInput<returnType>(check, BREAK);
//	}
//
//	template <typename returnType>
//	static returnType getInput(InputCheckType check, ErrorHandlingMethod onError)
//	{
//		string errorMessage;
//		switch (onError)
//		{
//		case BREAK:
//			errorMessage = "\n\n\n\nInvalid input!\n The program will now close.\n\n";
//			break;
//		case RETRY:
//			errorMessage = "\n\n\n\nInvalid input!\n\n Please try again: ";
//			break;
//		default:
//			errorMessage = "\n\n\n\nInvalid input!\n\n";
//		}
//		return getInput<returnType>(check, onError, errorMessage);
//	}
//
//	template <typename returnType>
//	static returnType getInput(InputCheckType check, ErrorHandlingMethod onError, std::string errorMessage)
//	{
//		returnType output;
//		string inputLine;
//		getline(cin, inputLine);
//
//		switch (check)
//		{
//		case MULTI_WORD:
//			if (typeid(returnType) == typeid(string))
//			{
//				output = inputLine;
//			}
//			break;
//		case SINGLE_WORD:
//			if (typeid(returnType) == typeid(string))
//			{
//				output = inputLine.substr(0, inputLine.find(" "));
//			}
//			break;
//		case INT:
//			string firstWord = inputLine.substr(0, inputLine.find(" "));
//			break;
//		case FLOAT:
//			cin >> output;
//			break;
//		}
//		return (returnType)output;
//
//	}
//}