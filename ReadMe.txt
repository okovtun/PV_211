https://github.com/okovtun/PV_211.git
https://www.youtube.com/watch?v=8WOtMA8pv4Y&list=PLeqyOOqxeiIMa-0fDCp-lpJ_qmDrZBmRI

TOREAD:
https://en.cppreference.com/w/

TODO:
1. Реализовать классы Circle и Triangle. Для рисования этих фигур используются следующие функции:
	https://learn.microsoft.com/en-us/windows/win32/gdi/about-filled-shapes
2. Для каждой фигуры добавить атрибут "Цвет";

TODO:
Реализовать иерархию геометрических фигур: круг, треугольник, квадрат, прямоугольник ...
Для каждой фигуры вывести на экран ее первичные свойства, такие как длина стороны квадрата,
радиус круга...., и вторичные свойства: площадь и периметр. Так же каждую фигуру нужно нарисовать.

DONE:
1. В проекте Files, разел WRITE_TO_FILE имя файла должно вводиться с клавиатуры;		DONE
2. Если при вводе имени пользователь не написал расширение имени файла, то программа сама должна добавить "*.txt";	DONE
3. Из файла "201 RAW.txt" создать новый файл "201 ready.txt", в котором столбцы с IP-адресом и MAC-адресом должны быть поменяны местами;	DONE
4. Из файла "201 RAW.txt" создать новый файл "201.dhcpd", который должен иметь следующий формат:	DONE
	https://github.com/okovtun/PV_211/blob/master/Inheritance/Task/201.dhcpd
5. Сохранить группу в файл;
6. Загрузить группу из файла;

DONE:
Реализовать проект Academy;

DONE:
От ветки 'master' создать ветку 'Separation', 
и в этой ветке вынести в отдельные файлы сначала класс 'Point',
а потом класс 'Fraction'.

DONE:
Добавить в класс String Move-методы:
https://legacy.cplusplus.com/doc/tutorial/classes2/

DONE:
1. Пять проектов на выбор залить на GitHub;
2. Проверочный код в проекте IntroductionToOOP\String:
	https://github.com/okovtun/PV_211/blob/3f251e284849ad3896fd7e019ca2d3d8571497b9/IntroductionToOOP/String/main.cpp#L48
   должен заработать.

DONE:
1. Проверочный код в секции HOME_WORK_1 должен заработать:
	https://github.com/okovtun/PV_211/blob/5afd5711a7935f874783ff64f552bcc10ae46edd/IntroductionToOOP/Fraction/main.cpp#L415
2. Проверочный код в секции HOME_WORK_2 должен заработать:
	https://github.com/okovtun/PV_211/blob/5afd5711a7935f874783ff64f552bcc10ae46edd/IntroductionToOOP/Fraction/main.cpp#L422

DONE:
Проверочный код должен заработать:
	Fraction A;
	cout << "Введите простю дробь: "; cin >> A;
	cout << A << endl;

	Необходимо предусмотреть следующие варианты ввода:
		5
		1/2
		2 3/4
		2(3/4)

DONE:
Для коасса Fraction перегрузить следующие операторы:
	1. Арифметические операторы:+, -, *, /;				DONE
	2. Составные присваивания:	+=, -=, *=, /=;			DONE
	3. Операторы сравнения:		==, !=, >, <, >=, <=;	DONE
	4. Написать метод ??? reduce(???), который сокращает дробь;	DONE
		https://www.webmath.ru/poleznoe/formules_12_7.php

DONE:
0. Выучить теорию!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
1. В Solution 'IntroductionToOOP' добавить проект 'Fraction', и в нем реализовать класс 'Fraction',
   описывающий простую дробь. В классе должны быть все необходимые методы и операторы;

DONE:
0. Выучить теорию!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
1. Написать метод ??? distance(???), который возвращает расстояние до указанной точки;		DONE
2. Написать функцию ??? distance(???), которая возвращает расстояние между двумя точками;	DONE