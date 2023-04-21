#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;

using std::cin;
using std::cout;
using std::endl;

#define delimeter "\n-----------------------------\n"

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			//cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			//cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;

	size_t size;

public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
		size = 0;
		cout << "TConstructor:\t" << this << endl;
	}

	Tree(const std::initializer_list<int>& il) : Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			insert(*it, Root);
		}
	}

	~Tree()
	{
		clear(Root);
		cout << "TDestructor:\t" << this << endl;
	}

	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int Count()const
	{
		return Count(Root);
	}
	int Sum()const
	{
		return Sum(Root);
	}
	int Avg()const
	{
		return (double)Sum(Root) / Count(Root);
	}
	int Depth()const
	{
		return Depth(Root);
	}
	void clear()
	{
		clear(Root);
		Root = nullptr;
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
	void print_tree(int level)const
	{
		print_tree(Root, level);
	}


private:
	void clear(Element* Root)
	{
		if (Root != NULL)
		{
			clear(Root->pLeft);
			clear(Root->pRight);
			delete Root;
		}
	}

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
		size++;
	}

	int minValue(Element* Root)const
	{
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		if (Root == nullptr)return 0;
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
		if (Root == nullptr)return 0;
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}

	int Count(Element* Root)const
	{
		//if (Root == nullptr) return 0;
		//return Count(Root->pLeft) + Count(Root->pRight) + 1;
		return Root == nullptr ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;
	}

	int Sum(Element* Root)const
	{
		//if (Root == nullptr) return 0;
		//return Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
		return Root == nullptr ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}

	double Avg(Element* Root)const
	{
		return (double)Sum(Root) / (double)Count(Root);
	}

	int Depth(Element* Root)const
	{
		//if (Root == nullptr) return 0;
		//return max(Depth(Root->pLeft) + 1, Depth(Root->pRight) + 1);

		return Root == nullptr ? 0 : max(Depth(Root->pLeft) + 1, Depth(Root->pRight) + 1);

		//if (Depth(Root->pLeft) + 1 >
		//	Depth(Root->pRight) + 1)
		//	return Depth(Root->pLeft) + 1;
		//else return Depth(Root->pRight) + 1;
	}

	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (Count(Root->pLeft) > Count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}

	void print_tree(Element* Root, int level)const
	{
		if (Root == nullptr)return;
		print_tree(Root->pLeft, level + 1);
		for (int i = 0; i < level; i++)cout << "   ";
		cout << Root->Data << endl;
		print_tree(Root->pRight, level + 1);


	}

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
};

class UniqueTree :public Tree
{
public:

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
};

//#define BASE_CHECK
#define DEPTH_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK

	Tree tree;
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	//time_t t// цепляем правого потомка_start = time(NULL);
	//clock_t c_start = clock();
	for (int i = 0; i < n; i++)
	{
		int num = rand() % 100;
		//cout << num << "\t";
		tree.insert(num);
	}
	//clock_t c_end = clock();
	//time_t t_end = time(NULL);
	//cout << "Дерево заполнено за " << t_end - t_start << " секунд\n";
	//cout << "Дерево заполнено за " << double(c_end - c_start) / CLOCKS_PER_SEC << " секунд\n";
	tree.print();
	cout << endl;
	cout << delimeter << endl;

	cout << "Количество элементов: " << tree.Count() << endl;
	cout << "Сумма элементов дерева: " << tree.Sum() << endl;
	cout << delimeter << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Среднее арифметическое: " << tree.Avg() << endl;
	cout << delimeter << endl;
	cout << "Глубина дерева: " << tree.Depth() << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	//u_tree.print(u_tree.getRoot());
	cout << endl;
	cout << delimeter << endl;
	cout << "Количество элементов: " << u_tree.Count() << endl;
	cout << "Сумма элементов дерева: " << u_tree.Sum() << endl;
	cout << delimeter << endl;
	cout << "Минимальное значение в дереве: " << u_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << u_tree.maxValue() << endl;
	cout << "Среднее арифметическое: " << u_tree.Avg() << endl;
	cout << delimeter << endl;
	cout << "Глубина дерева: " << u_tree.Depth() << endl;

#endif // BASE_CHECK

#ifdef DEPTH_CHECK
	Tree tree = { 50, 25, 75, 16, 32, 64, 90 };
	tree.print();
	cout << endl;
	cout << "Глубина дерева: " << tree.Depth() << endl;

	int value;
	cout << "Введите удаляемое значение: "; cin >> value;
	tree.erase(value);
	tree.print();
	cout << delimeter << endl;
	tree.print_tree(0);


#endif // DEPTH_CHECK
}