#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n--------------------------------\n"

template<typename T>T** Allocate(const int rows, const int cols);
template<typename T>void Clear(T** arr, const int rows);

void FillRand(int arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(double arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(int** arr, const int rows, const int cols);
void FillRand(double** arr, const int rows, const int cols);

template<typename T>void Print(T arr[], const int n);
template<typename T>void Print(T** arr, const int rows, const int cols);

template<typename T>T* push_back(T arr[], int& n, T value);
template<typename T>T* push_front(T arr[], int& n, T value);
template<typename T>T* insert(T arr[], int& n, T value, int index);

template<typename T>T* pop_back(T arr[], int& n);
template<typename T>T* pop_front(T arr[], int& n);

template<typename T>T** push_row_back(T** arr, int& rows, const int cols);
template<typename T>T** pop_row_back( T** arr, int& rows, const int cols);

template<typename T>void push_col_back(T** arr, const int rows, int& cols);
template<typename T>void pop_col_back( T** arr, const int rows, int& cols);

//#define POINTERS_AND_ARRAYS
//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2

void main()
{
	setlocale(LC_ALL, "");

#ifdef POINTERS_AND_ARRAYS
	const int n = 5;
	int arr[n] = { 3, 5, 8, 13, 21 };
	cout << arr << endl;
	cout << *arr << endl;
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << *(arr + i) << "\t";
	}
	cout << endl;
#endif // POINTERS_AND_ARRAYS

#ifdef DYNAMIC_MEMORY_1
	int n;
	cout << "������� ������ �������: "; cin >> n;
	double* arr = new double[n];

	FillRand(arr, n);
	Print(arr, n);

	int value;
	cout << "������� ����������� ��������: "; cin >> value;
	arr = push_back(arr, n, (double)value);
	Print(arr, n);
	cout << "������� ����������� ��������: "; cin >> value;
	Print(arr = push_front(arr, n, (double)value), n);

	int index;
	cout << "������� ����������� ��������: "; cin >> value;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	Print(arr = insert(arr, n, (double)value, index), n);

	Print(arr = pop_back(arr, n), n);
	Print(arr = pop_front(arr, n), n);

	delete[] arr;
#endif // DYNAMIC_MEMORY_1

#ifdef DYNAMIC_MEMORY_2
	int rows;
	int cols;
	cout << "������� ���������� �����: "; cin >> rows;
	cout << "������� ���������� ��������: "; cin >> cols;
	//1) ������� ������ ����������
	double** arr = Allocate<double>(rows, cols);

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);
	cout << delimiter << endl;

	arr = push_row_back(arr, rows, cols);
	FillRand(arr[rows - 1], cols, 100, 200);
	Print(arr, rows, cols);
	cout << delimiter << endl;
	
	arr = pop_row_back(arr, rows, cols);
	Print(arr, rows, cols);
	cout << delimiter << endl;

	push_col_back(arr, rows, cols);
	Print(arr, rows, cols);
	cout << delimiter << endl;

	pop_col_back(arr, rows, cols);
	Print(arr, rows, cols);
	cout << delimiter << endl;

	Clear(arr, rows);
#endif // DYNAMIC_MEMORY_2

}

template<typename T>T** Allocate(const int rows, const int cols)
{
	T** arr = new T*[rows];
	//2) �������� ������ ��� ������, � ������ ����� ���������� � �������� ������� ����������:
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new T[cols];
	}
	return arr;
}
template<typename T>void Clear(T** arr, const int rows)
{
	//1) ������� ������� ������ ���:
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	//2) ������� ������ ����������:
	delete[] arr;
}

void FillRand(int arr[], const int n, int minRand, int maxRand)
{
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand - minRand) + minRand;
	}
}
void FillRand(double arr[], const int n, int minRand, int maxRand)
{
	minRand *= 100;
	maxRand *= 100;
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand - minRand) + minRand;
		*(arr + i) /= 100;
	}
}

void FillRand(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % 100;
		}
	}
}
void FillRand(double** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % 10000;
			arr[i][j] /= 100;
		}
	}
}

template<typename T>void Print(T arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}
template<typename T>void Print(T** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << tab;
		}
		cout << endl;
	}
}

template<typename T>T* push_back(T arr[], int& n, T value)
{
	//1) ������� ����� ������ ������� �������:
	T* buffer = new T[n + 1]{};
	//2) �������� ��� ���������� ��������� ������� � ����� ������:
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}
	//3) ������� �������� ������:
	delete[] arr;
	//4) ��������� ����� ��������� ������� ������� ������ �������:
	arr = buffer;
	//5) ������ ����� ����� ����� � ����� ������� 'arr' ����� �������� ��� ���� ��������:
	arr[n] = value;
	//6) ����� ���������� �������� � ������, ���������� ��� ��������� ������������� �� 1
	n++;
	return buffer;
}
template<typename T>T* push_front(T arr[], int& n, T value)
{
	T* buffer = new T[n + 1]{};
	for (int i = 0; i < n; i++)	buffer[i + 1] = arr[i];
	delete[] arr;
	buffer[0] = value;
	n++;
	return buffer;
}
template<typename T>T* insert(T arr[], int& n, T value, int index)
{
	if (index<0 || index>n)return arr;
	T* buffer = new T[n + 1]{};
	/*for (int i = 0; i < index; i++)buffer[i] = arr[i];
	for (int i = index; i < n; i++)buffer[i + 1] = arr[i];*/
	for (int i = 0; i < n; i++)
	{
		/*if (i < index)	buffer[i] = arr[i];
		else			buffer[i + 1] = arr[i];*/
		//(i < index ? buffer[i] : buffer[i + 1]) = arr[i];
		buffer[i < index ? i : i + 1] = arr[i];
	}
	delete[] arr;
	buffer[index] = value;
	n++;
	return buffer;
}

template<typename T>T* pop_back(T arr[], int& n)
{
	T* buffer = new T[--n]{};
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}
template<typename T>T* pop_front(T arr[], int& n)
{
	T* buffer = new T[--n]{};
	for (int i = 0; i < n; i++)buffer[i] = arr[i + 1];
	delete[] arr;
	return buffer;
}

template<typename T>T** push_row_back(T** arr, int& rows, const int cols)
{
	return push_back(arr, rows, new T[cols]{});
}
template<typename T>T** pop_row_back(T** arr, int& rows, const int cols)
{
	//1) ������� ��������� ������ �������:
	delete[] arr[rows - 1];
	//2) ������������� ������ ����������:
	return pop_back(arr, rows);
}

template<typename T>void push_col_back(T** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		arr[i] = push_back(arr[i], cols, T());
		cols--;
		//T() - �������� �� ��������� ��� ���������� ����.
	}
	cols++;
}
template<typename T>void pop_col_back(T** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		arr[i] = pop_back(arr[i], cols);
		cols++;
	}
	cols--;
}