#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void vvod_b(double* b, int n) {
	if (n <= 4) {
		for (int i = 0; i < n; i++) {
			cin >> b[i];
		}
	}
	else {
		for (int i = 0; i < n; i++) {
			b[i] = rand() % 101;
		}
	}
}

void vvod_A(double** A, int n) {
	if (n <= 4) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> A[i][j];
	}
	else {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				A[i][j] = rand() % 101;
	}
}

double pr(double* x, double* b, double** A, int n) {
	double p, maxp = 0;
	for (int i = 0; i < n; i++) {
		p = 0;
		for (int j = 0; j < n; j++) {
			p = A[i][j] * x[j] + p;
		}
		if (maxp < fabs(p - b[i])) maxp = fabs(p - b[i]);
	}
	return maxp;
}

void trans(double** a, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			double tmp = a[i][j];
			a[i][j] = a[j][i];
			a[j][i] = tmp;
		}
	}
}

void printab(double** A, double* b, int n) {
	if (n <= 15) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << A[i][j] << ' ';
			}
			cout << '|' << ' ' << b[i] << endl;
		}
	}
	else {
		cout << "Слишком большая система для вывода" << endl;
	}
}

void gauss(double** A, double* b, double* x, int size) {
	int i, j, k; double d;
	for (j = 0; j < size; j++) {
		for (i = j + 1; i < size; i++) {
			d = A[i][j] / A[j][j];
			for (k = j; k < size; k++) {
				A[i][k] -= d * A[j][k];
			}
			b[i] -= d * b[j];
		}
	}
	printab(A, b, size);
	for (i = size - 1; i >= 0; i--) {
		double sum = 0;
		for (j = i + 1; j < size; j++) {
			sum += A[i][j] * x[j];
		}
		x[i] = (b[i] - sum) / A[i][i];
	}
}

void printres(double* x, int n) {
	cout << "Найденные решения:" << endl;
	for (int i = 0; i < n; i++) {
		cout << x[i] << " ";
	}
	cout << endl;
}

int sr(int n) {
	ifstream fs;
	fs.open("Postanovka zadachi.txt");
	fs >> n;
	fs.close();
	return n;
}

void file_write(double** A, double* b, int n) {
	ofstream fs;
	fs.open("Postanovka zadachi.txt");
	fs << n << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fs << A[i][j] << " ";
		}
		fs << endl;
	}
	for (int k = 0; k < n; k++) {
		fs << b[k] << endl;
	}
	fs.close();
}

void file_read(double** A, double* b, double** B, double* c, int n) {
	ifstream fs;
	fs.open("Postanovka zadachi.txt");
	fs >> n;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			fs >> A[i][j];
		}
	for (int k = 0; k < n; k++) {
		fs >> b[k];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			B[i][j] = A[i][j];
		}
		c[i] = b[i];
	}
	fs.close();
}

int main() {
	srand((unsigned int)time(NULL));
	setlocale(LC_ALL, "Russian");
	int n;
	cout << "Введите размер матрицы" << endl;
	cin >> n;
	int fl = 0;
	double max;
	double* x, * b, * c;
	x = new double[n]; b = new double[n]; c = new double[n];
	double** A;
	A = new double* [n];
	for (int i = 0; i < n; i++) {
		A[i] = new double[n];
	}
	double** B;
	B = new double* [n];
	for (int i = 0; i < n; i++) {
		B[i] = new double[n];
	}

	if (n <= 4) {
		cout << "Введите коэффициенты матрицы" << " " << n << "x" << n << endl;
	}
	vvod_A(A, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			B[i][j] = A[i][j];
		}
	}
	if (n <= 4) {
		cout << "Введите правую часть" << endl;
	}
	vvod_b(b, n);
	for (int i = 0; i < n; i++) {
		c[i] = b[i];
	}

	fl = 1;
	//ofstream fs;
	//fs.open("Postanovka zadachi");
	//fs << "Hello, file" << endl;
	//fs.close();

	cout << "\n1 - Печать матрицы\n2 - Транспортирование\n3 - Метод Гаусса\n4 - Изменить матрицу\n5 - Ввод данных в файл\n6 - Вывод данных из файла\n\n";
	int kod = 10;
	while (kod != 0) {
		cin >> kod;
		switch (kod)
		{
		case 1:
			printab(A, b, n);
			break;
		case 2:
			trans(A, n);
			printab(A, b, n);
			break;
		case 3:
			gauss(A, b, x, n);
			printres(x, n);
			max = pr(x, b, A, n);
			cout << "Максимальная разница" << " " << max << endl;
			break;
		case 4:
			delete[] b;
			delete[] x;
			delete[] c;

			for (int i = 0; i < n; i++)
			{
				delete A[i];
			}
			delete[] A;

			for (int i = 0; i < n; i++)
			{
				delete B[i];
			}
			delete[] B;

			cout << "Введите размер матрицы" << endl;
			cin >> n;
			fl = 1;
			x = new double[n]; b = new double[n]; A = new double* [n];
			A = new double* [n];
			for (int i = 0; i < n; i++)
			{
				A[i] = new double[n];
			}
			x = new double[n];
			b = new double[n];
			c = new double[n];

			B = new double* [n];
			for (int i = 0; i < n; i++) {
				B[i] = new double[n];
			}

			if (n <= 4) {
				cout << "Введите коэффициенты матрицы" << " " << n << "x" << n << endl;
			}
			vvod_A(A, n);
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					B[i][j] = A[i][j];
				}
			}
			if (n <= 4) {
				cout << "Введите правую часть" << endl;
			}
			vvod_b(b, n);
			for (int i = 0; i < n; i++) {
				c[i] = b[i];
			}

			break;
		case 5:
			if (fl == 1) {
				file_write(B, c, n);
				cout << "Ввод данных в файл выполнен" << endl;
			}
			else cout << "Для начала введите данные!" << endl;
			break;
		case 6:
			for (int i = 0; i < n; i++) {
				delete[] A[i];
			}
			delete[] A;
			for (int i = 0; i < n; i++) {
				delete[] B[i];
			}
			delete[] B;

			delete[] b;
			delete[] x;
			delete[] c;

			n = sr(n);
			A = new double* [n];
			for (int i = 0; i < n; i++)
			{
				A[i] = new double[n];
			}
			x = new double[n];
			b = new double[n];
			c = new double[n];

			B = new double* [n];
			for (int i = 0; i < n; i++) {
				B[i] = new double[n];
			}
			file_read(A, b, B, c, n);
			cout << "Заполнение матрицы данными из файла выполнено" << endl;
			fl = 1;
			break;
		}
	}
	/*
	printab(A,b,n);
	gauss(A,b,x,n);
	for (int i = 0; i < n; i++) {
		double f;
		f = pr(x,b,A,n);
		//cout.precision(5); //Установка кол-ва знаков после запятой
		cout << fixed; //В формате 0.000000001
		//cout << scientific; //В формате 1.0e-9
		//setprecision(10)
		//cout << defaultfloat; //cout сам решит, сколько знаков выводить
		cout << left << setw(3) << f << endl; //setw(Задать ширину) только на один следующий элемент; left- прижимает вывод влево
	}
	*/
}