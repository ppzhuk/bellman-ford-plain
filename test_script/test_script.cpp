// test_script.cpp: определяет точку входа для консольного приложения.
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
	if (thrds_num > m) {
		thrds_num = m;
	}

	boost::barrier barrier(thrds_num);
	HANDLE* thrd_pool = new HANDLE[thrds_num];

	thrd_param *p;
	int edges_per_thrd = e.size() / thrds_num;
	int edges_left = e.size() % thrds_num;
	int from = 0;
	int to = edges_per_thrd + edges_left - 1;
	for (int i = 0; i < thrds_num; ++i) {
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

namespace DataReadNS
{
	ifstream in_data, out_data;

	int n, m, v;
	vector<edge> e;

	string expected = "";

	void read_in_data(string filename_in) {
		in_data.open(filename_in, ios::in);
		if (in_data.is_open()) {
			in_data >> n >> m;
			for (int i = 0; i < m; ++i) {
				struct edge current_edge;
				in_data >> current_edge.a >> current_edge.b >> current_edge.cost;
				--current_edge.a;
				--current_edge.b;
				e.push_back(current_edge);
			}
			in_data >> v;
			--v;
			in_data.close();
		}
	}

	void read_out_data(string filename_out) {
		out_data.open(filename_out, ios::in);
		if (out_data.is_open()) {
			getline(out_data, expected);
			expected += '\n';
			out_data.close();
		}
	}

	void vipe_data() {
		n = m = v = 0;
		e.clear();
		expected = "";
	}

	void start_test(int iteration, int mode, int thrd_num, ofstream &out) {
		
		string res = "";
		unsigned int start_time;
		switch (mode) {
		case 1:
			start_time = clock();
			res = BFplain(n, m, e, v);
			break;
		case 2:
			start_time = clock();
			res = BFThreads(n, m, e, v, thrd_num);
			break;
		case 3:
			start_time = clock();
			res = BFopenMP(n, m, e, v, thrd_num);
			break;
		default:
			cout << "incorrect mode" << endl;
			exit(-1);
		}
		unsigned int end_time = clock();
		unsigned int work_time = end_time - start_time;
		if (res == expected) {
			out << work_time << endl;
			cout << "Iteration: " << iteration << " Time: " << work_time << " ms." << endl;
		}
		else {
			cout << "Error while evaluating! Iteration: " << iteration << ". Aborting." << endl;
			exit(-1);
		}
	}
}


int main(int argc, char* argv[])
{
	int mode = 1;
	int threads = 0;

	ofstream out_plian("plain_500semifull_script_results.txt");
	ofstream out_threads2("threads2_500semifull_script_results.txt");
	ofstream out_threads3("threads3_500semifull_script_results.txt");
	ofstream out_threads4("threads4_500semifull_script_results.txt");
	ofstream out_threads5("threads5_500semifull_script_results.txt");
	ofstream out_threads8("threads8_500semifull_script_results.txt");
	ofstream out_threads9("threads9_500semifull_script_results.txt");
	ofstream out_OMP2("OMP2_500semifull_script_results.txt");
	ofstream out_OMP3("OMP3_500semifull_script_results.txt");
	ofstream out_OMP4("OMP4_500semifull_script_results.txt");
	ofstream out_OMP5("OMP5_500semifull_script_results.txt");
	ofstream out_OMP8("OMP8_500semifull_script_results.txt");
	ofstream out_OMP9("OMP9_500semifull_script_results.txt");

	DataReadNS::vipe_data();
	DataReadNS::read_in_data("..\\tests\\500_semifull_in.txt");
	DataReadNS::read_out_data("..\\tests\\500_semifull_out.txt");

	cout << "Iterations amount: ";
	int iter;
	cin >> iter;
	++iter;

	cout << "Script started" << endl;

	//-------------------------------

	cout << "Performing plain experiments..." << endl;
	mode = 1;
	threads = 0;
	for (int i = 1; i < iter; ++i) {
		DataReadNS::start_test(i, mode, threads, out_plian);
	}
	cout << "Plain experiments finished!" << endl;
	out_plian.close();

	//---------------------------

	cout << "Performing threads2 experiments..." << endl;
	mode = 2;
	threads = 2;
	for (int i = 1; i < iter; ++i) {
		DataReadNS::start_test(i, mode, threads, out_threads2);
	}
	cout << "The threads2 experiments finished!" << endl;
	out_threads2.close();

	cout << "Performing threads3 experiments..." << endl;
	mode = 2;
	threads = 3;
	for (int i = 1; i < iter; ++i) {
		DataReadNS::start_test(i, mode, threads, out_threads3);
	}
	cout << "The threads3 experiments finished!" << endl;
	out_threads3.close();

	cout << "Performing threads4 experiments..." << endl;
	mode = 2;
	threads = 4;
	for (int i = 1; i < iter; ++i) {
		DataReadNS::start_test(i, mode, threads, out_threads4);
	}
	cout << "The threads4 experiments finished!" << endl;
	out_threads4.close();

	cout << "Performing threads5 experiments..." << endl;
	mode = 2;
	threads = 5;
	for (int i = 1; i < iter; ++i) {
		DataReadNS::start_test(i, mode, threads, out_threads5);
	}
	cout << "The threads5 experiments finished!" << endl;
	out_threads5.close();

	cout << "Performing threads8 experiments..." << endl;
	mode = 2;
	threads = 8;
	for (int i = 1; i < iter; ++i) {
		DataReadNS::start_test(i, mode, threads, out_threads8);
	}
	cout << "The threads8 experiments finished!" << endl;
	out_threads8.close();

	cout << "Performing threads9 experiments..." << endl;
	mode = 2;
	threads = 9;
	for (int i = 1; i < iter; ++i) {
		DataReadNS::start_test(i, mode, threads, out_threads9);
	}
	cout << "The threads9 experiments finished!" << endl;
	out_threads9.close();

	//--------------------------------------

	cout << "Performing OMP2 experiments..." << endl;
	mode = 3;
	threads = 2;
	for (int i = 1; i < iter; ++i) {
		DataReadNS::start_test(i, mode, threads, out_OMP2);
	}
	cout << "The OMP2 experiments finished!" << endl;
	out_OMP2.close();


	cout << "Performing OMP3 experiments..." << endl;
	mode = 3;
	threads = 3;
	for (int i = 1; i < iter; ++i) {
		DataReadNS::start_test(i, mode, threads, out_OMP3);
	}
	cout << "The OMP3 experiments finished!" << endl;
	out_OMP3.close();



	cout << "Performing OMP4 experiments..." << endl;
	mode = 3;
	threads = 4;
	for (int i = 1; i < iter; ++i) {
		DataReadNS::start_test(i, mode, threads, out_OMP4);
	}
	cout << "The OMP4 experiments finished!" << endl;
	out_OMP4.close();



	cout << "Performing OMP5 experiments..." << endl;
	mode = 3;
	threads = 5;
	for (int i = 1; i < iter; ++i) {
		DataReadNS::start_test(i, mode, threads, out_OMP5);
	}
	cout << "The OMP5 experiments finished!" << endl;
	out_OMP5.close();



	cout << "Performing OMP8 experiments..." << endl;
	mode = 3;
	threads = 8;
	for (int i = 1; i < iter; ++i) {
		DataReadNS::start_test(i, mode, threads, out_OMP8);
	}
	cout << "The OMP8 experiments finished!" << endl;
	out_OMP8.close();



	cout << "Performing OMP9 experiments..." << endl;
	mode = 3;
	threads = 9;
	for (int i = 1; i < iter; ++i) {
		DataReadNS::start_test(i, mode, threads, out_OMP9);
	}
	cout << "The OMP9 experiments finished!" << endl;
	out_OMP9.close();

	cout << "Script finished!" << endl;

	system("pause");
	return 0;
}

