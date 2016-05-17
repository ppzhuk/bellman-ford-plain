// bellman-ford-plain.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <Windows.h>
#include <boost/thread.hpp>
#include <boost/thread/barrier.hpp>
#include <omp.h>


using namespace std;

const int INF = 1000000000;

struct edge {
	int a, b, cost;
};

// -------------------------------------
// Последовательный вариант
// -------------------------------------

/* n - количество вершин
m - количество ребер
v - стартовая вершина
e - список ребер
*/
string BFplain(int n, int m, vector<edge> const& e, int v) {
	vector<int> d(n, INF);
	d[v] = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (d[e[j].a] < INF) {
				if (d[e[j].b] > d[e[j].a] + e[j].cost) {
					d[e[j].b] = max(-INF, d[e[j].a] + e[j].cost);
				}
			}
		}
	}

	stringstream ss;
	for (int i = 0; i < n; ++i) {
		ss << d[i] << " ";
	}
	ss << endl;
	return ss.str();
}

// -------------------------------------
// Потоки
// -------------------------------------

vector<int> * dist;
vector<edge> const* edgs;

struct thrd_param {
	int n, from, to;
	boost::barrier *barrier;

	thrd_param(int num, int f, int t, boost::barrier *bar) {
		n = num;
		from = f;
		to = t;
		barrier = bar;
	}
};

DWORD WINAPI thrd_func(LPVOID lpParam)
{
	thrd_param p = *(thrd_param*)lpParam;
	int n = p.n;
	int from = p.from;
	int to = p.to;
	boost::barrier *barrier = p.barrier;

	for (int i = 0; i < n; ++i) {
		for (int j = from; j <= to; ++j) {
			if ((*dist)[(*edgs)[j].a] < INF) {
				if ((*dist)[(*edgs)[j].b] > (*dist)[(*edgs)[j].a] + (*edgs)[j].cost) {
					(*dist)[(*edgs)[j].b] = max(-INF, (*dist)[(*edgs)[j].a] + (*edgs)[j].cost);
				}
			}
		}
		(*barrier).wait();
	}

	ExitThread(0);
}

string BFThreads(int n, int m, vector<edge> const& e, int v, int thrds_num) {

	edgs = &e;
	dist = new vector<int>(n, INF);
	(*dist)[v] = 0;
	// потоков не может быть больше ребер
	if (thrds_num > m) {
		thrds_num = m;
	}

	boost::barrier barrier(thrds_num);

	// создаем пул потоков
	HANDLE* thrd_pool = new HANDLE[thrds_num];

	thrd_param *p;

	// определяем какую часть списка ребер будет обрабатывать один поток
	int edges_per_thrd = e.size() / thrds_num;
	int edges_left = e.size() % thrds_num;
	int from = 0;
	int to = edges_per_thrd + edges_left - 1;

	for (int i = 0; i < thrds_num; ++i) {
		// задаем параметры потока и запускаем тред
		p = new thrd_param(n, from, to, &barrier);
		thrd_pool[i] = CreateThread(NULL, 0, &thrd_func, p, 0, NULL);
		from = to;
		to += edges_per_thrd;
	}

	WaitForMultipleObjects(thrds_num, thrd_pool, true, INFINITE);
	for (int i = 0; i < thrds_num; i++) {
		CloseHandle(thrd_pool[i]);
	}

	stringstream ss;
	for (int i = 0; i < n; ++i) {
		ss << (*dist)[i] << " ";
	}
	ss << endl;
	return ss.str();
}

// -------------------------------------
// OpenMP
// -------------------------------------

string BFopenMP(const int n, const  int m, vector<edge> const& e, int v, int thrds_num) {
	vector<int> d(n, INF);
	d[v] = 0;
	if (thrds_num > m) {
		thrds_num = m;
	}
	const int edges_per_thrd = e.size() / thrds_num + e.size() % thrds_num;

	omp_set_num_threads(thrds_num);
	int i;
	#pragma omp parallel private (i) shared (d, e)
	{
		for (i = 0; i < n; ++i) {
			#pragma omp for schedule(dynamic, edges_per_thrd)
			for (int j = 0; j < m; ++j) {
				if (d[e[j].a] < INF) {
					if (d[e[j].b] > d[e[j].a] + e[j].cost) {
						d[e[j].b] = max(-INF, d[e[j].a] + e[j].cost);
					}
				}
			}	
		}
	}
	

	stringstream ss;
	for (int i = 0; i < n; ++i) {
		ss << d[i] << " ";
	}
	ss << endl;
	return ss.str();
}

int main(int argc, char* argv[])
{
	int n, m, v;
	vector<edge> e;
	cout << "n=";
	cin >> n;
	cout << "m=";
	cin >> m;
	cout << "a b cost" << endl;
	for (int i = 0; i < m; ++i) {
		struct edge current_edge;
		cin >> current_edge.a >> current_edge.b >> current_edge.cost;
		--current_edge.a;
		--current_edge.b;
		e.push_back(current_edge);
	}
	cout << "start=";
	cin >> v;
	--v;
	cout << "mode (1 - plain, 2 - threads, 3 - openMP): ";
	int mode = 0;
	cin >> mode;
	int threads_number = 0;
	if (mode == 2 || mode == 3) {
		cout << "threads number [1..64]=";
		cin >> threads_number;
		if (threads_number < 1 || threads_number > 64) {
			cout << "incorrect threads number" << endl;
			return 0;
		}
	}


	string res = "";
	unsigned int start_time;

	switch (mode) {
	case 1:
		start_time = clock();
		res = BFplain(n, m, e, v);
		break;
	case 2:
		start_time = clock();
		res = BFThreads(n, m, e, v, threads_number);
		break;
	case 3:
		start_time = clock();
		res = BFopenMP(n, m, e, v, threads_number);
		break;
	default:
		cout << "incorrect mode" << endl;
		return 0;
	}

	unsigned int end_time = clock();
	unsigned int work_time = end_time - start_time;
	cout << res;
	cout << "working time: " << work_time << endl;

	system("pause");
	return 0;
}