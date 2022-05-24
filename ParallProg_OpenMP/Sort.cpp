#include <iostream>
#include <vector>
#include "omp.h"
using namespace std;

const int num = 30000;

bool isSorted(double* a) {
	for (int i = 0; i < num - 1; i++)
		if (a[i] > a[i + 1])
			return false;
	return true;
}
void bubbleSort(double* a) {
	double tmp;
	int i, j;
	for (i = 0; i < num; i++)
		for (j = 0; j < num - 1; j++)
			if (a[j] > a[j + 1])
			{
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
}
void chetNechetSort(double* a) {
	double tmp;
	int i, j;
	for (i = 0; i < num; i++) {
		for (j = (i % 2) ? 0 : 1; j < num - 1; j += 2) {
			if (a[j] > a[j + 1]) {
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
}
void chetNechetSortP(double* array) {
	double tmp;
	int i, j;
#pragma omp parallel private(i, j, tmp)
	for (i = 0; i < num; i++) {
		for (j = (i % 2) ? 0 : 1; j < num - 1; j += 2) {
			if (array[j] > array[j + 1]) {
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
		}
	}
}
void shellSort(double* a)
{
	double tmp;
	int d, i, j;
	for (d = num / 2; d > 0; d /= 2)
		for (i = 0; i < num - d; i++)
			for (j = i; j >= 0 && a[j] > a[j + d]; j--)
			{
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
}
void shellSortP(double* a)
{
	double tmp;
	int d, i, j;
#pragma omp parallel private(i, j, tmp, d)
	for (d = num / 2; d > 0; d /= 2)
		for (i = 0; i < num - d; i++)
			for (j = i; j >= 0 && a[j] > a[j + d]; j--)
			{
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
}


int main()
{
	setlocale(LC_ALL, "Russian");

	double* array1 = new double[num];
	double* array2 = new double[num];
	double* array3 = new double[num];
	double* array4 = new double[num];
	double* array5 = new double[num];
	double* array6 = new double[num];


	for (int i = 0; i < num; i++) {
		double tmp = rand() / 100.0;
		array1[i] = tmp;
		array2[i] = tmp;
		array3[i] = tmp;
		array4[i] = tmp;
		array5[i] = tmp;
		array6[i] = tmp;
	}
	double t1, t2;

	t1 = omp_get_wtime();
	bubbleSort(array1);
	t2 = omp_get_wtime();
	cout << "Время пузырька: " << t2 - t1 << endl;
	cout.flush();
	cout << endl;


	t1 = omp_get_wtime();
	chetNechetSort(array3);
	t2 = omp_get_wtime();
	cout << "Время чёт-нечёт: " << t2 - t1 << endl;
	cout.flush();
	cout << endl;
	t1 = omp_get_wtime();
	chetNechetSortP(array4);
	t2 = omp_get_wtime();
	cout << "Время параллельного чёт-нечёт: " << t2 - t1 << endl;
	cout.flush();

	t1 = omp_get_wtime();
	shellSort(array5);
	t2 = omp_get_wtime();
	cout << "Время Шелла: " << t2 - t1 << endl;
	cout.flush();
	cout << endl;
	t1 = omp_get_wtime();
	shellSortP(array6);
	t2 = omp_get_wtime();
	cout << "Время параллельного Шелла: " << t2 - t1 << endl;
	cout.flush();

	cout << isSorted(array1) << isSorted(array2) << isSorted(array3) << isSorted(array4) << isSorted(array5) << isSorted(array6);


	/*
	for (int i = 0; i < num; i++) {
		cout << array1[i] << ' ';
	}
	*/
}