#pragma once
#include <iostream> 

#define DLL_EXPORT
#if defined DLL_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

class DLL_API CMyDLL
{
public:
	CMyDLL(void);
	~CMyDLL(void);

public: 	 
    static double Add(double a, double b); 
	static double Subtract(double a, double b); 	 
	static double Multiply(double a, double b); 	 
	static double Divide(double a, double b); 
};

extern "C" DLL_API CMyDLL* GetCMyDLL(); //获取类CMyDLL的对象  