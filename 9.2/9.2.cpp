#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці

using namespace std;

enum Spec { KOMP, INF, MAT, FIZ, TR };

string specStr[] = { "Комп'ютерні науки", "Інформатика", "Математика ті економіка", "Фізика та інформатика", "Трудове навчання" };

struct Student
{
	string prizv;
	int kurs;
	Spec spec;
	int fiz;
	int mat;
	double avr;
	union
	{
		int pr;
		int ch;
		int pedo;
	};
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Search(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Spec spec, const int kurs);

int main()

{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	int N;
	cout << "Введіть кількість студентів N: "; cin >> N;

	Student* p = new Student[N];

	double proc;
	int menuItem;
	int ispec;
	Spec spec;
	string prizv;
	int kurs;
	int found;

	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - вивід прізвищ студентів, які вчаться без трійок," << endl;
		cout << " та кількості відмінників з фізики" << endl;
		cout << " [4] - фізичне впорядкування данних" << endl;
		cout << " [5] - індексне впорядкування та вивід данних" << endl;
		cout << " [6] - бінарний пошук" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;

		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Search(p, N);
			break;
		case 4:
			Sort(p, N);
		case 5:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 6:
			cout << "Введіть ключі пошуку:" << endl;
			cout << " спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
			cin >> ispec;
			spec = (Spec)ispec;
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
			cout << " прізвище: "; getline(cin, prizv);
			cout << " курс: "; cin >> kurs;
			cout << endl;
			if ((found = BinSearch(p, N, prizv, spec, kurs)) != -1)
				cout << "Знайдено студента в позиції " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	system("pause");
	return 0;
}

void Create(Student* p, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;

		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " курс: "; cin >> p[i].kurs;
		cout << " спціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
		cin >> spec;
		p[i].spec = (Spec)spec;
		switch (p[i].spec)
		{
		case KOMP:
			cout << " оцінка з фізики : "; cin >> p[i].fiz;
			cout << " оцінка з математики : "; cin >> p[i].mat;
			cout << " оцінка з програмування : "; cin >> p[i].pr;
			p[i].avr = (p[i].fiz + p[i].mat + p[i].pr) / 3;
			break;
		case INF:
			cout << " оцінка з фізики : "; cin >> p[i].fiz;
			cout << " оцінка з математики : "; cin >> p[i].mat;
			cout << " оцінка з чисельних методів : "; cin >> p[i].ch;
			p[i].avr = (p[i].fiz + p[i].mat + p[i].ch) / 3;
			break;
		case MAT:
			cout << " оцінка з фізики : "; cin >> p[i].fiz;
			cout << " оцінка з математики : "; cin >> p[i].mat;
			cout << " оцінка з педагогіки : "; cin >> p[i].pedo;
			p[i].avr = (p[i].fiz + p[i].mat + p[i].pedo) / 3;
			break;
		case FIZ:
			cout << " оцінка з фізики : "; cin >> p[i].fiz;
			cout << " оцінка з математики : "; cin >> p[i].mat;
			cout << " оцінка з педагогіки : "; cin >> p[i].pedo;
			p[i].avr = (p[i].fiz + p[i].mat + p[i].pedo) / 3;
			break;
		case TR:
			cout << " оцінка з фізики : "; cin >> p[i].fiz;
			cout << " оцінка з математики : "; cin >> p[i].mat;
			cout << " оцінка з педагогіки : "; cin >> p[i].pedo;
			p[i].avr = (p[i].fiz + p[i].mat + p[i].pedo) / 3;
			break;
		}
		cout << endl;
	}
}

void Search(Student* p, const int N)
{
	cout << "Студенти, які вчаться без трійок:" << endl;
	for (int i = 0; i < N; i++)
	{
		switch (p[i].spec)
		{
		case KOMP:
			if (p[i].fiz > 3 && p[i].mat > 3 && p[i].pr > 3)
				cout << "    " << p[i].prizv << endl;
			break;
		case INF:
			if (p[i].fiz > 3 && p[i].mat > 3 && p[i].ch > 3)
				cout << "    " << p[i].prizv << endl;
			break;
		case MAT:
			if (p[i].fiz > 3 && p[i].mat > 3 && p[i].pedo > 3)
				cout << "    " << p[i].prizv << endl;
			break;
		case FIZ:
			if (p[i].fiz > 3 && p[i].mat > 3 && p[i].pedo > 3)
				cout << "    " << p[i].prizv << endl;
			break;
		case TR:
			if (p[i].fiz > 3 && p[i].mat > 3 && p[i].pedo > 3)
				cout << "    " << p[i].prizv << endl;
			break;
		}
	}
	cout << "Кількість відмінників з фізики: ";

	int count = 0;

	for (int i = 0; i < N; i++)
	{
		if (p[i].fiz == 5)
			count++;
	}
	cout << count;
}

void Print(Student* p, const int N)
{
	cout << "============================================================================================================================"
		<< endl;
	cout << "| № |    Прізвище    | Курс |      Спеціальність      | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |"
		<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(15) << left << p[i].prizv
			<< "| " << setw(4) << right << p[i].kurs << " "
			<< "| " << setw(24) << left << specStr[p[i].spec];
		switch (p[i].spec)
		{
		case KOMP:
			cout << "| " << setw(6) << fixed << right << p[i].fiz << " |";
			cout << setw(11) << fixed << right << p[i].mat << " |";
			cout << setw(14) << fixed << right << p[i].pr << " |";
			cout << setw(18) << fixed << "|";
			cout << setw(13) << fixed << "|" << endl;
			break;
		case INF:
			cout << "| " << setw(6) << fixed << right << p[i].fiz << " |";
			cout << setw(11) << fixed << right << p[i].mat << " |";
			cout << setw(16) << fixed << "|";
			cout << setw(16) << fixed << right << p[i].ch << " |";
			cout << setw(13) << fixed << "|" << endl;
			break;
		case MAT:
			cout << "| " << setw(6) << fixed << right << p[i].fiz << " |";
			cout << setw(11) << fixed << right << p[i].mat << " |";
			cout << setw(16) << fixed << "|";
			cout << setw(18) << fixed << "|";
			cout << setw(11) << fixed << right << p[i].pedo << " |" << endl;
			break;
		case FIZ:
			cout << "| " << setw(6) << fixed << right << p[i].fiz << " |";
			cout << setw(11) << fixed << right << p[i].mat << " |";
			cout << setw(16) << fixed << "|";
			cout << setw(18) << fixed << "|";
			cout << setw(11) << fixed << right << p[i].pedo << " |" << endl;
			break;
		case TR:
			cout << "| " << setw(6) << fixed << right << p[i].fiz << " |";
			cout << setw(11) << fixed << right << p[i].mat << " |";
			cout << setw(16) << fixed << "|";
			cout << setw(18) << fixed << "|";
			cout << setw(11) << fixed << right << p[i].pedo << " |" << endl;
			break;
		}
	}
	cout << "============================================================================================================================"
		<< endl;
	cout << endl;
}

void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].spec > p[i1 + 1].spec)
				||
				(p[i1].spec == p[i1 + 1].spec &&
				 p[i1].avr < p[i1 + 1].avr)
				||
				(p[i1].spec == p[i1 + 1].spec &&
				 p[i1].avr == p[i1 + 1].avr &&
				 p[i1].prizv > p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
	cout << "Готово!";
}

int* IndexSort(Student* p, const int N)
{
	int* I = new int[N]; // створили індексний масив
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними
	int i, j, value; // починаємо сортувати масив індексів
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].spec > p[value].spec) 
				||
				(p[I[j]].spec == p[value].spec &&
				 p[I[j]].avr < p[value].avr)
				||
				(p[I[j]].spec == p[value].spec &&
				 p[I[j]].avr == p[value].avr &&
				 p[I[j]].prizv > p[value].prizv)); j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(Student* p, int* I, const int N)
{ // аналогічно функції Print(), але замість звертання p[i]...
 // використовуємо доступ за допомогою індексного масиву І: p[I[i]]...
	cout << "============================================================================================================================"
		<< endl;
	cout << "| № |    Прізвище    | Курс |      Спеціальність      | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |"
		<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(15) << left << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].kurs << " "
			<< "| " << setw(24) << left << specStr[p[I[i]].spec];
		switch (p[i].spec)
		{
		case KOMP:
			cout << "| " << setw(6) << fixed << right << p[I[i]].fiz << " |";
			cout << setw(11) << fixed << right << p[I[i]].mat << " |";
			cout << setw(14) << fixed << right << p[I[i]].pr << " |";
			cout << setw(18) << fixed << "|";
			cout << setw(13) << fixed << "|" << endl;
			break;
		case INF:
			cout << "| " << setw(6) << fixed << right << p[I[i]].fiz << " |";
			cout << setw(11) << fixed << right << p[I[i]].mat << " |";
			cout << setw(16) << fixed << "|";
			cout << setw(16) << fixed << right << p[I[i]].ch << " |";
			cout << setw(13) << fixed << "|" << endl;
			break;
		case MAT:
			cout << "| " << setw(6) << fixed << right << p[I[i]].fiz << " |";
			cout << setw(11) << fixed << right << p[I[i]].mat << " |";
			cout << setw(16) << fixed << "|";
			cout << setw(18) << fixed << "|";
			cout << setw(11) << fixed << right << p[I[i]].pedo << " |" << endl;
			break;
		case FIZ:
			cout << "| " << setw(6) << fixed << right << p[I[i]].fiz << " |";
			cout << setw(11) << fixed << right << p[I[i]].mat << " |";
			cout << setw(16) << fixed << "|";
			cout << setw(18) << fixed << "|";
			cout << setw(11) << fixed << right << p[I[i]].pedo << " |" << endl;
			break;
		case TR:
			cout << "| " << setw(6) << fixed << right << p[i].fiz << " |";
			cout << setw(11) << fixed << right << p[I[i]].mat << " |";
			cout << setw(16) << fixed << "|";
			cout << setw(18) << fixed << "|";
			cout << setw(11) << fixed << right << p[I[i]].pedo << " |" << endl;
			break;
		}
	}
	cout << "============================================================================================================================"
		<< endl;
	cout << endl;
}

int BinSearch(Student* p, const int N, const string prizv, const Spec spec, const int kurs)
{
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].spec == spec && p[m].kurs == kurs)
			return m;
		if (((p[m].kurs < kurs)
			||
			(p[m].kurs == kurs &&
				p[m].spec < spec)
			||
			(p[m].kurs == kurs &&
				p[m].spec == spec &&
				p[m].prizv > prizv)))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}