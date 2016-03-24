// testGenerator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	ofstream out("..\\tests\\500_semifull_in_ttttt.txt", ios::out);
	int n = 500;
	int m = 125000;
	cout << "starting formin in file...." << endl;
	out << n << " " << m << endl;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if ((i % 2 == 0) && (j % 2 == 1)) {
				out << i << " " << j << " " << (rand() % 100 + 1) << endl;
			}
			if ((i % 2 == 1) && (j % 2 == 0)) {
				out << i << " " << j << " " << (rand() % 100 + 1) << endl;
			}
		}	
	}
	out << 1;
	cout << endl << "finished" << endl;

	cout << "starting formin out file...." << endl;
	ofstream out2("..\\tests\\1000_semifull_out_ttttt.txt", ios::out);
	for (int i = 0; i <= m; ++i) {
		out2 << i << " ";
	}
	cout << endl << "finished" << endl;

	out.close();
	out2.close();
	system("pause");
    return 0;
}

