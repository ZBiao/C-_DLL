#include "MyDLL.h"

CMyDLL::CMyDLL(void)
{
}

CMyDLL::~CMyDLL(void)
{
}

double CMyDLL::Add(double a, double b)
{
	return a + b;
}

double CMyDLL::Subtract(double a, double b)
{
	return a - b;
}

double CMyDLL::Multiply(double a, double b)
{
	return a * b;
}

double CMyDLL::Divide(double a, double b)
{
	if (b == 0)
	{
		 printf("b cannot be zero!");
	}

	return a / b;
}

extern "C" DLL_API CMyDLL* GetCMyDLL()
{
	return new CMyDLL();
}