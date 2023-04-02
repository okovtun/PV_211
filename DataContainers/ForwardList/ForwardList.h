#pragma once
//ForwardList
#include<iostream>
#include<string>
#include<ctime>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-------------------------------------\n"

template<typename T> class ForwardList;
template<typename T> ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
template<typename T> class ConstIterator;
template<typename T> class Iterator;

template<typename T>class Element
{
	T Data;				//значение элемента
	Element<T>* pNext;	//адрес следующего элемента
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr);
	~Element();

	friend class ForwardList<T>;
	friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
	friend class ConstIterator<T>;
	friend class Iterator<T>;
};

template<typename T>
int Element<T>::count = 0;	//—татическую переменную можно проинициализировать только за пределами класса

template<typename T>class ConstIterator
{
	Element<T>* Temp;
public:
	ConstIterator(Element<T>* Temp);
	~ConstIterator();

	ConstIterator& operator++();

	bool operator==(const ConstIterator& other)const;
	bool operator!=(const ConstIterator& other)const;
	const T& operator*()const;
};
template<typename T>class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp);
	~Iterator();

	Iterator& operator++();

	bool operator==(const Iterator& other)const;
	bool operator!=(const Iterator& other)const;
	T& operator*();
};

template<typename T>class ForwardList
{
	Element<T>* Head;
	unsigned int size;
public:
	Iterator<T> begin();
	Iterator<T> end();
	ConstIterator<T> begin()const;
	ConstIterator<T> end()const;

	ForwardList();
	ForwardList(initializer_list<T> il);
	ForwardList(const ForwardList<T>& other);
	ForwardList(ForwardList<T>&& other);
	~ForwardList();

	//				Operators:
	ForwardList<T>& operator=(const ForwardList<T>& other);
	ForwardList<T>& operator=(ForwardList<T>&& other);

	//				Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	//				Removing elements:
	void pop_front();
	void pop_back();
	void erase(int Index);

	//				Methods:
	void reverse();
	void print()const;
	friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
};