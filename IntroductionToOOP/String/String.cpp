#include"String.h"

///----------------------------------------------------------------------------///

///////////////////////////////////////////////////////////////////////////////////
///////////				ОПРЕДЕЛЕНИЕ КЛАССА - CLASS DEFINITION			///////////

int String::get_size()const
{
	return size;
}
const char* String::get_str()const
{
	return str;
}
char* String::get_str()
{
	return str;
}

//				Contructors:
String::String(int size) :size(size), str(new char[size] {})
{
	cout << "DefConstructor:\t" << this << endl;
}
String::String(const char* str) : String(strlen(str) + 1)
{
	for (int i = 0; str[i]; i++)this->str[i] = str[i];
	cout << "Constructor:\t" << this << endl;
}
//Deep copy (Побитовое копирование)
//other
//this
//Shallow copy (Поверхностное копирование)
String::String(const String& other) :String(other.str)
{
	cout << "CopyConstructor:" << this << endl;
}
String::String(String&& other) : size(other.size), str(other.str)
{
	other.size = 0;
	other.str = nullptr;
	cout << "MoveConstructor:" << this << endl;
}
String::~String()
{
	delete[] this->str;
	this->str = nullptr;
	cout << "Destructor:\t" << this << endl;
	//Debug assertion failed
}

//				Operators:
String& String::operator=(const String& other)
{
	/*int a = 2;
	int b = 3;
	a = b;*/

	if (this == &other)return *this;
	delete[] this->str;

	this->size = other.size;
	//Deep copy (Побитовое копирование):
	this->str = new char[size] {};
	for (int i = 0; i < size; i++)
		this->str[i] = other.str[i];
	//-----------------------------
	cout << "CopyAssignment:\t" << this << endl;
	return *this;
}
String& String::operator=(String&& other)
{
	if (this == &other)return *this;
	delete[] this->str;
	this->size = other.size;
	this->str = other.str;
	other.size = 0;
	other.str = nullptr;
	cout << "MoveAssignment:\t" << this << endl;
	return *this;
}
String& String::operator+=(const String& other)
{
	return *this = *this + other;
}

char String::operator[](int i)const
{
	return str[i];
}
char& String::operator[](int i)
{
	return str[i];
}

//				Methods:
void String::print()const
{
	cout << "Size:\t" << size << endl;
	cout << "Str:\t" << str << endl;
}

String operator+(const String& left, const String& right)
{
	String cat(left.get_size() + right.get_size() - 1);
	for (int i = 0; i < left.get_size(); i++)
		cat[i] = left[i];
	//cat.get_str()[i] = left.get_str()[i];
	for (int i = 0; i < right.get_size(); i++)
		cat[i + left.get_size() - 1] = right[i];
	//cat.get_str()[i + left.get_size() - 1] = right.get_str()[i];
	return cat;

	//		l-value = r-value;
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

///////////			КОНЕЦ ОПРЕДЕЛЕНИЯ КЛАССА - CLASS DEFINITION	END		///////////
///////////////////////////////////////////////////////////////////////////////////
