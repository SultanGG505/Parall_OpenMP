#include <iostream>
#include <fstream>
#include <vector>
#include "omp.h"
using namespace std;
const int maxV = 1000;
int i, j, n;
int GR[maxV][maxV];
//алгоритм Флойда-Уоршелла
void FU(int D[][maxV], int V)
{
	int k;
	for (i = 0; i < V; i++) D[i][i] = 0;

	for (k = 0; k < V; k++)
		for (i = 0; i < V; i++)
			for (j = 0; j < V; j++)
				if (D[i][k] && D[k][j] && i != j)
					if (D[i][k] + D[k][j] < D[i][j] || D[i][j] == 0)
						D[i][j] = D[i][k] + D[k][j];

	return;
}
void parallel_FU(int D[][maxV], int V)
{
	int k;
	for (i = 0; i < V; i++) D[i][i] = 0;

#pragma omp parallel private(i, j)
	for (k = 0; k < V; k++)
		for (i = 0; i < V; i++)
			for (j = 0; j < V; j++)
				if (D[i][k] && D[k][j] && i != j)
					if (D[i][k] + D[k][j] < D[i][j] || D[i][j] == 0)
						D[i][j] = D[i][k] + D[k][j];

	return;
}
//главная функция
void main()
{
	setlocale(LC_ALL, "Rus");
	ifstream inFile("input.txt");
	n = 300;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			GR[i][j] = rand() / 10.0;
			if (i == j)
				GR[i][j] = 0;
		}
	double t1, t2;

	t1 = omp_get_wtime();
	FU(GR, n);
	t2 = omp_get_wtime();
	cout << "Время Флойда: " << t2 - t1 << endl;

	t1 = omp_get_wtime();
	parallel_FU(GR, n);
	t2 = omp_get_wtime();
	cout << "Время параллельного Флойда: " << t2 - t1 << endl;

	cin >> t1;
}