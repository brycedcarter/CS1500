#include <string>

namespace BDC
{
	enum InputCheckType
	{
		MULTI_WORD,
		SINGLE_WORD,
		SINGLE_WORD_SET,
		INT,
		INT_RANGE,
		INT_SET,
		FLOAT,
		FLOAT_RANGE,
		FLOAT_SET,
		POS_INT,
		POS_FLOAT
	};

	enum ErrorHandlingMethod
	{
		BREAK,
		RETRY
	};

	class IO_Helper
	{
	public:
		template <typename returnType> 
		static inline returnType getInput(InputCheckType check);
		template <typename returnType> 
		static returnType getInput(static *InputChecker check, ErrorHandlingMethod onError);
		template <typename returnType>
		static returnType getInput(static *InputChecker check, ErrorHandlingMethod onError, std::string errorMessage);

		static std::string getInput(static *InputChecker<string> check, ErrorHandlingMethod onError, std::string errorMessage, std::string typeVar);
		static int getInput(static *InputChecker check, ErrorHandlingMethod onError, std::string errorMessage, int typeVar);
		static float getInput(static *InputChecker check, ErrorHandlingMethod onError, std::string errorMessage, float typeVar);

		static std::string getInputString(static *InputChecker check, ErrorHandlingMethod onError, std::string errorMessage);
		static int getInputInt(static *InputChecker check, ErrorHandlingMethod onError, std::string errorMessage);
		static float getInputFloat(static *InputChecker check, ErrorHandlingMethod onError, std::string errorMessage);

		template <typename returnType>
		static returnType raiseError(ErrorHandlingMethod onError, std::string errorMessage, InputCheckType check, 
			returnType(*callBack)(InputCheckType check, ErrorHandlingMethod onError, std::string errorMessage));

	};


	template <class inputType>
	class InputChecker
	{
		InputChecker();
		InputChecker(InputCheckType check);
		bool check(inputType input);
	private:
		InputCheckType checkType;
		float lowerBound = 0;
		float upperBound = 3;
		int setSize = 3;
		int intSet[3] = { 0, 1, 2 };
		float floatSet[3] = { 0, 1, 2 };
		string wordSet[3] = { "zero", "one", "two" };
		bool upperBoundInclusive = true;
		bool lowerBoundInclusive = true;
	};
}