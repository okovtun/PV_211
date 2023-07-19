#include<iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "");
	for (int i = 0; i < 256; i++)
	{
		cout << i << "\t" << (char)i << endl;
	}
}