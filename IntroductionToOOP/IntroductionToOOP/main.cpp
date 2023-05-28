#include<iostream>
//using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n-------------------------\n"

class Point
{
	//Создавая структуру или класс мы создаем новый тип данных
	//Классы и структуры еще называют пользовательскими типами данных
	//						КЛАСС - ЭТО ТИП ДАННЫХ!!!
	//					СТРУКТУРА - ЭТО ТИП ДАННЫХ!!!
	double x;
	double y;
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}

	//				  Constructors:
	/*Point()
	{
		x = y = double();
		cout << "DefaultConstructor:\t" << this << endl;
	}
	Point(double x)
	{
		this->x = x;
		this->y = 0;
		cout << "1ArgConstructor:\t" << this << endl;
	}*/
	Point(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
		cout << "Constructor:\t\t" << this << endl;
	}
	Point(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t\t" << this << endl;
	}

	//					Operators:
	Point& operator=(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}

	Point& operator++()	//Prefix increment
	{
		x++;
		y++;
		return *this;
	}
	Point operator++(int)
	{
		Point old = *this;	//сохраняем старое значение объекта
		//Изменяем объект:
		x++;
		y++;
		return old;
	}

	//					Methods:
	double distance(const Point& other)const 
	{
		//this - эта точка
		//other - та точка
		double x_distance = this->x - other.x;
		double y_distance = this->y - other.y;
		double distance = sqrt(x_distance*x_distance + y_distance * y_distance);
		return distance;
	}
	void print()const
	{
		cout << "X = " << x << "\tY = " << y << endl;
	}
};

Point operator+(const Point& left, const Point& right)
{
	Point res;
	res.set_x(left.get_x() + right.get_x());
	res.set_y(left.get_y() + right.get_y());
	return res;
}

double distance(const Point& A, const Point& B)
{
	double x_distance = A.get_x() - B.get_x();
	double y_distance = A.get_y() - B.get_y();
	double distance = sqrt(x_distance*x_distance + y_distance * y_distance);
	return distance;
}

int add(int a = 0, int b = 0)
{
	return a + b;
}

//#define STRUCT_POINT
//#define CONTRUCTORS_CHECK
//#define DISTANCE_CHECK
//#define ASSIGNMENT_CHECK

void main()
{
	setlocale(LC_ALL, "Russian");

	//cout << add() << endl;
	//cout << "\n----------------------------\n";

#ifdef STRUCT_POINT
	int a;	//Объявление переменной 'a' типа 'int'
	Point A;//Объявление переменной 'A' типа 'Point'
			//Создание объекта 'A' структуры 'Point'
			//Создание экземпляра 'A' структуры 'Point'
			//Объекты классов и структур еще называют экземплярами классов и структур.

	A.x = 2;
	A.y = 3;
	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A;	//https://ru.wikipedia.org/wiki/%D0%92%D0%B5%D0%BD%D0%B3%D0%B5%D1%80%D1%81%D0%BA%D0%B0%D1%8F_%D0%BD%D0%BE%D1%82%D0%B0%D1%86%D0%B8%D1%8F
	cout << pA->x << "\t" << pA->y << endl;
#endif // STRUCT_POINT

#ifdef CONTRUCTORS_CHECK
	Point A;		//Здесь вызывается конструктор по умолчанию (Default constructor)
//A.set_x(2);
//A.set_y(3);
	cout << A.get_x() << "\t" << A.get_y() << endl;
	A.print();

	Point B = 5;	//Single-argument constructor
	B.print();

	Point C(22, 33);
	C.print();

	Point D = C;	//Copy constructor
	D.print();

	Point E;		//Default constructor
	E = D;			//Copy assignment
	E.print();

	/*for (int i = 0; i < 10; i++)
	{
		cout << i << "\t";
	}
	cout << endl;*/
#endif // CONTRUCTORS_CHECK

#ifdef DISTANCE_CHECK
	/*
------------------
1. Создается объект;
2. Для него вызывается метод;
3. В этот метод передается указанная точка
   (которая так же предварительно должна быть создана);
------------------
*/

	Point A(2, 3);
	A.print();

	Point B(4, 5);
	B.print();
	cout << delimiter << endl;
	cout << "Расстояние от точки A до точки B:" << A.distance(B) << endl;
	cout << delimiter << endl;
	cout << "Расстояние от точки B до точки A:" << B.distance(A) << endl;
	cout << delimiter << endl;
	cout << "Расстояние между точками A и B:  " << distance(A, B) << endl;
	cout << delimiter << endl;
	cout << "Расстояние между точками B и A:  " << distance(B, A) << endl;
	cout << delimiter << endl;
#endif // DISTANCE_CHECK

#ifdef ASSIGNMENT_CHECK
	//Copy assignment:

	int a, b, c;
	a = b = c = 2;
	cout << a << "\t" << b << "\t" << c << endl;

	Point A, B, C;
	cout << "\n-------------------------------\n";
	A = B = C = Point(2, 3);
	cout << "\n-------------------------------\n";
	A.print();
	B.print();
	C.print();
#endif // ASSIGNMENT_CHECK

	int a = 2;
	int b = 3;
	int c = a + b;

	Point A(2, 3);	A.print();
	Point B(4, 5);	B.print();
	//Point C = A + B;C.print();
	//C++; C.print();
	Point C = A;
	C.print();
}

/*
--------------------------------------------------------------
.  - Оператор прямого доступа (Point operator)
	 используется для доступа к полям объекта по ИМЕНИ объекта.

-> - Оператор косвенного доступа (Arrow operator)
	 используется для доступа к полям объекта по АДРЕСУ объекта.
--------------------------------------------------------------
*/

/*
--------------------------------------------------------------
				OOP concepts:
1. Encapsulation - сокрытие определенной части класса от внешнего мира.
	Модификаторы доступа
		private:	закрытые поля, доступны только внутри класса
		public:		открытые поля, доступны из любого места программы
		protected:	защищенные поля, доступны только внутри класса, и его дочерних классов.
					используется только при наследовании.

	get/set-методы  используются для доступа к закрытым переменным в классе
		get (взять, получить) используются для доступа к закрытым переменным на чтение, т.е.,
							  позволяют получить значение закрытой переменной.
		set (задать, установить) используются для доступа к закрытым перемееным на запись, т.е.,
							  позволяют задать значение закрытой переменной.
							  Кроме того, set-методы обеспечивают фильтрацию данных.
2. Inheritance;
3. Polymorphism;
--------------------------------------------------------------
*/

/*
--------------------------------------------------------------
				Special members:
1. Constructor - это метод, который создает объект.
	-с параметрами;
	-без параметров;
	-конструктор по умолчанию - это конструктор, который может быть вызван без параметров;
	-конструктор копирования;
	-конструктор переноса;
2. ~Destructor - это метод, который уничтожвет объект по завершении его времени жизни;
3. Assignment operator;
--------------------------------------------------------------
*/

/*
--------------------------------------------------------------
				Overloading rules
1. Перегрузить можно только существующие операторы. Создавать новые операторы невозможно.
	Например:
	+  - перегружается;
	++ - перегружается;
	*  - перегружается;
	** - НЕ перегружается;
2. Не все существующие операторы можно перегрузить.
   Не перегружаются:
	?: - Ternary operator
	:: - Scope operator (Оператор разрешения видимости)
	.  - Оператор прямого доступа (Point operator)
	.* - Pointer to member selection
	#  - Preprocessor directive
	## - Preprocessor concatenation
3. Перегруженные операторы сохраняют приоритет.
	a = b + c * d + e / f;
4. Переопределить поведение операторов над встроенными типами невозможно.

	"Hello" + "World" = "HelloWorld";
--------------------------------------------------------------
	type operator@(....)
	{
		....;
		code;
		....;
	}
--------------------------------------------------------------
*/