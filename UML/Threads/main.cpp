#include<iostream>
#include<thread>
using namespace std;
using namespace std::chrono_literals;	//1s, 1ms, 1mks....

//https://legacy.cplusplus.com/reference/thread/thread/

bool finish = false;

void Plus()
{
	while (!finish)
	{
		cout << "+ ";
		std::this_thread::sleep_for(1s);
	}
}
void Minus()
{
	while (!finish)
	{
		cout << "- ";
		std::this_thread::sleep_for(1s);
	}
}

void main()
{
	//Plus();
	//Minus();
	//throw;
	cout << Plus << endl;
	std::thread plus_thread(Plus);
	std::thread minus_thread(Minus);
	cin.get();	//метод get() ожидает нажатие 'Enter'
	finish = true;
	if(plus_thread.joinable())plus_thread.join();
	if(minus_thread.joinable())minus_thread.join();
	if(minus_thread.joinable())minus_thread.join();
	if(minus_thread.joinable())minus_thread.join();
	if(minus_thread.joinable())minus_thread.join();
	if(minus_thread.joinable())minus_thread.join();
	if(minus_thread.joinable())minus_thread.join();
	if(minus_thread.joinable())minus_thread.join();
}