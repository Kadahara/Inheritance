#define _USE_MATH_DEFINES
#include<iostream>
#include<Windows.h>
using namespace std;

namespace Geometry
{
	enum Color	//������������ - ��� ����� ������������� ��������
	{
		//	  0xAABBGGRR
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,
		yellow = 0x0000FFFF,
		white = 0x00FFFFFF,
		grey = 0x00AAAAAA,

		console_default = 0x07,
		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0xCC,
		console_yellow = 0xEE,
		console_white = 0xFF,
	};
	enum Limitations
	{
		MIN_SIZE = 50,
		MAX_SIZE = 550,
		MIN_START_X = 0,
		MIN_START_Y = 0,
		MAX_START_X = 1000,
		MAX_START_Y = 700,
		MIN_LINE_WIDTH = 3,
		MAX_LINE_WIDTH = 30,
	};
#define SHAPE_TAKE_PARAMETERS unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color
	class Shape
	{
	protected:
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;
		Color color;
	public:
		void set_start_x(int start_x)
		{
			if (start_x > Limitations::MAX_START_X)start_x = Limitations::MAX_START_X;
			this->start_x = start_x;
		}
		void set_start_y(int start_y)
		{
			if (start_y > Limitations::MAX_START_Y)start_y = Limitations::MAX_START_Y;
			this->start_y = start_y;
		}
		void set_line_width(int line_width)
		{
			if (line_width < Limitations::MIN_LINE_WIDTH)line_width = Limitations::MIN_LINE_WIDTH;
			if (line_width > Limitations::MAX_LINE_WIDTH)line_width = Limitations::MAX_LINE_WIDTH;
			this->line_width = line_width;
			SHRT_MIN;
		}
		unsigned int get_start_x()const
		{
			return start_x;
		}
		unsigned int get_start_y()const
		{
			return start_y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}
		Color get_color()const
		{
			return color;
		}
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;

		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}

		virtual void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "������� ������: " << get_area() << endl;
			cout << "�������� ������: " << get_perimeter() << endl;
			draw();
		}
	};

	/*class Square :public Shape
	{
		double side;
	public:
		void set_side(double side)
		{
			if (side < Dimensions::MIN_SIZE)side = Dimensions::MIN_SIZE;
			if (side > Dimensions::MAX_SIZE)side = Dimensions::MAX_SIZE;
			this->side = side;
		}
		double get_side()const
		{
			return side;
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
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "����� �������: " << side << endl;
			Shape::info();
		}
		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
	};*/

	class Rectangle :public Shape
	{
		double side1, side2;
	public:
		void set_side1(double side1)
		{
			if (side1 < Limitations::MIN_SIZE)side1 = Limitations::MIN_SIZE;
			if (side1 > Limitations::MAX_SIZE)side1 = Limitations::MAX_SIZE;
			this->side1 = side1;
		}
		void set_side2(double side2)
		{
			if (side2 < Limitations::MIN_SIZE)side2 = Limitations::MIN_SIZE;
			if (side2 > Limitations::MAX_SIZE)side2 = Limitations::MAX_SIZE;
			this->side2 = side2;
		}
		double get_side1()const
		{
			return side1;
		}
		double get_side2()const
		{
			return side2;
		}
		double get_area()const override
		{
			return side1 * side2;
		}
		double get_perimeter()const
		{
			return 2 * (side1 + side2);
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);	//�������� ���������� ���� �������.
			//�������� ���������� (Device context) - ��� ��, �� ��� �� ������
//����� ���� ��, ��� �� ������:
			HPEN hPen = CreatePen(PS_SOLID, 5, color);	//pen - ��������, ������ ��������� �����
			HBRUSH hBrush = CreateSolidBrush(color);	//brush - �����, ������ �������

			//��������, ��� � �� ��� ����� ��������:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//��������� ���������:
			//::Rectangle(hdc, start_x, start_y, end_x, end_y);
			::Rectangle(hdc, start_x, start_y, start_x + side1, start_y + side2);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "������� 1: " << side1 << endl;
			cout << "������� 2: " << side2 << endl;
			Shape::info();
		}

		Rectangle(double side1, double side2, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side1(side1);
			set_side2(side2);
		}
		~Rectangle() {}
	};
	class Square :public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
		~Square() {}
	};

	class Circle :public Shape
	{
		double radius;
	public:
		void set_radius(double radius)
		{
			if (radius < Limitations::MIN_SIZE)radius = Limitations::MIN_SIZE;
			if (radius > Limitations::MAX_SIZE)radius = Limitations::MAX_SIZE;
			this->radius = radius;
		}
		double get_radius()const
		{
			return radius;
		}
		double get_area()const override
		{
			return M_PI * radius * radius;
		}
		double get_perimeter()const override
		{
			return 2 * M_PI * radius;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, start_x, start_y, start_x + 2 * radius, start_y + 2 * radius);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Radius: " << radius << endl;
			Shape::info();
		}

		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}
		~Circle() {}
	};

	class Triangle :public Shape
	{
	public:
		Triangle(SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS) {}
		~Triangle() {}

		virtual double get_height()const = 0;
		void info()const
		{
			cout << "������ ������������: " << get_height() << endl;
			Shape::info();
		}

	};
	class EquilateralTriangle :public Triangle
	{
		double side;
	public:
		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		void set_side(double side)
		{

			if (side < Limitations::MIN_SIZE)side = Limitations::MIN_SIZE;
			if (side > Limitations::MAX_SIZE)side = Limitations::MAX_SIZE;
			this->side = side;
		}
		double get_height()const
		{
			return sqrt(pow(side, 2) - pow(side / 2, 2));
		}
		double get_area()const
		{
			return side * get_height() / 2;
		}
		double get_perimeter()const
		{
			return side * 3;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vertex[] =
			{
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side / 2, start_y + side - get_height()}
			};
			::Polygon(hdc, vertex, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "����� �������: " << side << endl;
			Triangle::info();
		}
	};
	class IsoscelesTriangle :public Triangle
	{
		double footing;
		double side;
	public:
		IsoscelesTriangle(double side,double footing, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
			set_footing(footing);
		}
		double get_footing()const
		{
			return footing;
		}
		double get_side()const
		{
			return side;
		}
		void set_footing(double footing)
		{
			if (footing < Limitations::MIN_SIZE)footing = Limitations::MIN_SIZE;
			if (footing > Limitations::MAX_SIZE)footing = Limitations::MAX_SIZE;
			this->footing = footing;
		}
		void set_side(double side)
		{
			if (side < Limitations::MIN_SIZE)side = Limitations::MIN_SIZE;
			if (side > Limitations::MAX_SIZE)side = Limitations::MAX_SIZE;
			this->side = side;
		}
		double get_height()const override
		{
			return sqrt(pow(side, 2) - pow(footing / 2, 2));
		}
		double get_area()const override
		{
			return side / 2 * get_height();
		}
		double get_perimeter()const override
		{
			return footing + side * 2;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT point[] =
			{
				{start_x, start_y + side},
				{start_x + footing, start_y + side},
				{start_x + footing / 2, start_y + side - get_height()}
			};
			::Polygon(hdc, point, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "���������: " << footing << endl;
			cout << "�������:   " << side << endl;
			Triangle::info();
		}
	};
}


void main()
{
	unsigned int number = -1;
	cout << number << endl;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {};
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &coord);

	setlocale(LC_ALL, "");
	//Shape shape;
	Geometry::Square square(5, 350, 300, 25, Geometry::Color::red);
	/*cout << "����� ������� ��������: " << square.get_side() << endl;
	cout << "������� ��������: " << square.get_area() << endl;
	cout << "�������� ��������: " << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect(380, 80, 500, 300, 5, Geometry::Color::blue);
	rect.info();

	Geometry::Circle circle(50, 1000, 300, 5, Geometry::Color::yellow);
	circle.info();

	Geometry::EquilateralTriangle t_eq(300, 700, 30, 25, Geometry::Color::green);
	t_eq.info();

	Geometry::IsoscelesTriangle IsoscelesTriangle(90, 145, 400, 170, 12, Geometry::Color::red); 
	IsoscelesTriangle.info();
}	