#include<Windows.h>
#include<iostream>
#include<conio.h>
#include<thread>
using namespace std;

#define MIN_TANK_VOLUME	20
#define MAX_TANK_VOLUME	100

class Tank
{
	const int VOLUME;	//характеристика бака
	double fuel_level;	//состояние бака
public:
	int get_VOLUME()const
	{
		return VOLUME;
	}
	double get_fuel_level()const
	{
		return fuel_level;
	}
	double give_fuel(double amount)
	{
		fuel_level -= amount;
		if (fuel_level < 0)fuel_level = 0;
		return fuel_level;
	}
	void fill(double fuel)
	{
		if (fuel < 0)return;
		if (fuel_level + fuel > VOLUME)fuel_level = VOLUME;
		else fuel_level += fuel;
	}
	Tank(int volume) :VOLUME(
		volume<MIN_TANK_VOLUME ? MIN_TANK_VOLUME :
		volume>MAX_TANK_VOLUME ? MAX_TANK_VOLUME :
		volume), fuel_level(0)
	{
		cout << "Tank is ready" << endl;
	}
	~Tank()
	{
		cout << "Tank is over" << endl;
	}
	void info()const
	{
		cout << "Tank volume:\t" << get_VOLUME() << " liters.\n";
		cout << "Fuel level:\t" << get_fuel_level() << " liters.\n";
	}
};

#define MIN_ENGINE_CONSUMPTION	3
#define MAX_ENGINE_CONSUMPTION	25
class Engine
{
	int consumption;	//расход топлива на 100 км
	double consumption_per_second;	//расзод топлива за 1 секунду на холостом ходу
	double default_consumption_per_second;
	bool is_started;
public:
	Engine(int consumption) :consumption(
		consumption<MIN_ENGINE_CONSUMPTION ? MIN_ENGINE_CONSUMPTION :
		consumption>MAX_ENGINE_CONSUMPTION ? MAX_ENGINE_CONSUMPTION :
		consumption
	)
	{
		consumption_per_second = consumption * 3e-5;
		default_consumption_per_second = consumption * 3e-5;
		is_started = false;
		cout << "Engine ready" << endl;
	}
	~Engine()
	{
		cout << "Engine is over" << endl;
	}
	void start()
	{
		is_started = true;
	}
	void stop()
	{
		is_started = false;
	}
	bool started()const
	{
		return is_started;
	}

	int get_consumption()const
	{
		return consumption;
	}
	double get_consumption_per_second()const
	{
		return consumption_per_second;
	}
	double set_consumption_per_second(int speed)
	{
		if (speed == 0)consumption_per_second = default_consumption_per_second;
		else if (speed <= 60)consumption_per_second = default_consumption_per_second * 20 / 3;
		else if (speed <= 100)consumption_per_second = default_consumption_per_second * 48;
		else if (speed <= 140)consumption_per_second = default_consumption_per_second * 20 / 3;
		else if (speed <= 200)consumption_per_second = default_consumption_per_second * 8.33;
		else consumption_per_second = default_consumption_per_second * 10;
		return consumption_per_second;
	}

	void info()const
	{
		cout << "Consumption per 100 km:\t" << consumption << " liters.\n";
		cout << "Consumption per second:\t" << consumption_per_second << " liters.\n";
		cout << "Engine is " << (started() ? "started" : "stopped") << ".\n";
	}
};

#define MAX_SPEED_LOW_LIMIT 50
#define MAX_SPEED_HIGH_LIMIT 400

#define Enter 13
#define Escape 27
class Car
{
	Engine engine;
	Tank tank;
	bool driver_inside;
	int speed;
	const int MAX_SPEED;
	int accelleration = 10;
	struct
	{
		std::thread panel_thread;
		std::thread engine_idle_thread;
		std::thread free_wheeling_thread;
	}threads;
public:
	Car(int engine_consumption, int tank_volume, int max_speed) :
		engine(engine_consumption),
		tank(tank_volume),
		MAX_SPEED(
			max_speed<MAX_SPEED_LOW_LIMIT ? MAX_SPEED_LOW_LIMIT :
			max_speed>MAX_SPEED_HIGH_LIMIT ? MAX_SPEED_HIGH_LIMIT :
			max_speed)
	{
		speed = 0;
		driver_inside = false;
		cout << "Your car is ready, press Enter to get in" << endl;
	}
	~Car()
	{
		cout << "Your car is over" << endl;
	}

	void get_in()
	{
		driver_inside = true;
		threads.panel_thread = std::thread(&Car::panel, this);
	}
	void get_out()
	{
		driver_inside = false;
		if (threads.panel_thread.joinable())threads.panel_thread.join();
		system("CLS");
		cout << "You are out of your car" << endl;
	}
	void start()
	{
		if (driver_inside && tank.get_fuel_level())
		{
			engine.start();
			threads.engine_idle_thread = std::thread(&Car::engine_idle, this);
		}
	}
	void stop()
	{
		engine.stop();
		if (threads.engine_idle_thread.joinable())threads.engine_idle_thread.join();
	}
	void accellerate()//accelleration - ускорение
	{
		if (driver_inside && engine.started())
		{
			speed += accelleration;
			if (speed > MAX_SPEED)speed = MAX_SPEED;
			std::this_thread::sleep_for(1s);
			if (!threads.free_wheeling_thread.joinable())
				threads.free_wheeling_thread = std::thread(&Car::free_wheeling, this);
		}
	}
	void slow_down()
	{
		if (driver_inside)
		{
			speed -= accelleration * 2;
			if (speed < 0)speed = 0;
			std::this_thread::sleep_for(1s);
			if (speed == 0 && threads.free_wheeling_thread.joinable())
				threads.free_wheeling_thread.join();
		}
	}
	void control()
	{
		char key = 0;	//команда с клавиатуры
		do
		{
			if (_kbhit())	//Функция _kbhit() возвращает ненулевое значение если была нажата клавиша
			{
				key = _getch();	//Функция _getch() ожидает нажатие клавиши и возвращает ASCII-код нажатой клавиши
				switch (key)
				{
				case Enter:
					if (driver_inside)get_out();
					else get_in();
					break;
				case 'F':case 'f':
					if (driver_inside)
					{
						cout << "Для начала выйдите из машины" << endl;
						break;
					}
					double fuel;
					cout << "Введите объем топлива: "; cin >> fuel;
					tank.fill(fuel);
					break;
				case 'I':case 'i':	//Ignition
					if (driver_inside)!engine.started() ? start() : stop();
					break;
				case 'W':case 'w':case '72':
					accellerate();
					break;
				case 'S':case 's':case '75':
					slow_down();
					break;
				case Escape:
					stop();
					get_out();
					speed = 0;
				}
			}
			if (speed < 0)speed = 0;
			if (tank.get_fuel_level() == 0)stop();
			if (speed == 0 && threads.free_wheeling_thread.joinable())
				threads.free_wheeling_thread.join();
		} while (key != Escape);
	}
	void free_wheeling()
	{
		while (speed--)
		{
			if (speed < 0)speed = 0;
			engine.set_consumption_per_second(speed);
			std::this_thread::sleep_for(1s);
		}
	}
	void engine_idle()
	{
		while (engine.started() && tank.give_fuel(engine.get_consumption_per_second()))
			std::this_thread::sleep_for(1s);
	}
	void panel()
	{
		while (driver_inside)
		{
			system("CLS");
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			for (int i = 0; i <= speed / 2.2; i++)
			{
				if (i > MAX_SPEED / 2.2 * 3 / 5)SetConsoleTextAttribute(hConsole, 0x0E);
				if (i > MAX_SPEED / 2.2 * 4 / 5)SetConsoleTextAttribute(hConsole, 0x0C);
				setlocale(LC_ALL, "C");
				cout << "|";
				setlocale(LC_ALL, "");
				SetConsoleTextAttribute(hConsole, 0x07);
			}
			cout << endl;
			cout << "Speed:\t\t" << speed << " km/hour.\n";
			cout << "Fuel level:\t" << tank.get_fuel_level() << " liters.\t";
			if (tank.get_fuel_level() <= 5)
			{
				SetConsoleTextAttribute(hConsole, 0xCF);
				cout << " LOW FUEL ";
				SetConsoleTextAttribute(hConsole, 0x07);
			}
			cout << endl;
			cout << "Engine " << (engine.started() ? "started" : "stopped");
			cout << "Consumption:\t" << (!engine.started() ? 0 : engine.get_consumption_per_second()) << " l/s\n";
			std::this_thread::sleep_for(1s);
		}
	}

	void info()const
	{
		engine.info();
		tank.info();
		cout << "Max speed:\t" << MAX_SPEED << " km/hour.\n";
	}
};

//#define TANK_CHECK
//#define ENGINE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef TANK_CHECK
	Tank tank(40);
	tank.info();
	int fuel;
	do
	{
		cout << "Введите уровень топлива: "; cin >> fuel;
		tank.fill(fuel);
		tank.info();
} while (fuel);
#endif // TANK_CHECK

#ifdef ENGINE_CHECK
Engine engine(8);
engine.info();
#endif // ENGINE_CHECK

Car mustang(10, 80, 250);
mustang.control();
}