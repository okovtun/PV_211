#include"ForwardList.cpp"

//#define BASE_CHECK
//#define OPERATOR_PLUS
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST
//#define PREFORMANCE_TEST

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	cout << delimiter << endl;
	//list.push_back(123);
	//list.pop_front();
	//list.pop_back();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();

	/*ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();*/
#endif // BASE_CHECK

#ifdef OPERATOR_PLUS
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1 = list1;
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	//ForwardList list3 = list1 + list2;	//CopyConstructor
	cout << delimiter << endl;
	ForwardList list3;
	list3 = list1 + list2;
	cout << delimiter << endl;
	list3.print();
#endif // OPERATOR_PLUS

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
	cout << typeid(arr).name() << endl;
	cout << sizeof(arr) << endl;
	//Range-based for:
	//https://legacy.cplusplus.com/doc/tutorial/control/#:~:text=equal%20to%2050.-,Range%2Dbased%20for%20loop,-The%20for%2Dloop
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
	print(arr);
#endif // RANGE_BASE_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3, 5, 8, 13, 21 };
	/*for (int i : list)
	{
		//i *= 10;
		cout << i << tab;
	}*/
	cout << endl;
	print(list);
	list.print();
#endif // RANGE_BASED_FOR_LIST

#ifdef PREFORMANCE_TEST
	int n;
	cout << "Введите размер списка: "; cin >> n;
	clock_t start = clock();
	ForwardList<int> list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	clock_t end = clock();
	double delta = double(end - start) / CLOCKS_PER_SEC;
	cout << "Список заполнен за " << delta << " секунд." << endl;
	//list.print();
	start = clock();
	ForwardList<int> list2 = list;
	end = clock();
	delta = double(end - start) / CLOCKS_PER_SEC;
	cout << "Список скопирован за " << delta << " секунд." << endl;
	//list2.print();  
#endif // PREFORMANCE_TEST

	ForwardList<int> i_list = { 3, 5, 8, 13, 21 };
	for (int i : i_list)cout << i << tab; cout << endl;

	ForwardList<double> d_list = { 2.7, 3.14, 5.1, 8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;

	ForwardList<std::string> s_list = { "Хорошо", "живет", "на", "свете", "Винни", "Пух" };
	for (std::string i : s_list)cout << i << tab; cout << endl;
}

/*
----------------------------------------------------
Class object;		//обычный класс
Class<type> object;	//шаблонный класс
----------------------------------------------------
*/