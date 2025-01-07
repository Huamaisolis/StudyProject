#pragma once
#include <string>
#include <iostream>

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