/*********************************************
 * MyDLL.dll 以C++编程方式声明和实现相关函数 
 * 【动态调用】.dll中的函数，由于C++有函数的重载，
 * 导致.dll中的函数在C++中使用时，编译器以自身
 * 的编码方式对函数重新编码，例子如下：
 * Add() <===> ?Add@CMyDLL@@SANNN@Z 
 ********************************************/

#include "stdio.h"
#include <stdlib.h>
#include "windows.h"
#include <iostream>

#define MODE_CLASS
#ifndef MODE_CLASS
#pragma comment(lib,"MyDLL.lib")
#endif  

using namespace std;

int main(int argc, char * argv[])
{
#ifdef MODE_CLASS
	typedef double(*FunctionAdd)(double,double);  //函数指针
	FunctionAdd pAdd = NULL;

	HINSTANCE  hDll = LoadLibraryA("MyDLL.dll");   	
	if(NULL != hDll)
	{
		 //调用方式一：通过反编译找到函数被重载的函数名，如下： 
		 //pAdd =(FunctionAdd)GetProcAddress(hDll, "?Add@CMyDLL@@SANNN@Z");
		 //调用方式二：通过反编译找到函数被重载后在dll中的序号，如下：
		 pAdd = (FunctionAdd)GetProcAddress(hDll, reinterpret_cast<LPCSTR>(MAKEINTRESOURCE(4)));
		 if(pAdd != 0)
		 { 			 
			 cout<<"Add(2.3,2.3) = "<<pAdd(2.3,2.3)<<endl;
			 system("pause");			
		 }	
	}
	FreeLibrary(hDll);
#else 
	//调用方式三：未实现
	HINSTANCE  hDll = LoadLibraryA("MyDLL.dll");   

	typedef CMyDLL * (*GetCMyDLL)(); //定义函数指针,获取类GetCMyDLL对象  
	GetCMyDLL getCMyDLL=(GetCMyDLL)GetProcAddress(hDll,"GetCMyDLL");

	CMyDLL *mydll = getCMyDLL(); 

	if (getCMyDLL)
	{
		cout<<"Add(2.3,2.3) = "<<mydll->Add(2.3,2.3)<<endl;
		system("pause");
	}

#endif
	return 0;	 
}


/*********************************************
 * MyDLL.dll 以C++编程方式声明和实现相关函数 
 * 【静态态调用】.dll中的函数,下面是调用
 ********************************************/
//#pragma comment (lib,"MyDLL.lib")
//#include "MyDLL.h"
//
//int main(int argc,char **argv)
//{
//	double ret = CMyDLL::Add(2.3,2.3);
//	cout<<"ret = "<<ret<<endl;
//	system("pause");
//
//	return 0;
//}
