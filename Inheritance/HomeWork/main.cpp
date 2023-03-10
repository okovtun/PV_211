#include<iostream>
#include<fstream>
using namespace std;

//#define WRITE_TO_FILE
//#define READ_FROM_FILE
//#define HOME_WORK_T1

const char* UNITS[] = { "B", "kB", "MB", "GB" };

void main()
{
	setlocale(LC_ALL, "");
	//	std::cout << "Hello World";
	//	std::cout << endl;
		//https://legacy.cplusplus.com/doc/tutorial/files/

#ifdef WRITE_TO_FILE

	ofstream fout;			//1) Создаем поток
	fout.open("File.txt", std::ios_base::app);	//2) Открываем поток
	fout << "Hello Files" << endl;//3) Пишем в поток
	fout << "Всем привет" << endl;
	fout.close();			//4) После того как запись в поток выполнена, его обязательно нужно закрыть!!!
	system("notepad File.txt");

#endif // WRITE_TO_FILE
#ifdef READ_FROM_FILEDEBUG

	std::ifstream fin("File.txt");
	cout << "Начальная позиция курсора: " << fin.tellg() << endl;
	fin.seekg(0, ios::end);
	int i = 0;
	int filesize = fin.tellg();
	cout << "Конечная позиция курсора: " << filesize << endl;
	for (; filesize > 1024; i++, filesize /= 1024);
	cout << "Размер файла: " << filesize << " " << UNITS[i] << endl;
	//fin.tellg() - tell get position (говорит позцию считывающего курсора)
	system("PAUSE");
	if (fin.is_open())
	{
		//TODO: будем читать из файла
		const int SIZE = 1024 * 512;
		char sz_buffer[SIZE] = {};
		while (!fin.eof())
		{
			//fin >> sz_buffer;
			fin.getline(sz_buffer, SIZE);	//getline() позволяет ввести строку с пробелами, до заданного разделителя
			//по умолчанию, разделителем для fin.getline() является '\n'
			cout << sz_buffer << endl;
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}

#endif // READ_FROM_FILEDEBUG
#ifdef HOME_WORK_T1

	string fileName;
	cin >> fileName;

	fileName += ".txt";

	ofstream outfile(fileName);
	outfile << "Hello Files" << endl;
	outfile << "Всем привет" << endl;
	outfile.close();
	ifstream infile(fileName);

#endif // HOME_WORK_T1
	/*
		std::ifstream is("201 RAW.txt", std::ifstream::binary);
		if (is)
		{

			is.seekg(0, is.end);
			int length = is.tellg();
			is.seekg(0, is.beg);
			char* buffer = new char[length];
			is.read(buffer, length);

			is.close();
			std::cout.write(buffer, length);
			delete[] buffer;
		}
	*/

	streampos size;
	char* memblock;

	ifstream file("201 RAW.txt", ios::in | ios::binary | ios::ate);
	if (file.is_open())
	{
		size = file.tellg();
		memblock = new char[size];
		file.seekg(0, ios::beg);
		file.read(memblock, size);
		file.close();

		std::cout.write(memblock, size);

		delete[] memblock;
	}

}