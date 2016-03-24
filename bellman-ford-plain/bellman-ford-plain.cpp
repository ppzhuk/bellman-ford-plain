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

using namespace std;

const int INF = 1000000000;

struct edge {
	int a, b, cost;
};

string BFplain(int n, int m, vector<edge> const& e, int v) {
	vector<int> d(n, INF);
	d[v] = 0;
	int x;
	for (int i = 0; i < n; ++i) {
		x = -1;
		for (int j = 0; j < m; ++j) {
			if (d[e[j].a] < INF) {
				if (d[e[j].b] > d[e[j].a] + e[j].cost) {
					d[e[j].b] = max(-INF, d[e[j].a] + e[j].cost);
					x = e[j].b;
				}
			}
		}
	}

	stringstream ss;
	if (x == -1)
		for (int i = 0; i < n; ++i) {
			ss << d[i] << " ";
		}
	else {
		++v;
		ss << "Graph has negative cycle from " << v;
	}
	ss << endl;
	return ss.str();
}



void count_incoming_edges(vector<edge> const& e, vector<vector<edge>> & into, int m) {
	for (int j = 0; j < m; ++j) {
		into[e[j].b].push_back(e[j]);
	}
}

vector<int> *dist;
int minDist;

struct thrd_param {
	HANDLE mutex;
	int vertex, from, to;
	vector<vector<edge>> *into;

	thrd_param(HANDLE  m, int f, int t, int v, vector<vector<edge>> *income_edges) {
		mutex = m;
		vertex = v;
		from = f;
		to = t;
		into = income_edges;
	}
};

DWORD WINAPI thrd_func(LPVOID lpParam)
{
	thrd_param p = *(thrd_param*)lpParam;
	int v = p.vertex;
	vector<vector<edge>> * into = p.into;
	for (int i = p.from; i <= p.to; ++i) {
		int a_dist = (*dist)[(*into)[p.vertex][i].a];
		if (a_dist < INF) {
			int d = (*into)[p.vertex][i].cost + a_dist;
			WaitForSingleObject(p.mutex, INFINITE);
			minDist = min(minDist, d);
			ReleaseMutex(p.mutex);
		}
	}
	ExitThread(0);
}

// 1. Выяснить почему и где тормозят бамбуки
// 2. Заоптимизить ||
// 3. ?? сделать || через вектор ребер?
// 4. Комменты, отчет

string BFThreads(int n, int m, vector<edge> const& e, int v, int thrds_num, vector<vector<edge>> & into) {
	dist = new vector<int>(n, INF);
	(*dist)[v] = 0;
	HANDLE mutex = CreateMutex(NULL, false, NULL);
	bool changed = false;
	for (int i = 0; i < n; ++i) {
		changed = false;
		for (int j = 0; j < n; ++j) {
			minDist = (*dist)[j];

			//-----parrallel part------
			if (into[j].size() == 0)
				continue;
			int threads_number = thrds_num;
			int edges_per_thrd = into[j].size() / threads_number;
			int edges_left     = into[j].size() % threads_number;

			while (edges_per_thrd == 0 && threads_number > 1) {
				threads_number /= 2;
				edges_per_thrd = into[j].size() / threads_number;
				edges_left = into[j].size() % threads_number;
			}

			HANDLE* thrd_pool = new HANDLE[threads_number];
			thrd_param *p = new thrd_param(&mutex, 0, (edges_per_thrd + edges_left - 1), j, &into);
			thrd_pool[0] = CreateThread(NULL, 0, &thrd_func, p, 0, NULL);

			for (int k = 1; k < threads_number; ++k) {
				p = new thrd_param(&mutex, (p->to)+1, (p->to) + edges_per_thrd, j, &into);
				thrd_pool[k] = CreateThread(NULL, 0, &thrd_func, p, 0, NULL);
			}

			WaitForMultipleObjects(threads_number, thrd_pool, true, INFINITE);
			//--------------------------

			if (minDist < (*dist)[j]) {
				(*dist)[j] = minDist;
				changed = true;
			}
		}
	}

	stringstream ss;
	if (!changed)
		for (int i = 0; i < n; ++i) {
			ss << (*dist)[i] << " ";
		}
	else {
		++v;
		ss << "Graph has negative cycle from " << v;
	}
	ss << endl;
	return ss.str();
}

string BFopenMP(int n, int m, vector<edge> const& e, int v, int threads_number) {
	return "";
}

int main()
{
	int n, m, v;
	vector<edge> e;
	cout << "n=";
	cin >> n;
	cout << "m=";
	cin >> m;
	cout << "a b c" << endl;
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
	vector<vector<edge>> into(n);

	switch (mode) {
	case 1:
		start_time = clock();
		res = BFplain(n, m, e, v);
		break;
	case 2:
		count_incoming_edges(e, into, m);
		start_time = clock();
		res = BFThreads(n, m, e, v, threads_number, into);
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