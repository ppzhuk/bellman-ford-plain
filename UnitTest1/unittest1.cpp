#include "stdafx.h"
#include "CppUnitTest.h"
#include "bellman-ford-plain.cpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
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

	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Test1)
		{
			vipe_data();
			read_in_data("..\\tests\\1_in.txt");
			read_out_data("..\\tests\\1_out.txt");
			Assert::AreEqual(BFplain(n, m, e, v), expected);

		}

		TEST_METHOD(Test1k)
		{
			vipe_data();
			read_in_data("..\\tests\\1k_in.txt");
			read_out_data("..\\tests\\1k_out.txt");
			Assert::AreEqual(BFplain(n, m, e, v), expected);

		}

		TEST_METHOD(Test3k)
		{
			vipe_data();
			read_in_data("..\\tests\\3k_in.txt");
			read_out_data("..\\tests\\3k_out.txt");
			Assert::AreEqual(BFplain(n, m, e, v), expected);

		}

		TEST_METHOD(Test500_semifull)
		{
			vipe_data();
			read_in_data("..\\tests\\500_semifull_in.txt");
			read_out_data("..\\tests\\500_semifull_out.txt");
			Assert::AreEqual(BFplain(n, m, e, v), expected);

		}
	};

	TEST_CLASS(UnitTest2)
	{
	public:

		TEST_METHOD(Threads2Test1)
		{
			vipe_data();
			read_in_data("..\\tests\\1_in.txt");
			read_out_data("..\\tests\\1_out.txt");
			vector<vector<edge>> into(n);
			Assert::AreEqual(BFThreads(n, m, e, v, 2), expected);
		}

		TEST_METHOD(Threads3Test1)
		{
			vipe_data();
			read_in_data("..\\tests\\1_in.txt");
			read_out_data("..\\tests\\1_out.txt");
			vector<vector<edge>> into(n);
			Assert::AreEqual(BFThreads(n, m, e, v, 3), expected);
		}

		TEST_METHOD(Threads4Test1)
		{
			vipe_data();
			read_in_data("..\\tests\\1_in.txt");
			read_out_data("..\\tests\\1_out.txt");
			vector<vector<edge>> into(n);
			Assert::AreEqual(BFThreads(n, m, e, v, 4), expected);
		}

		TEST_METHOD(Threads2Test1k)
		{
			vipe_data();
			read_in_data("..\\tests\\1k_in.txt");
			read_out_data("..\\tests\\1k_out.txt");
			vector<vector<edge>> into(n);
			
			Assert::AreEqual(BFThreads(n, m, e, v, 2), expected);

		}

		TEST_METHOD(Threads3Test1k)
		{
			vipe_data();
			read_in_data("..\\tests\\1k_in.txt");
			read_out_data("..\\tests\\1k_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFThreads(n, m, e, v, 3), expected);

		}

		TEST_METHOD(Threads4Test1k)
		{
			vipe_data();
			read_in_data("..\\tests\\1k_in.txt");
			read_out_data("..\\tests\\1k_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFThreads(n, m, e, v, 4), expected);

		}

		TEST_METHOD(Threads5Test1k)
		{
			vipe_data();
			read_in_data("..\\tests\\1k_in.txt");
			read_out_data("..\\tests\\1k_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFThreads(n, m, e, v, 5), expected);

		}

		TEST_METHOD(Threads8Test1k)
		{
			vipe_data();
			read_in_data("..\\tests\\1k_in.txt");
			read_out_data("..\\tests\\1k_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFThreads(n, m, e, v, 8), expected);

		}

		TEST_METHOD(Threads9Test1k)
		{
			vipe_data();
			read_in_data("..\\tests\\1k_in.txt");
			read_out_data("..\\tests\\1k_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFThreads(n, m, e, v, 9), expected);

		}

		TEST_METHOD(Threads2Test3k)
		{
			vipe_data();
			read_in_data("..\\tests\\3k_in.txt");
			read_out_data("..\\tests\\3k_out.txt");
			vector<vector<edge>> into(n);
			Assert::AreEqual(BFThreads(n, m, e, v, 2), expected);

		}

		TEST_METHOD(Threads3Test3k)
		{
			vipe_data();
			read_in_data("..\\tests\\3k_in.txt");
			read_out_data("..\\tests\\3k_out.txt");
			vector<vector<edge>> into(n);
			Assert::AreEqual(BFThreads(n, m, e, v, 3), expected);

		}

		TEST_METHOD(Threads4Test3k)
		{
			vipe_data();
			read_in_data("..\\tests\\3k_in.txt");
			read_out_data("..\\tests\\3k_out.txt");
			vector<vector<edge>> into(n);
			Assert::AreEqual(BFThreads(n, m, e, v, 4), expected);

		}

		TEST_METHOD(Threads5Test3k)
		{
			vipe_data();
			read_in_data("..\\tests\\3k_in.txt");
			read_out_data("..\\tests\\3k_out.txt");
			vector<vector<edge>> into(n);
			Assert::AreEqual(BFThreads(n, m, e, v, 5), expected);

		}

		TEST_METHOD(Threads8Test3k)
		{
			vipe_data();
			read_in_data("..\\tests\\3k_in.txt");
			read_out_data("..\\tests\\3k_out.txt");
			vector<vector<edge>> into(n);
			Assert::AreEqual(BFThreads(n, m, e, v, 8), expected);

		}

		TEST_METHOD(Threads9Test3k)
		{
			vipe_data();
			read_in_data("..\\tests\\3k_in.txt");
			read_out_data("..\\tests\\3k_out.txt");
			vector<vector<edge>> into(n);
			Assert::AreEqual(BFThreads(n, m, e, v, 9), expected);

		}

		TEST_METHOD(Threads2Test500_semifull)
		{
			vipe_data();
			read_in_data("..\\tests\\500_semifull_in.txt");
			read_out_data("..\\tests\\500_semifull_out.txt");
			vector<vector<edge>> into(n);
			
			Assert::AreEqual(BFThreads(n, m, e, v, 2), expected);

		}

		TEST_METHOD(Threads3Test500_semifull)
		{
			vipe_data();
			read_in_data("..\\tests\\500_semifull_in.txt");
			read_out_data("..\\tests\\500_semifull_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFThreads(n, m, e, v, 3), expected);

		}

		TEST_METHOD(Threads4Test500_semifull)
		{
			vipe_data();
			read_in_data("..\\tests\\500_semifull_in.txt");
			read_out_data("..\\tests\\500_semifull_out.txt");
			vector<vector<edge>> into(n);
			
			Assert::AreEqual(BFThreads(n, m, e, v, 4), expected);

		}

		TEST_METHOD(Threads5Test500_semifull)
		{
			vipe_data();
			read_in_data("..\\tests\\500_semifull_in.txt");
			read_out_data("..\\tests\\500_semifull_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFThreads(n, m, e, v, 5), expected);

		}

		TEST_METHOD(Threads8Test500_semifull)
		{
			vipe_data();
			read_in_data("..\\tests\\500_semifull_in.txt");
			read_out_data("..\\tests\\500_semifull_out.txt");
			vector<vector<edge>> into(n);
			
			Assert::AreEqual(BFThreads(n, m, e, v, 8), expected);

		}

		TEST_METHOD(Threads9Test500_semifull)
		{
			vipe_data();
			read_in_data("..\\tests\\500_semifull_in.txt");
			read_out_data("..\\tests\\500_semifull_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFThreads(n, m, e, v, 9), expected);

		}
	};

	TEST_CLASS(UnitTest3)
	{
	public:

		TEST_METHOD(OMP2Test1)
		{
			vipe_data();
			read_in_data("..\\tests\\1_in.txt");
			read_out_data("..\\tests\\1_out.txt");
			vector<vector<edge>> into(n);
			Assert::AreEqual(BFopenMP(n, m, e, v, 2), expected);
		}

		TEST_METHOD(OMP3Test1)
		{
			vipe_data();
			read_in_data("..\\tests\\1_in.txt");
			read_out_data("..\\tests\\1_out.txt");
			vector<vector<edge>> into(n);
			Assert::AreEqual(BFopenMP(n, m, e, v, 3), expected);
		}

		TEST_METHOD(OMP4Test1)
		{
			vipe_data();
			read_in_data("..\\tests\\1_in.txt");
			read_out_data("..\\tests\\1_out.txt");
			vector<vector<edge>> into(n);
			Assert::AreEqual(BFopenMP(n, m, e, v, 4), expected);
		}

		TEST_METHOD(OMP2Test1k)
		{
			vipe_data();
			read_in_data("..\\tests\\1k_in.txt");
			read_out_data("..\\tests\\1k_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFopenMP(n, m, e, v, 2), expected);

		}

		TEST_METHOD(OMP3Test1k)
		{
			vipe_data();
			read_in_data("..\\tests\\1k_in.txt");
			read_out_data("..\\tests\\1k_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFopenMP(n, m, e, v, 3), expected);

		}

		TEST_METHOD(OMP4Test1k)
		{
			vipe_data();
			read_in_data("..\\tests\\1k_in.txt");
			read_out_data("..\\tests\\1k_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFopenMP(n, m, e, v, 4), expected);

		}

		TEST_METHOD(OMP5Test1k)
		{
			vipe_data();
			read_in_data("..\\tests\\1k_in.txt");
			read_out_data("..\\tests\\1k_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFopenMP(n, m, e, v, 5), expected);

		}

		TEST_METHOD(OMP8Test1k)
		{
			vipe_data();
			read_in_data("..\\tests\\1k_in.txt");
			read_out_data("..\\tests\\1k_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFopenMP(n, m, e, v, 8), expected);

		}

		TEST_METHOD(OMP9Test1k)
		{
			vipe_data();
			read_in_data("..\\tests\\1k_in.txt");
			read_out_data("..\\tests\\1k_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFopenMP(n, m, e, v, 9), expected);

		}

		TEST_METHOD(OMP2Test3k)
		{
			vipe_data();
			read_in_data("..\\tests\\3k_in.txt");
			read_out_data("..\\tests\\3k_out.txt");
			vector<vector<edge>> into(n);
			Assert::AreEqual(BFopenMP(n, m, e, v, 2), expected);

		}

		TEST_METHOD(OMP3Test3k)
		{
			vipe_data();
			read_in_data("..\\tests\\3k_in.txt");
			read_out_data("..\\tests\\3k_out.txt");
			vector<vector<edge>> into(n);
			Assert::AreEqual(BFopenMP(n, m, e, v, 3), expected);

		}

		TEST_METHOD(OMP4Test3k)
		{
			vipe_data();
			read_in_data("..\\tests\\3k_in.txt");
			read_out_data("..\\tests\\3k_out.txt");
			vector<vector<edge>> into(n);
			Assert::AreEqual(BFopenMP(n, m, e, v, 4), expected);

		}

		TEST_METHOD(OMP5Test3k)
		{
			vipe_data();
			read_in_data("..\\tests\\3k_in.txt");
			read_out_data("..\\tests\\3k_out.txt");
			vector<vector<edge>> into(n);
			Assert::AreEqual(BFopenMP(n, m, e, v, 5), expected);

		}

		TEST_METHOD(OMP8Test3k)
		{
			vipe_data();
			read_in_data("..\\tests\\3k_in.txt");
			read_out_data("..\\tests\\3k_out.txt");
			vector<vector<edge>> into(n);
			Assert::AreEqual(BFopenMP(n, m, e, v, 8), expected);

		}

		TEST_METHOD(OMP9Test3k)
		{
			vipe_data();
			read_in_data("..\\tests\\3k_in.txt");
			read_out_data("..\\tests\\3k_out.txt");
			vector<vector<edge>> into(n);
			Assert::AreEqual(BFopenMP(n, m, e, v, 9), expected);

		}

		TEST_METHOD(OMP2Test500_semifull)
		{
			vipe_data();
			read_in_data("..\\tests\\500_semifull_in.txt");
			read_out_data("..\\tests\\500_semifull_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFopenMP(n, m, e, v, 2), expected);

		}

		TEST_METHOD(OMP3Test500_semifull)
		{
			vipe_data();
			read_in_data("..\\tests\\500_semifull_in.txt");
			read_out_data("..\\tests\\500_semifull_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFopenMP(n, m, e, v, 3), expected);

		}

		TEST_METHOD(OMP4Test500_semifull)
		{
			vipe_data();
			read_in_data("..\\tests\\500_semifull_in.txt");
			read_out_data("..\\tests\\500_semifull_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFopenMP(n, m, e, v, 4), expected);

		}

		TEST_METHOD(OMP5Test500_semifull)
		{
			vipe_data();
			read_in_data("..\\tests\\500_semifull_in.txt");
			read_out_data("..\\tests\\500_semifull_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFopenMP(n, m, e, v, 5), expected);

		}

		TEST_METHOD(OMP8Test500_semifull)
		{
			vipe_data();
			read_in_data("..\\tests\\500_semifull_in.txt");
			read_out_data("..\\tests\\500_semifull_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFopenMP(n, m, e, v, 8), expected);

		}

		TEST_METHOD(OMP9Test500_semifull)
		{
			vipe_data();
			read_in_data("..\\tests\\500_semifull_in.txt");
			read_out_data("..\\tests\\500_semifull_out.txt");
			vector<vector<edge>> into(n);

			Assert::AreEqual(BFopenMP(n, m, e, v, 9), expected);

		}
	};
}