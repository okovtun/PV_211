#include<iostream>
using namespace std;

void elevator(int floor)
{
	if (floor <= 0)
	{
		cout << "Вы в подвале" << endl;
		return;
	}
	cout << "Вы на " << floor << " этаже" << endl;
	elevator(floor - 1);
	cout << "Вы на " << floor << " этаже" << endl;
}

int factorial(int n)
{
	if (n < 0)return 0;
	/*if (n == 0)return 1;
	else return n * factorial(n - 1);*/
	return n == 0 ? 1 : n * factorial(n - 1);
}
double power(double a, int n)
{
	//a - основание степени
	//n - показатель степени
	/*if (n == 0)return 1;
	else if (n > 0) return a * power(a, n - 1);
	else return 1 / power(a, -n);*/
	return n == 0 ? 1 : n > 0 ? a * power(a, n - 1) : 1 / power(a, -n);
}

void main()
{
	setlocale(LC_ALL, "");
	//cout << "Hello Recursion!";
	/*int n;
	cout << "Введите номер этажа: "; cin >> n;
	elevator(n);*/

	/*int n;
	cout << "Введите число: "; cin >> n;
	cout << factorial(n) << endl;*/

	int a;
	int n;
	cout << "Введите основание степени: "; cin >> a;
	cout << "Введите показатель степени: "; cin >> n;
	cout << a << " ^ " << n << " = " << power(a, n) << endl;

	//main();
}