//BinaryTree
#include<iostream>
#include<ctime>
#include<algorithm>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define DEBUG

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
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;	//Сразу же объявляем Root - указатель на корневой элемент.
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
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
	void tree_print()const
	{
		tree_print(0, 50);
		cout << endl;
	}
private:
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
		/*if (Root == nullptr)return 0;
		else return Count(Root->pLeft) + Count(Root->pRight) + 1;*/
		//return Root == nullptr ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;
		//return !Root ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;
		return Root ? Count(Root->pLeft) + Count(Root->pRight) + 1 : 0;
	}
	int Sum(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;*/
		return Root == nullptr ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}
	double Avg(Element* Root)const
	{
		return (double)Sum(Root) / Count(Root);
	}
	int Depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		return std::max(Depth(Root->pLeft), Depth(Root->pRight)) + 1;
		/*int l_depth = Depth(Root->pLeft) + 1;
		int r_depth = Depth(Root->pRight) + 1;
		return l_depth > r_depth ? l_depth : r_depth;
*/
	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
	/*int element_depth(int Data, Element* Root)
	{
		if(Root == nullptr)
	}*/
public:
	void depth_print(Element* Root, int depth, int width)const
	{
		if (Root == nullptr)
		{
			cout.width(width);
			cout << "";
			return;
		}
		if (depth == 0)
		{
			cout.width(width);
			cout << Root->Data /*<< "\t"*/;
			return;
		}
		depth_print(Root->pLeft, depth - 1, width);
		cout.width(width);
		cout << " ";
		depth_print(Root->pRight, depth - 1, width);
	}
	void tree_print(/*Element* Root,*/ int depth, int width)const
	{
		//if (Root == nullptr)return;
		if (depth > Depth(Root))return;
		depth_print(Root, depth, width);
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		//tree_print(Root->pLeft, depth + 1);
		//tree_print(Root->pRight, depth + 1);
		tree_print(/*Root,*/ depth + 1, width / 2);
	}
	/*void tree_print(Element* Root, int depth, int i=0)
	{
		if (Root == nullptr)return;
		if (depth - this->Depth(Root) == i)cout << Root->Data << "\t";
	}*/
	void balance(Element* Root)
	{
		if (Root == nullptr)return;
		//if (abs(Count(Root->pLeft) - Count(Root->pRight)) < 3)return;
		if (abs(Count(Root->pLeft) - Count(Root->pRight)) < 2)return;
		
		if (Count(Root->pRight) < Count(Root->pLeft))
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Root->Data);
			else insert(Root->Data, Root->pRight);
			Root->Data = maxValue(Root->pLeft);
			erase(maxValue(Root->pLeft), Root->pLeft);
		}
		if (Count(Root->pLeft) < Count(Root->pRight))
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Root->Data);
			else insert(Root->Data, Root->pLeft);
			Root->Data = minValue(Root->pRight);
			erase(minValue(Root->pRight), Root->pRight);
		}
		balance(Root->pLeft);
		balance(Root->pRight);
		balance(Root);
	}
};
class UniqueTree :public Tree
{

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
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

//#define BASE_CHECK
//#define DEPTH_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	Tree tree;
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	//time_t t_start = time(NULL);
	clock_t c_start = clock();
	for (int i = 0; i < n; i++)
	{
		int num = rand() % 100;
		//cout << num << "\t";
		tree.insert(num);
	}
	//time_t t_end = time(NULL);
	clock_t c_end = clock();
	//cout << "Дерево заполнено за " << t_end - t_start << " секунд\n";
	cout << "Дерево заполнено за " << double(c_end - c_start) / CLOCKS_PER_SEC << " секунд\n";
	//tree.clear();
	//tree.print(tree.getRoot());
	cout << endl;
	c_start = clock();
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	c_end = clock();
	cout << "Найдено за " << double(c_end - c_start) / CLOCKS_PER_SEC << " секунд.\n";
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов дерева: " << tree.Count() << endl;
	cout << "Сумма элементов дерева: " << tree.Sum() << endl;
	cout << "Среднее-арифметическое элементов дерева: " << tree.Avg() << endl;
	c_start = clock();
	cout << "Глубина дерева: " << tree.Depth() << endl;
	c_end = clock();
	cout << "Вычислина за " << double(c_end - c_start) / CLOCKS_PER_SEC << " секунд.\n";
	tree.tree_print();


	/*UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << u_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << u_tree.maxValue() << endl;
	cout << "Количество элементов дерева: " << u_tree.Count() << endl;
	cout << "Сумма элементов дерева: " << u_tree.Sum() << endl;
	cout << "Среднее-арифметическое элементов дерева: " << u_tree.Avg() << endl;
	cout << "Глубина дерева: " << u_tree.Depth() << endl;*/
#endif // BASE_CHECK

#ifdef DEPTH_CHECK
	Tree tree = { 50, 25, 75, 16, 32, 64, 90, 28, 91, 88 };
	tree.print();
	cout << "Глубина дерева: " << tree.Depth() << endl;
	int depth;
	//cout << "Введите глубину: "; cin >> depth;
	//tree.depth_print(tree.getRoot(), depth);
	tree.tree_print();
	int value;
	//cout << "Введите удаляемое значение: "; cin >> value;
	//tree.erase(value);
	//tree.print();
#endif // DEPTH_CHECK

	Tree tree = { 55, 34, 21, 13, 8, 5, 3 };
	tree.balance(tree.getRoot());
	tree.tree_print();
	tree.print();
	/*int value;
	cout << "Введите удаляемое значение: "; cin >> value;
	tree.erase(value);
	tree.print();*/

}