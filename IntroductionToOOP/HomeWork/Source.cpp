#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

class Fraction;
Fraction operator*(Fraction left, Fraction right);	//Прототип фугкции - объявление функции (Function declaration)
Fraction operator/(const Fraction& left, const Fraction& right);

class Fraction
{
	int integer;		//целая часть
	int numerator;		//числитель
	int denominator;	//знаменатель
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}
	//				Constructors:
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstructor:\t" << this << endl;
	}
	explicit Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "1ArgConstructor:\t" << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t\t" << this << endl;
	}

	//				Operators:
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this * other;	//Вызов функции - Function call (operator*)
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}

	Fraction& operator()(int integer, int numerator, int denominator)
	{
		set_integer(integer);
		set_numerator(numerator);
		set_denominator(denominator);
		return *this;
	}

	//				Type-cast operators:
	explicit operator int()
	{
		return integer;
	}

	//				Methods:
	Fraction& reduce()
	{
		int more, less, rest;
		if (numerator > denominator)more = numerator, less = denominator;
		else more = denominator, less = numerator;
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more;	//GCD - Greates Common Divisor (Наибольший общий делитель)
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction inverted()const
	{
		Fraction inverted = *this;	//копируем объект
		inverted.to_improper();
		std::swap(inverted.numerator, inverted.denominator);
		return inverted;
	}
	void print()const
	{
		if (integer)cout << integer;
		if (numerator)
		{
			if (integer) cout << "(";
			cout << numerator << "/" << denominator;
			if (integer) cout << ")";
		}
		else if (integer == 0)cout << 0;
		cout << endl;
	}
};

Fraction operator+(const Fraction& left, const Fraction& right)
{
	return Fraction
	(
		left.get_integer() + right.get_integer(),
		left.get_numerator() * right.get_denominator() + right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
}
Fraction operator*(Fraction left, Fraction right)	//Реализация функции - определение функции (Function definition)
{
	left.to_improper();
	right.to_improper();
	/*Fraction result;
	result.set_numerator(left.get_numerator()*right.get_numerator());
	result.set_denominator(left.get_denominator()*right.get_denominator());*/
	/*Fraction result
	(
		left.get_numerator()*right.get_numerator(),
		left.get_denominator()*right.get_denominator()
	);
	result.to_proper();
	return result;*/
	//создаем временный безымянный объект, и сразу же возвращаем его на место вызова.
	//Временные безымянные объекты существуют только в пределах одного выражения (до ;)
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
}
Fraction operator/(const Fraction& left, const Fraction& right)
{
	return left * right.inverted();
}

////////////////////////////////////////////////////////////////////////////////////
bool operator==(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return
		left.get_numerator() * right.get_denominator() ==
		right.get_numerator() * left.get_denominator();
}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);
	!true == false;
}
bool operator>(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return
		left.get_numerator() * right.get_denominator() >
		right.get_numerator() * left.get_denominator();
}
bool operator<(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return
		left.get_numerator() * right.get_denominator() <
		right.get_numerator() * left.get_denominator();
}
bool operator<=(const Fraction& left, const Fraction& right)
{
	return left < right || left == right;
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	return !(left < right);
}

////////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	if (obj.get_integer())os << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_integer()) os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer()) os << ")";
	}
	else if (obj.get_integer() == 0)os << 0;
	return os;
}
//#define PRIMITIVE_EXTRACTION
std::istream& operator>>(std::istream& is, Fraction& obj)
{
	//Оператор извлечения из потока (Extraction operator)

#ifdef PRIMITIVE_EXTRACTION
	int integer, numerator, denominator;
	is >> integer >> numerator >> denominator;
	/*obj.set_integer(integer);
	obj.set_numerator(numerator);
	obj.set_denominator(denominator);*/
	obj(integer, numerator, denominator);
#endif // PRIMITIVE_EXTRACTION

	const int SIZE = 256;
	char buffer[SIZE] = {};
	char delimiters[] = "/ ()";
	int number[3] = {};
	//is >> buffer;
	is.getline(buffer, SIZE);

	int n = 0;	//счетчик чисел, извлеченных из строки
	for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
		number[n++] = atoi(pch);
	//for (int i = 0; i < n; i++)cout << number[i] << "\t"; cout << endl;

	obj = Fraction();	//Обнуляем объект, сбрасываем его до объекта по умолчанию.
	switch (n)
	{
	case 1: obj.set_integer(number[0]); break;
	case 2: obj.set_numerator(number[0]); obj.set_denominator(number[1]); break;
	case 3: obj(number[0], number[1], number[2]);
	}
	return is;
}
////////////////////////////////////////////////////////////////////////////////////

//#define CONSTRUCTORS_CHECK
//#define ARITHMETICAL_OPERATORS_CHECK
//#define IOSTREAM_OPERATORS_CHECK
//#define TYPE_CONVERSIONS_BASICS
//#define CONVERSION_FROM_OTHER_TO_CLASS
//#define CONVERSION_FROM_CLASS_TO_OTHER
#define HOME_WORK_1
#define HOME_WORK_2

void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	Fraction A;		//Default constructor
	A.print();

	Fraction B = 5;
	B.print();

	Fraction C(1, 2);
	C.print();

	Fraction D(2, 3, 4);
	D.print();

	Fraction E = D;
	E.print();

	Fraction F;
	F = E;
	F.print();
#endif // CONSTRUCTORS_CHECK

#ifdef ARITHMETICAL_OPERATORS_CHECK
	Fraction A(2, 3, 4);
	A.print();

	Fraction B(3, 4, 5);
	B.print();

	(A + B).print();

	/*Fraction C = A * B;
	C.print();
	Fraction D = A / B;
	D.print();
	*/
	int a = 2;
	int b = 3;
	a *= b;//a=6		//a = a * b;
	a /= b;//a=2

	/*A *= B;
	A.print();
	A /= B;
	A.print();*/
#endif // ARITHMETICAL_OPERATORS_CHECK

	/*int a, b;
	cout << "Введите два числа: "; cin >> a >> b;
	int c = add(a, b);*/

	//cout << (Fraction(1, 2) >= Fraction(5, 11)) << endl;

#ifdef IOSTREAM_OPERATORS_CHECK
	Fraction A(2, 3, 4);
	cout << "Введите простую дробь: "; cin >> A;
	cout << A << endl;
#endif // IOSTREAM_OPERATORS_CHECK

#ifdef TYPE_CONVERSIONS_BASICS
	//	(type)value;	//C-like notation (C-подобная форма записи)
	//	type(value);	//Functional notation (Функциональная форма записи)

	int a = 2;		//No conversions
	double b = 3;	//Converion from less to more
	int c = b;		//Converion from more to less without data loss
	int d = 5.2;	//Conversion from more to less with data loss
	//cout << d << endl;
	cout << (double)7 / 2 << endl;
#endif // TYPE_CONVERSIONS_BASICS

	/*
	-----------------------------------
	1. From other to Class:
		-Single-argument constructor;
		-Assignment operator;
	2. From Class to other types:
	-----------------------------------
	*/

#ifdef CONVERSION_FROM_OTHER_TO_CLASS
	Fraction A = (Fraction)5;	//Conversion from less to more (From 'int' to 'Fraction')
	//preformed by Single-argument constructor.
	cout << A << endl;

	Fraction B;		//Default constructor
	B = Fraction(7);			//Assignment operator
	cout << B << endl;
#endif // CONVERSION_FROM_OTHER_TO_CLASS

	//explicit - запрещает неявные преобразования, 
	//и оставляет возможность лишь явно преобразовывать типы.

#ifdef CONVERSION_FROM_CLASS_TO_OTHER
			/*
----------------------------------
	operator type()
	{
		.....
		conversion code;
		.....
		return value;
	}
----------------------------------
*/

	Fraction A(2, 3, 4);
	cout << A << endl;
	int a = (int)A;
	cout << a << endl;
#endif // CONVERSION_FROM_CLASS_TO_OTHER

#ifdef HOME_WORK_1
	Fraction A(2, 3, 4);
	cout << A << endl;
	double a = int(A);
	cout << a << endl;
#endif // HOME_WORK_1

#ifdef HOME_WORK_2
	Fraction B = Fraction(2.75);
	cout << B << endl;
#endif // HOME_WORK_2

}