#include <string>

namespace BDC
{
	class IO_Helper
	{
	public:
		static int test(int in);
}

//namespace BDC
//{
//	enum InputCheckType
//	{
//		MULTI_WORD,
//		SINGLE_WORD,
//		INT,
//		FLOAT
//	};
//
//	enum ErrorHandlingMethod
//	{
//		BREAK,
//		RETRY
//	};
//
//	class IO_Helper
//	{
//	public:
//		template <typename returnType> 
//		static returnType getInput(InputCheckType check);
//		template <typename returnType> 
//		static returnType getInput(InputCheckType check, ErrorHandlingMethod onError);
//		template <typename returnType> 
//		static returnType getInput(InputCheckType check, ErrorHandlingMethod onError, std::string errorMessage);
//
//	};
//}