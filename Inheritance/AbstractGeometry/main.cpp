#define _USE_MATH_DEFINES
#include<Windows.h>
#include<iostream>
using namespace std;

namespace Geometry
{
	enum limits
	{
		MIN_SIZE = 50,
		MAX_SIZE = 500,
		MIN_LINE_WIDTH = 1,
		MAX_LINE_WIDTH = 30,
		MIN_START_X = 100,
		MAX_START_X = 1000,
		MIN_START_Y = 100,
		MAX_START_Y = 700
	};
	enum Color
	{
		//0x - Hexadecimal (Шестнадцатеричная система счисления)
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,
		yellow = 0x00FFFF,
		white = 0x00FFFFFF
	};
#define SHAPE_TAKE_PARAMETERS int start_x, int start_y, int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color
	class Shape
	{
	protected:
		int start_x;
		int start_y;
		int line_width;
		Color color;
	public:
		Shape(SHAPE_TAKE_PARAMETERS):color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}
		int get_start_x()const
		{
			return start_x;
		}
		int get_start_y()const
		{
			return start_y;
		}
		int get_line_width()const
		{
			return line_width;
		}
		void set_start_x(int start_x)
		{
			if (start_x < limits::MIN_START_X)start_x = limits::MIN_START_X;
			if (start_x > limits::MAX_START_X)start_x = limits::MAX_START_X;
			this->start_x = start_x;
		}
		void set_start_y(int start_y)
		{
			if (start_y < limits::MIN_START_Y)start_y = limits::MIN_START_Y;
			if (start_y > limits::MAX_START_Y)start_y = limits::MAX_START_Y;
			this->start_y = start_y;
		}
		void set_line_width(int line_width)
		{
			if (line_width < limits::MIN_LINE_WIDTH)line_width = limits::MIN_LINE_WIDTH;
			if (line_width > limits::MAX_LINE_WIDTH)line_width = limits::MAX_LINE_WIDTH;
			this->line_width = line_width;
		}

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
		Square(double side, SHAPE_TAKE_PARAMETERS):Shape(SHAPE_GIVE_PARAMETERS)
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
		Rectangle(double width, double length, SHAPE_TAKE_PARAMETERS):Shape(SHAPE_GIVE_PARAMETERS)
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
			if (length < limits::MIN_SIZE)length = limits::MIN_SIZE;
			if (length > limits::MAX_SIZE)length = limits::MAX_SIZE;
			this->length = length;
		}
		void set_width(double width)
		{
			if (width < limits::MIN_SIZE)width = limits::MIN_SIZE;
			if (width > limits::MAX_SIZE)width = limits::MAX_SIZE;
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
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);	//Карандаш рисует контур фигуры
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + length);

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
		Circle(double radius, SHAPE_TAKE_PARAMETERS):Shape(SHAPE_GIVE_PARAMETERS)
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
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, start_x, start_y, start_x + 2 * radius, start_y + 2 * radius);

			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &coord);

	Geometry::Square square(8, 100, 100, 5, Geometry::Color::blue);
	/*cout << "Длина стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect(150, 77, 200, 100, 5, Geometry::Color::red);
	rect.info();

	Geometry::Circle circle(500, 300, 100, 5, Geometry::Color::yellow);
	circle.info();
}