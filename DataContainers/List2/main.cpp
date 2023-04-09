//TemplatedList2classWork
#include<iostream>
#include<string>
using namespace std;

#define tab "\t"

template<typename T>class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List<T>;
	}*Head, *Tail;
	size_t size;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}

		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;

		const T& operator*()const;
	};
public:
	class ConstIterator:public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstIterator() {}

		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator:public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp) {}
		~ConstReverseIterator() {}

		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*();
	};
	const ConstIterator begin()const;
	const ConstIterator end()const;
	const ConstReverseIterator rbegin()const;
	const ConstReverseIterator rend()const;

	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();

	//					Constructors:
	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();

	//				Operators:
	List<T>& operator=(const List<T>& other);

	//				Adding elemnts:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	//					Removing elements:
	void pop_front();
	void pop_back();

	//					Methods:
	void print()const;
	void reverse_print()const;
};

////////////////////////////////////////////////////////////////////////////////////////////
///////////////////					 Element						////////////////////////
template<typename T>List<T>::Element::Element(T Data, Element* pNext, Element* pPrev)
	:Data(Data), pNext(pNext), pPrev(pPrev)
{
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
}
///////////////////					 Element						////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

///--------------------------------------------------------------------------------------///

////////////////////////////////////////////////////////////////////////////////////////////
///////////////////				  ConstIterators					////////////////////////

template<typename T>bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}

template<typename T>const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}

//----------------------------------------------------------------------------------------//

template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()	//Prefix increment
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)	//Postfix increment
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
//----------------------------------------------------------------------------------------//
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator  List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
///////////////////				  ConstIterators					////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

///--------------------------------------------------------------------------------------///

////////////////////////////////////////////////////////////////////////////////////////////
///////////////////					 Iterators						////////////////////////
template<typename T>T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
template<typename T>T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

///////////////////					 Iterators						////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

///--------------------------------------------------------------------------------------///

////////////////////////////////////////////////////////////////////////////////////////////
///////////////////						List						////////////////////////

template<typename T>const typename List<T>::ConstIterator List<T>::begin()const
{
	return Head;
}
template<typename T>const typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template<typename T>typename const List<T>::ConstReverseIterator List<T>::rbegin()const
{
	return Tail;
}
template<typename T>typename const List<T>::ConstReverseIterator List<T>::rend()const
{
	return nullptr;
}

//						type			name		(parameters)
template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

//					Constructors:
template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
#ifdef DEBUG
	cout << "LConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template<typename T>List<T>::List(const List<T>& other) :List()
{
	*this = other;
#ifdef DEBUG
	cout << "LCopyConstruct:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::~List()
{
	//while (Head)pop_front();
	while (Tail)pop_back();
#ifdef DEBUG
	cout << "LDestructor:\t" << this << endl;
#endif // DEBUG
}

//				Operators:
template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_back(Temp->Data);
#ifdef DEBUG
	cout << "LCopyAssignment:\t" << this << endl;
#endif // DEBUG
	return *this;
}

//				Adding elemnts:
template<typename T>void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;	//Ключевое слово 'return' прерывает работу функции 
				//и возвращает управление на место вызова. 
	}
	Head = Head->pPrev = new Element(Data, Head);
	size++;
}
template<typename T>void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)return push_front(Data);
	Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}
template<typename T>void List<T>::insert(T Data, int Index)
{
	if (Index > size)return;
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
	}
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	size++;
}

//					Removing elements:
template<typename T>void List<T>::pop_front()
{
	if (Head == nullptr&&Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		return;
	}
	//1) Исключаем элемент из списка:
	Head = Head->pNext;
	//2) Удаляем элемент из памяти:
	delete Head->pPrev;
	//3) "Забываем" про удаленный элемент:
	Head->pPrev = nullptr;
	size--;
}
template<typename T>void List<T>::pop_back()
{
	if (Head == Tail)return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}

//					Methods:
template<typename T>void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
}
template<typename T>void List<T>::reverse_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
}
///////////////////						List						////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat;
	for (typename List<T>::ConstIterator it = left.begin(); it != left.end(); ++it)cat.push_back(*it);
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)cat.push_back(*it);
	return cat;
}
template<typename T>void print(const List<T>& list)
{
	for (typename List<T>::ConstIterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
}
template<typename T>void reverse_print(const List<T>& list)
{
	for (typename List<T>::ConstReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		//*it*=10;
		cout << *it << tab;
	}
	cout << endl;
}

//#define BASE_CHECK
//#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int value;
	int index;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

#ifdef ITERATORS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	//list.print();
	//list.reverse_print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	//for (int& i : list3)i *= 10;
	//for (int i : list3)cout << i << tab; cout << endl;
	print(list3);
	reverse_print(list3);
	
	List<double> d_list_1 = { 2.7, 3.14, 8.2 };
	List<double> d_list_2 = { 7.3, 5.4};
	List<double> d_list_3 = d_list_1 + d_list_2;
	for (double i : d_list_1)cout << i << tab; cout << endl;
	for (double i : d_list_2)cout << i << tab; cout << endl;
	print(d_list_3);
	reverse_print(d_list_3);

	List<std::string> s_list_1 = { "Хорошо", "Живет", "на", "свете" };
	List<std::string> s_list_2 = { "Винни", "Пух" };
	List<std::string> s_list_3 = s_list_1 + s_list_2;
	for (List<std::string>::Iterator it = s_list_3.begin(); it != s_list_3.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	print(s_list_2);
	print(s_list_3);
	reverse_print(s_list_3);

	List<char> c_list = { 'S', 'a', 'm', 's', 'u', 'n', 'g' };
	print(c_list);
	reverse_print(c_list);
}