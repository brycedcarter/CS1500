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
		FLOAT_SET
	};

	enum ErrorHandlingMethod
	{
		BREAK,
		RETRY
	};

	class Outputter
	{
	public:
		static void printFloat(float value, int precision);
		static void printDollarValue(float value);
		static void printSelectionList(std::string* list, int listLength);
	};

	class InputChecker 
	{
	public:
		void setBounds(float lower, float upper);
		void setMatchingSet(const float* arr, int setSize);
		bool removeFromMatchingSet(float numToRemove);
		bool addToMatchingSet(float numToAdd);
		void setBoundsTypes(bool lowerInclusive, bool upperInclusive);
		void setErrorHandling(ErrorHandlingMethod onError);
		void setErrorHandling(ErrorHandlingMethod onError, std::string errorMessage);

	protected:
		InputChecker();
		~InputChecker();

		bool processError();
		void cleanCin();

		InputCheckType checkType;
		float lowerBound;
		float upperBound;
		int setSize;
		float* matchingSet;
		bool upperBoundInclusive;
		bool lowerBoundInclusive;
		ErrorHandlingMethod onError;
		std::string errorMessage;
	};

	//============================== StringInputCheker ============================
	//=============================================================================

	class StringInputChecker : public InputChecker
	{
	public:
		StringInputChecker(InputCheckType check);
		~StringInputChecker() {};
		bool check(std::string input);
		std::string getInput();
		std::string getInput(std::string prompt);

	private:
		std::string handleError(std::string inputPrompt);

	};

	//============================== IntInputCheker ============================
	//==========================================================================

	class IntInputChecker : public InputChecker
	{
	public:
		IntInputChecker(InputCheckType check);
		~IntInputChecker() {};
		bool check(std::string input);
		int getInput();
		int getInput(std::string prompt);

	private:
		int handleError(std::string inputPrompt);

	};

	//============================== FloatInputCheker ============================
	//============================================================================

	class FloatInputChecker : public InputChecker
	{
	public:
		FloatInputChecker(InputCheckType check);
		~FloatInputChecker() {};
		bool check(std::string input);
		float getInput();
		float getInput(std::string prompt);


	private:
		float handleError(std::string inputPrompt);

	};

}