/*********************************************
 * MyDLL.dll ��C++��̷�ʽ������ʵ����غ��� 
 * ����̬���á�.dll�еĺ���������C++�к��������أ�
 * ����.dll�еĺ�����C++��ʹ��ʱ��������������
 * �ı��뷽ʽ�Ժ������±��룬�������£�
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
	typedef double(*FunctionAdd)(double,double);  //����ָ��
	FunctionAdd pAdd = NULL;

	HINSTANCE  hDll = LoadLibraryA("MyDLL.dll");   	
	if(NULL != hDll)
	{
		 //���÷�ʽһ��ͨ���������ҵ����������صĺ����������£� 
		 //pAdd =(FunctionAdd)GetProcAddress(hDll, "?Add@CMyDLL@@SANNN@Z");
		 //���÷�ʽ����ͨ���������ҵ����������غ���dll�е���ţ����£�
		 pAdd = (FunctionAdd)GetProcAddress(hDll, reinterpret_cast<LPCSTR>(MAKEINTRESOURCE(4)));
		 if(pAdd != 0)
		 { 			 
			 cout<<"Add(2.3,2.3) = "<<pAdd(2.3,2.3)<<endl;
			 system("pause");			
		 }	
	}
	FreeLibrary(hDll);
#else 
	//���÷�ʽ����δʵ��
	HINSTANCE  hDll = LoadLibraryA("MyDLL.dll");   

	typedef CMyDLL * (*GetCMyDLL)(); //���庯��ָ��,��ȡ��GetCMyDLL����  
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
 * MyDLL.dll ��C++��̷�ʽ������ʵ����غ��� 
 * ����̬̬���á�.dll�еĺ���,�����ǵ���
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
