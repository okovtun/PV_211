#include<iostream>
#include<fstream>
#include<string>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define HUMAN_TAKE_PARAMETERS	const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS	last_name, first_name, age

//enum (Enumeration - Перечисление) - это набор целочисленных именованных констант
enum allignment
{
	last_name_width = 15,
	first_name_width = 10,
	age_width = 5,
	speciality_width = 25,
	numeric_width = 8
};

class Human
{
	std::string last_name;
	std::string first_name;
	int age;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(int age)
	{
		this->age = age;
	}

	//						Constructors:
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	virtual void info()const
	{
		cout << last_name << " " << first_name << " " << age << endl;
	}
	virtual std::ostream& print(std::ostream& os)const
	{
		return os << last_name << " " << first_name << " " << age;
	}
	virtual std::ofstream& print(std::ofstream& ofs)const
	{
		ofs.width(allignment::last_name_width);
		ofs << left;
		ofs << last_name;
		ofs.width(allignment::first_name_width);
		ofs << first_name;
		ofs.width(allignment::age_width);
		ofs << age;
		return ofs;
	}
	virtual std::ifstream& scan(std::ifstream& ifs)
	{
		ifs >> last_name >> first_name >> age;
		return ifs;
	}
};
std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.print(os);
}
std::ofstream& operator<<(std::ofstream& ofs, const Human& obj)
{
	return obj.print(ofs);
}
std::ifstream& operator>>(std::ifstream& ifs, Human& obj)
{
	return obj.scan(ifs);
}

#define STUDENT_TAKE_PARAMETERS	const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS	speciality, group, rating, attendance
class Student :public Human
{
	std::string speciality;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//					Constructors:
	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//						Methods:
	void info()const
	{
		Human::info();
		cout << speciality << " " << group << " " << rating << " " << attendance << endl;
	}
	std::ostream& print(std::ostream& os)const override
	{
		return Human::print(os) << " " << speciality << " " << group << " " << rating << " " << attendance;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Human::print(ofs);
		ofs.width(allignment::speciality_width);
		ofs << left;
		ofs << speciality;
		ofs.width(allignment::numeric_width);
		ofs << group;
		ofs.width(allignment::numeric_width);
		ofs << rating;
		ofs.width(allignment::numeric_width);
		ofs << attendance;
		return ofs;
	}
	std::ifstream& scan(std::ifstream& ifs)override
	{
		Human::scan(ifs);
		char sz_buffer[allignment::speciality_width] = {};
		ifs.read(sz_buffer, allignment::speciality_width - 1);	//метод read() читает заданное количество Байт из файла
		for (int i = allignment::speciality_width - 2;sz_buffer[i] == ' ';	i--)
			sz_buffer[i] = 0;
		while (sz_buffer[0] == ' ')
			for (int i = 0; sz_buffer[i]; i++)sz_buffer[i] = sz_buffer[i + 1];
		speciality = sz_buffer;
		ifs >> group;
		ifs >> rating;
		ifs >> attendance;
		return ifs;
	}
};

#define TEACHER_TAKE_PARAMETERS	const std::string& speciality, double experience
#define TEACHER_GIVE_PARAMETERS	speciality, experience
class Teacher : public Human
{
	std::string speciality;
	int experience;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	int get_experience()const
	{
		return experience;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experiece(double experience)
	{
		this->experience = experience;
	}

	//					Constructors:
	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experiece(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//				Methods:
	void info()const
	{
		Human::info();
		cout << speciality << " " << experience << " лет.\n";
	}
	std::ostream& print(std::ostream& os)const override
	{
		return Human::print(os) << " " << speciality << " " << experience;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Human::print(ofs);
		ofs.width(allignment::speciality_width);
		ofs << speciality;
		ofs.width(allignment::numeric_width);
		ofs << experience;
		return ofs;
	}
	std::ifstream& scan(std::ifstream& ifs)override
	{
		Human::scan(ifs);
		char sz_buffer[allignment::speciality_width] = {};
		ifs.read(sz_buffer, allignment::speciality_width - 1);
		for (int i = allignment::speciality_width - 2; sz_buffer[i] == ' '; i--)sz_buffer[i] = 0;
		while (sz_buffer[0] == ' ')
			for (int i = 0; sz_buffer[i]; i++)sz_buffer[i] = sz_buffer[i + 1];
		speciality = sz_buffer;
		ifs >> experience;
		return ifs;
	}
};

#define GRADUATE_TAKE_PARAMETERS	const std::string& subject
#define GRADUATE_GIVE_PARAMETERS	subject
class Graduate :public Student
{
	std::string subject;
public:
	const std::string& get_subject()const
	{
		return subject;
	}
	void set_subject(const std::string& subject)
	{
		this->subject = subject;
	}
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETERS)
		:Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
	{
		set_subject(subject);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}
	void info()const
	{
		Student::info();
		cout << subject << endl;
	}
	std::ostream& print(std::ostream& os)const override
	{
		return Student::print(os) << " " << subject;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Student::print(ofs);
		ofs << subject;
		return ofs;
	}
	std::ifstream& scan(std::ifstream& ifs)
	{
		Student::scan(ifs);
		std::getline(ifs, subject);
		return ifs;
	}
};

Human* HumanFactory(const std::string& type)
{
	if (type.find("Student") != std::string::npos)return new Student("", "", 0, "", "", 0, 0);
	if (type.find("Graduate") != std::string::npos)return new Graduate("", "", 0, "", "", 0, 0, "");
	if (type.find("Teacher") != std::string::npos)return new Teacher("", "", 0, "", 0);
}

void save(Human** group, const int n, const char* filename)
{
	std::ofstream fout(filename);
	for (int i = 0; i < n; i++)
	{
		fout << typeid(*group[i]).name() << ":\t";
		fout << *group[i] << endl;
	}
	fout.close();
	std::string s_command = "start notepad ";
	s_command += filename;
	system(s_command.c_str());
}
Human** load(const char* filename, int& n)
{
	Human** group = nullptr;	//Если файл небыл найден, то группа не создана
	n = 0;

	std::ifstream fin(filename);
	if (fin.is_open())
	{
		//1) Определяем количество строк в файле:
		while (!fin.eof())
		{
			std::string buffer;
			std::getline(fin, buffer);
			if (buffer.empty())continue;
			n++;
		}

		//2) Выделяем память под объекты. Каждый объект занимает отдельную строку в файле.
		group = new Human*[n] {};

		//3) Возвращаемся в начало файла, для того чтобы прочитать его еще раз:
		cout << "Позиция курсора в файле: " << fin.tellg() << endl;
		fin.clear();
		fin.seekg(0);	//seekg() задает get-позицию курсора (get - взять, прочитать)
		cout << "Позиция курсора в файле: " << fin.tellg() << endl;

		//4) Выполняем повторное чтение:
		std::string obj_type;
		for (int i = 0; i < n; i++)
		{
			std::getline(fin, obj_type, ':');
			fin.ignore();
			if (obj_type.empty())continue;
			group[i] = HumanFactory(obj_type);
			fin >> *group[i];
		}

		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}

	return group;
}

//#define INHERITANCE_CHECK
//#define POLYMORPHISM	//(многоформенность)
#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");

#ifdef INHERITANCE_CHECK
	Human human("Тупенко", "Василий", 20);
	human.info();

	Student student("Иванов", "Иван", 18, "IT", "PV_211", 12, 100);
	student.info();

	Teacher teacher("Einstein", "Albert", 143, "Astronomy", 110);
	teacher.info();

	Graduate graduate("Петров", "Николай", 21, "IT", "PV_211", 10, 80, "Организация защиты безопасности четотам сети");
	graduate.info();
#endif // INHERITANCE_CHECK

#ifdef POLYMORPHISM
	//1. Ad-Hoc polymorphism

//2. Runtime polymorphism:
/*
	1. Pointers to base class;	//Generalisation - Обобщение
	2. Virtual functions;
*/

//			Generalisation (UpCast)
	Human* group[] =
	{
		new Student("Pinkman", "Jessie", 20, "Chemistry", "WW_220", 89, 92),
		new Teacher("Whaite", "Walter", 50, "Chemistry", 25),
		new Graduate("Schreder", "Hank", 40, "Criminalistic", "OBN", 95, 75, "How to catch Heizenberg"),
		new Student("Vercetti", "Tomas", 30, "Criminalistic", "Vice", 98, 99),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20)
	};
	cout << sizeof(group) / sizeof(group[0]) << endl;
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		cout << typeid(*group[i]).name() << endl;
		//group[i]->info();
		cout << *group[i] << endl;
		cout << "\n------------------------------------\n";
	}
	//save(group, sizeof(group) / sizeof(group[0]), "group.txt");

	for (int i = 0; i < sizeof(group) / sizeof(Human*); i++)
	{
		delete group[i];
	}
	//delete[] group;	//При удалении статической памяти вылетает Debug Assertion Failed  
#endif // POLYMORPHISM

#ifdef READ_FROM_FILE
	int n = 0;	//Размер группы. Будет вычислен функцией load()
	Human** group = load("group.txt", n);
	cout << "\n-----------------------------------------\n";
	for (int i = 0; i < n; i++)
	{
		cout << *group[i] << endl;
		cout << "\n-----------------------------------------\n";
	}
	for (int i = 0; i < n; i++)
	{
		delete group[i];
	}
	delete[] group;
#endif // READ_FROM_FILE

}