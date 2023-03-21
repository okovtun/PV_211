#include<iostream>
using namespace std;

void HelloWorld()
{
	cout << "HelloWorld" << endl;
}

void main()
{
	setlocale(LC_ALL, "");
	cout << HelloWorld << endl;
	cout << &HelloWorld << endl;
	cout << typeid(HelloWorld).name() << endl;
	void(*pf)() = HelloWorld;
	pf();
	cout << typeid(pf).name() << endl;
}