#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<list>
#include<time.h>
#include<Windows.h>
using namespace std;

#define delimiter "\n------------------------------------------\n"

const std::map<int, std::string> crime =
{
	{0, "Правонарушение не определено"},
	{1, "Привышение скорости"},
	{2, "Прозд на красный"},
	{3, "Ремень безопасности"},
	{4, "Выезд на встречную полосу"},
	{5, "Оскорбление офицера"},
	{6, "Езда в нетрезвом состоянии"},
	{7, "Дрифт на светофоре"},
	{8, "Парковка в неположенном месте"},
};

#define TAKE_TIME int min, int hour, int day, int month, int year
#define GIVE_TIME	  min,	   hour,	 day,	  month,	 year
class Crime
{
	static int width;
	int id;	//статья
	std::string place;	//место правонарушения
	tm time;	//Дата, время правонарушения
public:
	int get_width()const
	{
		return width;
	}
	int get_id()const
	{
		return id;
	}
	const std::string& get_place()const
	{
		return place;
	}
	const char* get_time()const
	{
		//time_t t_time = mktime(&time);
		return asctime(&time);
	}
	//type	name	(parameters)
	time_t get_timestamp()const
	{
		struct tm time = this->time;
		return mktime(&time);
	}
	void set_width()
	{
		for (std::map<int, std::string>::const_iterator it = crime.begin(); it != crime.end(); ++it)
		{
			if (it->second.size() > width)width = it->second.size() + 2;
		}
	}
	void set_id(int id)
	{
		if (id >= crime.size())id = 0;
		this->id = id;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	void set_time(TAKE_TIME)
	{
		//time_t - это время в формате 'timestamp'
		//tm - это структра, в которой разделены единицы времени (часы, минуты, дни.....)
		//функция localtime() преобразует время из формата 'timestamp' в формат 'tm'
		//функция mktime() преобразует время из формата 'tm' в формат 'timestamp'
		time = tm();
		time.tm_min = min;
		time.tm_hour = hour;
		time.tm_mday = day;
		time.tm_mon = month - 1;
		time.tm_year = year - 1900;
		//Следующие преобразования нужны для того, чтобы корректно проинициалировать 
		//переменную-член tm_wday (день недели), структуры 'tm'
		time_t t_time = mktime(&time);
		tm* new_time = localtime(&t_time);
		time = *new_time;
		//delete new_time;
	}
	void set_time(time_t time)
	{
		tm* p_time = localtime(&time);
		this->time = *p_time;
	}

	//					Constructors:
	Crime(int id, const std::string& place, TAKE_TIME)
	{
		set_width();
		set_id(id);
		set_place(place);
		set_time(GIVE_TIME);
	}
	~Crime() {}

	Crime& operator()(std::string crime)
	{
		id = stoi(crime, 0, 10);		//преобразуем первое число в строке в число, и записываем его в 'id'
		while (crime.front() == ' ')crime.erase(0, 1);	//удаляем пробел с начала строки
		crime.erase(0, crime.find(' '));//удаляем сохраненное число из строки

		set_time(stoi(crime, 0, 10));	//читаем timestamp из строки
		crime.erase(0, 1);	//удаляем пробел с начала строки
		crime.erase(0, crime.find(' '));//удаляем timestamp из строки

		while (crime.front() == ' ')crime.erase(0, 1);	//удаляем пробел с начала строки
		set_place(crime);

		return *this;
	}

	//					Methdos:

};

int Crime::width = 1;

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	/*os << obj.get_id() << " ";
	os << obj.get_place() << " ";
	os << obj.get_time();
	return os;*/
	std::string time = obj.get_time();
	time[time.size() - 1] = 0;
	//return os << time << ": " << crime.at(obj.get_id()) << ", " << obj.get_place();
	os << time << ": ";
	os.width(obj.get_width());
	os << std::left;
	os << crime.at(obj.get_id());
	os << obj.get_place();
	return os;
}
std::ifstream& operator>>(std::ifstream& ifs, Crime& obj)
{
	int id;
	time_t datetime;
	std::string place;
	ifs >> id >> datetime;
	std::getline(ifs, place, ',');
	obj.set_id(id);
	obj.set_time(datetime);
	obj.set_place(place);
	return ifs;
}

void print(const std::map<std::string, std::list<Crime>>& base)
{
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		cout << it->first << ":\n";
		for (std::list<Crime>::const_iterator c_it = it->second.begin(); c_it != it->second.end(); ++c_it)
		{
			cout << "\t" << *c_it << endl;
		}
		cout << delimiter << endl;
	}
}
void print_number(const std::map<std::string, std::list<Crime>>& base)
{
	std::string licence_plate;
	cout << "Введите номер автомобиля: "; cin >> licence_plate;
	try
	{
		for (std::list<Crime>::const_iterator it = base.at(licence_plate).begin(); it != base.at(licence_plate).end(); ++it)
		{
			cout << "\t" << *it << endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Номера нет в базе" << endl;
	}
}
void print_range(const std::map<std::string, std::list<Crime>>& base)
{
	std::string start_plate;
	std::string end_plate;
	cout << "Введите начальный номер диапазона: "; cin >> start_plate;
	cout << "Введите конечный номер диапазона:  "; cin >> end_plate;
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.lower_bound(start_plate); it != base.upper_bound(end_plate); ++it)
	{
		cout << it->first << ":\n";
		for (std::list<Crime>::const_iterator c_it = it->second.begin(); c_it != it->second.end(); ++c_it)
		{
			cout << "\t" << *c_it << endl;
		}
		cout << delimiter << endl;
	}
}
void add_crime(std::map<std::string, std::list<Crime>>& base)
{
	for (std::pair<int, std::string> i : crime)cout << i.first << "\t" << i.second << endl;
	int id;	//статья
	std::string licence_plate;	//номер автомобиля
	std::string place;		//место нарушения
	int min, hour, day, month, year;	//дата и время нарушения
	cout << "Введите статью: "; cin >> id;
	cout << "Введите номер автомобиля: "; cin >> licence_plate; cin.ignore();
	cout << "Введите место нарушения:  "; std::getline(cin, place);
	cout << "Введите дату и время нарушения:"; cin >> year >> month >> day >> hour >> min;
	base[licence_plate].push_back(Crime(id, place, min, hour, day, month, year));
}
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	std::ofstream fout(filename);
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		fout << it->first << ":\t";
		for (std::list<Crime>::const_iterator c_it = it->second.begin(); c_it != it->second.end(); ++c_it)
		{
			fout << c_it->get_id() << " " << c_it->get_timestamp() << " ";
			//fout.seekp(-2, ios::cur);
			fout << " " << c_it->get_place() << ", ";
		}
		fout.seekp(-2, std::ios::cur);
		fout << ";\n";
	}
	fout.close();
	std::string command = "notepad ";
	command += filename;
	system(command.c_str());
}
void load(std::map <std::string, std::list<Crime>>& base, const std::string& filename)
{
	base.clear();
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		//TODO: read file
		std::string licence_plate;
		const int SIZE = 1024;
		char all_crimes[SIZE] = {};
		Crime crime(0, "", 1, 1, 1, 1, 1971);
		while (!fin.eof())
		{
			std::getline(fin, licence_plate, ':');
			if (licence_plate.empty())continue;
			/*while (crime.get_place().back() != ';')
			{
				fin >> crime;
			}*/
			fin.getline(all_crimes, SIZE, ';');
			for (char* pch = strtok(all_crimes, ",;"); pch; pch = strtok(NULL, ",;"))
			{
				crime(pch);
				base[licence_plate].push_back(crime);
			}
		}
		fin.ignore();
		fin.close();
	}
	else
	{
		std::cerr << "File not found" << endl;
	}
}

//#define CRIME_CHECK
//#define TIME_CHECK
void main()
{
	//throw;
	setlocale(LC_ALL, "");
#ifdef CRIME_CHECK
	Crime crime(10, "ул. Ленина", 23, 22, 1, 5, 2023);
	cout << crime << endl;
#endif // CRIME_CHECK

#ifdef TIME_CHECK
	cout << "Текущее время в формате 'timestamp':" << time(NULL) << endl;
	time_t t_current_time = time(NULL);
	tm* p_tm_current_time = localtime(&t_current_time);
	cout << "Текущее время в формате 'tm':" << asctime(p_tm_current_time) << endl;
#endif // TIME_CHECK

	/*char str[256];
	cout << "Введите строку: ";
	SetConsoleCP(1251);
	cin.getline(str, 256);
	SetConsoleCP(866);
	cout << str << endl;*/

	std::map<std::string, std::list<Crime>> base/* =
	{
		{
			"m777aa",
			{
				Crime(1, "ул.Ленина 2", 22,11, 29, 4, 2023),
				Crime(2, "ул.Ленина", 23,11, 29, 04, 2023),
				Crime(4, "ул.Ленина", 24, 11, 29,04,2023)
			}
		},

		{
			"m001aa",
			{
				Crime(6, "ул.Пушкина", 30, 18, 30, 04, 2023),
				Crime(5, "ул.Пушкина", 40, 18, 30, 04, 2023),
			}
		},

		{
			"b123cc",
			{
				Crime(8, "ул.Октябрьская", 10, 8, 8, 03, 2022),
				Crime(3, "ул.Октябрьская", 22, 18, 11, 04, 2022),
			}
		}
	}*/;
	int key;
	do
	{
		cout << "Выберите действие:\n";
		cout << "1. Вывести базу на экран;" << endl;
		cout << "2. Сохранить базу в файл;" << endl;
		cout << "3. Загрузить базу из файла;" << endl;
		cout << "4. Добавить нарушение;" << endl;
		cout << "5. Вывести все нарушения заданного номера;" << endl;
		cout << "6. Вывести все нарушения по диапазону номеров;" << endl;
		cout << "0. Выход;" << endl;
		cin >> key;
		system("CLS");
		switch (key)
		{
		case 1: print(base); break;
		case 2: save(base, "base.txt"); break;
		case 3: load(base, "base.txt"); break;
		case 4: add_crime(base); break;
		case 5: print_number(base); break;
		case 6: print_range(base); break;
		}
		system("PAUSE");
		system("CLS");
	} while (key);
	//print(base);
	}