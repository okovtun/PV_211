#include"String.h"

#define HOME_WORK

void main()
{
	setlocale(LC_ALL, "");
	/*String str;
	str.print();*/

#ifdef HOME_WORK
	String str1 = "Hello";
	str1 = str1;
	cout << str1 << endl;

	String str2 = "World";
	cout << str2 << endl;

	//String str3 = str1 + str2;	//Copy constructor
	String str3;
	str3 = str1 + str2;	//Copy assignment
	cout << str3 << endl;

	str1 += str2;
	cout << str1 << endl;

	String str4 = str1;
	cout << str4 << endl;
#endif // HOME_WORK

	//MoveMethods:
	//"The rule of three": CopyConstructor, CopyAssignment, ~Destructor
	//"The rule of zero"
	//C++ 11
	//"The rule of five":  MoveConstructor, MoveAssignment
}