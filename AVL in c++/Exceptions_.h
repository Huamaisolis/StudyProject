#ifndef Exceptions_
#define Exceptions_
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class illegalParameterValue
{
public:
	illegalParameterValue() :message("Illegal parameter value") {}
	illegalParameterValue(const char* theMessage) { message = theMessage; }
	illegalParameterValue(string theMessage) { message = theMessage; }
	void outputMessage() const { cout << message << endl; }
private:
	string message;
};

class queueEmpty
{
public:
	queueEmpty() :message("queueEmpty") {}
	queueEmpty(const char* theMessage) { message = theMessage; }
	queueEmpty(string theMessage) { message = theMessage; }
	void outputMessage() const { cout << message << endl; }
private:
	string message;
};

class insertFalse
{
public:
	insertFalse() :message("queueEmpty") {}
	insertFalse(const char* theMessage) { message = theMessage; }
	insertFalse(string theMessage) { message = theMessage; }
	void outputMessage() const { cout << message << endl; }
private:
	string message;
};

<<<<<<< HEAD:AVL in c++/Exceptions_.h
#endif
=======
#endif
>>>>>>> 9fde6a686f40215d44f80bf1cc088be4436b0b93:Exceptions_.h
