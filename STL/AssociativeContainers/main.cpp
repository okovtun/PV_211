#include<iostream>
#include<string>
#include<map>
#include<set>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

//#define STL_SET
#define STL_MAP

void main()
{
	setlocale(LC_ALL, "");
	//К ассоциативным контейнерам относятся: map, set, multimap, multiset
	//Все ассоциативные контейнеры хранят данные в виде Бинарного дерева.
#ifdef STL_SET
	std::set<int> set = { 50, 25, 75, 16, 32, 64, 128, 8 };
	for (std::set<int>::iterator it = set.begin(); it != set.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // STL_SET

#ifdef STL_MAP
	//map - это контейнер, каждый элемент которого хранит ПАРУ: ключ-значение
	//pair<key, value>

	std::map<int, std::string> week = 
	{
		std::pair<int, std::string>(0, "Sunday"),
		std::pair<int, std::string>(1, "Monday"),
		std::pair<int, std::string>(2, "Tuesday"),
		std::pair<int, std::string>(3, "Wednesday"),
		{4, "Thursday"},
		{5, "Friday"},
		{6, "Saturday"},
		{7, "Sunday"},
		{0, "Sunday"},
	};

	for (std::map<int, std::string>::iterator it = week.begin(); it != week.end(); ++it)
	{
		cout << it->first << tab << it->second << endl;
	}
	cout << endl;
#endif // STL_MAP

}