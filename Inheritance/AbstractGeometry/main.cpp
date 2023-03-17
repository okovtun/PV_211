#define _USE_MATH_DEFINES
#include<Windows.h>
#include<iostream>
using namespace std;

namespace Geometry
{
	class Shape
	{
	public:
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры:" << get_perimeter() << endl;
			draw();
		}
	};

	class Square :public Shape
	{
		double side;
	public:
		Square(double side)
		{
			set_side(side);
		}
		~Square() {}
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side < 5)side = 5;
			if (side > 20)side = 20;
			this->side = side;
		}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
		{
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
		}

		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны квадрата: " << side << endl;;
			Shape::info();
		}
	};

	class Rectangle :public Shape
	{
		double length;
		double width;
	public:
		Rectangle(double width, double length)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle() {}
		double get_length()const
		{
			return length;
		}
		double get_width()const
		{
			return width;
		}
		void set_length(double length)
		{
			if (length < 3)length = 3;
			if (length > 20)length = 20;
			this->length = length;
		}
		void set_width(double width)
		{
			if (width < 5)width = 5;
			if (width > 30)width = 30;
			this->width = width;
		}
		double get_area()const override
		{
			return length * width;
		}
		double get_perimeter()const override
		{
			return (length + width) * 2;
		}
		void draw()const override
		{
			/*for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < length; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}*/

			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));	//Карандаш рисует контур фигуры
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Rectangle(hdc, 100, 100, 400, 200);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина прямоугольника: " << length << endl;
			cout << "Ширина прямоугольника: " << width << endl;
			Shape::info();
		}
	};
	class Circle :public Shape
	{
		double radius;
	public:
		Circle(double radius)
		{
			set_radius(radius);
		}
		~Circle() {}
		double get_radius()const
		{
			return this->radius;
		}
		void set_radius(double radius)
		{
			if (radius < 50)radius = 50;
			if (radius > 300)radius = 300;
			this->radius = radius;
		}
		double get_area()const override
		{
			return M_PI * radius*radius;
		}
		double get_perimeter()const override
		{
			return 2 * radius*M_PI;
		}
		void draw()const override
		{
			HWND hwnd = GetDesktopWindow();
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 0));

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, 700, 100, 900, 300);

			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");

	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//COORD coord;
	//SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &coord);

	Geometry::Square square(8);
	/*cout << "Длина стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect(5, 12);
	rect.info();

	Geometry::Circle circle(500);
	circle.info();
}