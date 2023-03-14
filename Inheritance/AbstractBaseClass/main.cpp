#include<iostream>
using namespace std;

class Vehicle	//Транспортное средство
{
	int speed;
public:
	virtual void move() = 0;	//Чисто-виртуальный метод
	//Если в классе есть хотябы один чисто-виртуальный метод, то класс является абстрактным.
};

class GroundVehicle :public Vehicle{};

class Car :public GroundVehicle
{
public:
	void move()override
	{
		cout << "Машина едит на четырех колесах, со скоростью " << endl;
	}
};
class Bike :public GroundVehicle
{
public:
	void move()override
	{
		cout << "Мотоцикл едит на двух колесах" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Vehicle vehicle;
	//GroundVehicle gv;
	Car bmw;
	bmw.move();

	Bike harley_devidson;
	harley_devidson.move();
}